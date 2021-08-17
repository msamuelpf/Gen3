/*!
 * @file
 * @brief Single wire GEA2 interface implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdbool.h>
#include <string.h>
#include "Gea2Constants.h"
#include "Gea2Interface_SingleWire.h"
#include "Gea2InterfaceAcceptDelegate.h"
#include "Gea2Packet.h"
#include "Fsm.h"
#include "uassert.h"
#include "utils.h"

// Send packet should match Gea2Packet, but stores dataLength (per spec) instead of payloadLength
// (application convenience)
typedef struct
{
   uint8_t destination;
   uint8_t dataLength;
   uint8_t source;
   uint8_t data[1];
} SendPacket_t;

STATIC_ASSERT(sizeof(SendPacket_t) == sizeof(Gea2Packet_t));

enum
{
   CrcSize = sizeof(Crc16_t),

   // Dest (1), Len (1), Src (1), CRC (2), STX (1), ETX (1)
   PacketOverhead = 7,

   // Payload length for application doesn't include crc (2 bytes), dst (1 byte) or len (1 byte)
   PacketBytesNotIncludedInPayload = (CrcSize + offsetof(Gea2Packet_t, payload)),

   // The size of everything in a send packet that isn't part of the payload
   SendPacketHeaderSize = (offsetof(SendPacket_t, data)),

   UnbufferedBytes = 2
};

enum
{
   FSM_BYTE_RECEIVED = FSM_USER_SIGNAL_START,
   FSM_INTERBYTE_TIMEOUT,
   FSM_REFLECTION_TIMEOUT,
   FSM_SEND_READY,
   FSM_IDLE_TIMEOUT_COMPLETE,
   FSM_COLLISION_TIMEOUT_COMPLETE,
   FSM_ACK_TIMEOUT,
   FSM_SERIAL_ERROR
};

enum
{
   SEND_STATE_STX,
   SEND_STATE_DATA,
   SEND_STATE_CRC_MSB,
   SEND_STATE_CRC_LSB,
   SEND_STATE_ETX,
   SEND_STATE_DONE
};

static void State_Receive(Fsm_t *fsm, FsmSignal_t signal, const void *data);
static void State_Idle(Fsm_t *fsm, FsmSignal_t signal, const void *data);
static void State_IdleCooldown(Fsm_t *fsm, FsmSignal_t signal, const void *data);
static void State_CollisionCooldown(Fsm_t *fsm, FsmSignal_t signal, const void *data);
static void State_Send(Fsm_t *fsm, FsmSignal_t signal, const void *data);
static void State_WaitForAck(Fsm_t *fsm, FsmSignal_t signal, const void *data);

// Obtain the enclosing Gea2Interface_SingleWire_t from an fsm
static Gea2Interface_SingleWire_t * InterfaceFromFsm(Fsm_t *fsm)
{
   return CONTAINER_OF(Gea2Interface_SingleWire_t, fsm, fsm);
}

static bool LenValid(uint8_t *receiveBuffer, size_t receiveCount)
{
   const size_t lenIndex = offsetof(Gea2Packet_t, payloadLength);

   bool lengthMatches = (bool)(receiveBuffer[lenIndex] == (receiveCount + UnbufferedBytes));
   bool minimumLengthSatisfied = (bool)(receiveCount >= (UnbufferedBytes + GEA2PACKET_OVERHEAD));

   return lengthMatches && minimumLengthSatisfied;
}

static bool CrcValid(uint8_t *receiveBuffer, size_t receiveCount, I_Crc16Calculator_t *crc16Calculator)
{
   Crc16_t crc = Crc16Calculator_ProcessString(crc16Calculator, GEA2_CRC_SEED, receiveBuffer, receiveCount - CrcSize);
   bool msbMatches = (bool)(receiveBuffer[receiveCount - 2] == (crc >> 8));
   bool lsbMatches = (bool)(receiveBuffer[receiveCount - 1] == (crc & 0x00FF));

   return msbMatches && lsbMatches;
}

static bool PacketValid(uint8_t *receiveBuffer, size_t receiveCount, I_Crc16Calculator_t *crc16Calculator)
{
   // Don't need bounds check in CrcValid because LenValid is always checked first
   return LenValid(receiveBuffer, receiveCount) && CrcValid(receiveBuffer, receiveCount, crc16Calculator);
}

static void FinalizeReceivedPacket(uint8_t *receiveBuffer, const uint8_t receiveCount)
{
   Gea2Packet_t *packet = (Gea2Packet_t *)receiveBuffer;

   packet->payloadLength = (uint8_t)(receiveCount - PacketBytesNotIncludedInPayload);
}

static bool IsBroadcastAddress(const uint8_t address)
{
   return (GEA2_BCAST_MASK & address) == GEA2_BCAST_MASK;
}

static void HandleAck(Gea2Interface_SingleWire_t *instance, const uint8_t address)
{
   if(!IsBroadcastAddress(address))
   {
      if((address == instance->address)
         || Gea2InterfaceAcceptDelegate_CheckAccept(instance->acceptDelegate, address))
      {
         Uart_Send(instance->serial, GEA2_ACK);
      }
   }
}

// Handle bytes received while in the receive state
static void Receive_ProcessReceivedByte(Gea2Interface_SingleWire_t *instance, const uint8_t byte)
{
   if(instance->receive.count >= instance->sendReceiveBufferSize)
   {
      // Ran out of space, abort!
      Fsm_Transition(&instance->fsm, State_IdleCooldown);
   }
   else if(instance->receive.escaped)
   {
      instance->sendReceiveBuffer[instance->receive.count++] = byte;
      instance->receive.escaped = false;
   }
   else
   {
      switch(byte)
      {
         case GEA2_ESC:
            instance->receive.escaped = true;
            break;

         case GEA2_ACK:
            Fsm_Transition(&instance->fsm, State_IdleCooldown);
            break;

         case GEA2_STX:
            Fsm_Transition(&instance->fsm, State_Receive);
            break;

         case GEA2_ETX:
            if(PacketValid(instance->sendReceiveBuffer, (size_t)instance->receive.count, instance->crc16Calculator))
            {
               Gea2Packet_t *packet = (Gea2Packet_t *)instance->sendReceiveBuffer;
               Gea2InterfaceOnReceiveArgs_t onReceiveArgs =
                  { packet };

               FinalizeReceivedPacket(instance->sendReceiveBuffer, instance->receive.count);

               // Send ACK first in case the notifier takes a while
               HandleAck(instance, packet->destination);

               Event_Synchronous_Publish(&instance->OnReceive, &onReceiveArgs);
            }

            // Done receiving this packet
            Fsm_Transition(&instance->fsm, State_IdleCooldown);
            break;

         default:
            instance->sendReceiveBuffer[instance->receive.count++] = byte;
            break;
      }
   }
}

static void InterByteTimeout(void *context)
{
   Gea2Interface_SingleWire_t *instance = context;
   Fsm_SendSignal(&instance->fsm, FSM_INTERBYTE_TIMEOUT, NULL);
}

static void StartInterByteTimeoutTimer(Gea2Interface_SingleWire_t *instance)
{
   TimerModule_StartOneShot(&instance->timerModule, &instance->timer, GEA2_INTERBYTE_TIMEOUT_MSEC, InterByteTimeout, instance);
}

static void State_Receive(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);

   switch(signal)
   {
      case FSM_ENTRY:
         instance->receive.count = 0;
         StartInterByteTimeoutTimer(instance);
         break;

      case FSM_BYTE_RECEIVED:
         {
         const uint8_t byte = *(const uint8_t *)data;
         StartInterByteTimeoutTimer(instance);
         Receive_ProcessReceivedByte(instance, byte);
         break;
      }

      case FSM_SERIAL_ERROR:
         case FSM_INTERBYTE_TIMEOUT:
         Fsm_Transition(fsm, State_IdleCooldown);
         break;

      case FSM_EXIT:
         TimerModule_Stop(&instance->timerModule, &instance->timer);
         break;

      default:
         break;
   }
}

static Crc16_t CalculateCrc(const SendPacket_t *sendPacket, const uint8_t payloadSize, I_Crc16Calculator_t *calculator)
{
   return Crc16Calculator_ProcessString(calculator, GEA2_CRC_SEED, (const void * )sendPacket, (size_t )(payloadSize + SendPacketHeaderSize));
}

static void PrepareSendPacket(Gea2Interface_SingleWire_t *instance)
{
   uint8_t retries;
   uint8_t packetPayloadLength;
   REINTERPRET(sendPacket, instance->sendReceiveBuffer, SendPacket_t *);

   Gea2PacketQueue_Peek(instance->send.packetQueue, (Gea2Packet_t * )sendPacket, &retries);

   if(!instance->send.inProgress)
   {
      instance->send.retries = retries;
   }

   packetPayloadLength = sendPacket->dataLength;

   sendPacket->dataLength = (uint8_t)(packetPayloadLength + PacketOverhead);
   instance->send.dataSize = (uint8_t)(packetPayloadLength + SendPacketHeaderSize);
   instance->send.crc = CalculateCrc(sendPacket, packetPayloadLength, instance->crc16Calculator);
}

static void PublishSendReadyIfPacketQueued(Gea2Interface_SingleWire_t *instance)
{
   if(Gea2PacketQueue_Count(instance->send.packetQueue))
   {
      Fsm_SendSignal(&instance->fsm, FSM_SEND_READY, NULL);
   }
}

static void State_Idle(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);

   switch(signal)
   {
      case FSM_ENTRY:
         if(Gea2PacketQueue_Count(instance->send.packetQueue))
         {
            Fsm_Transition(&instance->fsm, State_Send);
         }
         break;

      case FSM_BYTE_RECEIVED:
         {
         const uint8_t byte = *(const uint8_t *)data;

         if(GEA2_STX == byte)
         {
            Fsm_Transition(fsm, State_Receive);
         }
         else
         {
            Fsm_Transition(fsm, State_IdleCooldown);
         }
         break;
      }

      case FSM_SEND_READY:
         Fsm_Transition(fsm, State_Send);
         break;

      case FSM_EXIT:
         break;

      default:
         break;
   }
}

static void IdleTimeout(void *context)
{
   Gea2Interface_SingleWire_t *instance = context;
   Fsm_SendSignal(&instance->fsm, FSM_IDLE_TIMEOUT_COMPLETE, NULL);
}

static TimerTicks_t GetIdleTimeout(uint8_t address)
{
   return 10 + (address & 0x1F);
}

static void State_IdleCooldown(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);

   switch(signal)
   {
      case FSM_ENTRY:
         TimerModule_StartOneShot(&instance->timerModule, &instance->timer,
            GetIdleTimeout(instance->address), IdleTimeout, instance);
         break;

      case FSM_BYTE_RECEIVED:
         {
         const uint8_t byte = *(const uint8_t *)data;

         if(GEA2_STX == byte)
         {
            Fsm_Transition(fsm, State_Receive);
         }
         else
         {
            Fsm_Transition(fsm, State_IdleCooldown);
         }
         break;
      }

      case FSM_IDLE_TIMEOUT_COMPLETE:
         Fsm_Transition(fsm, State_Idle);
         break;

      case FSM_EXIT:
         TimerModule_Stop(&instance->timerModule, &instance->timer);
         break;

      default:
         break;
   }
}

static void CollisionTimeout(void *context)
{
   Gea2Interface_SingleWire_t *instance = context;
   Fsm_SendSignal(&instance->fsm, FSM_COLLISION_TIMEOUT_COMPLETE, NULL);
}

static TimerTicks_t GetCollisionTimeout(uint8_t address, uint8_t pseudoRandomNumber)
{
   return 43 + (address & 0x1F) + ((pseudoRandomNumber ^ address) & 0x1F);
}

static void StartCollisionTimeout(Gea2Interface_SingleWire_t *instance)
{
   uint8_t currentTicks = (uint8_t)TimeSource_GetTicks(instance->timeSource);
   TimerTicks_t collisionTimeoutTicks = GetCollisionTimeout(instance->address, currentTicks);
   TimerModule_StartOneShot(&instance->timerModule, &instance->timer, collisionTimeoutTicks, CollisionTimeout, instance);
}

static void State_CollisionCooldown(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);

   switch(signal)
   {
      case FSM_ENTRY:
         StartCollisionTimeout(instance);
         break;

      case FSM_BYTE_RECEIVED:
         {
         uint8_t byte = *((const uint8_t *)data);

         if(GEA2_STX == byte)
         {
            Fsm_Transition(fsm, State_Receive);
         }
         break;
      }

      case FSM_COLLISION_TIMEOUT_COMPLETE:
         Fsm_Transition(fsm, State_Idle);
         break;

      case FSM_EXIT:
         TimerModule_Stop(&instance->timerModule, &instance->timer);
         break;

      default:
         break;
   }
}

static void ReflectionTimeout(void *context)
{
   Gea2Interface_SingleWire_t *instance = context;
   Fsm_SendSignal(&instance->fsm, FSM_REFLECTION_TIMEOUT, NULL);
}

static bool NeedsEscape(uint8_t byte)
{
   switch(byte)
   {
      case GEA2_ESC:
         case GEA2_STX:
         case GEA2_ETX:
         case GEA2_ACK:
         return true;

      default:
         return false;
   }
}

// Returns true if the byte is to be sent, false if an escape is to be sent
static bool DetermineByteToSendConsideringEscapes(Gea2Interface_SingleWire_t *instance, uint8_t byte, uint8_t *byteToSend)
{
   if(!instance->send.escaping && NeedsEscape(byte))
   {
      instance->send.escaping = true;
      *byteToSend = GEA2_ESC;
   }
   else
   {
      instance->send.escaping = false;
      *byteToSend = byte;
   }

   return !instance->send.escaping;
}

static void SendNextByte(Gea2Interface_SingleWire_t *instance)
{
   uint8_t byteToSend;

   TimerModule_StartOneShot(&instance->timerModule, &instance->timer, GEA2_REFLECTION_TIMEOUT_MSEC, ReflectionTimeout, instance);

   switch(instance->send.state)
   {
      case SEND_STATE_STX:
         instance->send.dataIndex = 0;
         instance->send.state = SEND_STATE_DATA;
         byteToSend = GEA2_STX;
         break;

      case SEND_STATE_DATA:
         if(DetermineByteToSendConsideringEscapes(instance, instance->sendReceiveBuffer[instance->send.dataIndex], &byteToSend))
         {
            instance->send.dataIndex++;

            if(instance->send.dataIndex >= instance->send.dataSize)
            {
               instance->send.state = SEND_STATE_CRC_MSB;
            }
         }
         break;

      case SEND_STATE_CRC_MSB:
         if(DetermineByteToSendConsideringEscapes(instance, (uint8_t)(instance->send.crc >> 8), &byteToSend))
         {
            instance->send.state = SEND_STATE_CRC_LSB;
         }
         break;

      case SEND_STATE_CRC_LSB:
         if(DetermineByteToSendConsideringEscapes(instance, (uint8_t)(instance->send.crc & 0xFF), &byteToSend))
         {
            instance->send.state = SEND_STATE_ETX;
         }
         break;

      case SEND_STATE_ETX:
         instance->send.state = SEND_STATE_DONE;
         byteToSend = GEA2_ETX;
         break;

      default:
         uassert(!"We should never get here!");
         byteToSend = 0x00;
         break;
   }

   instance->send.expectedReflection = byteToSend;
   Uart_Send(instance->serial, byteToSend);
}

static void FinishSending(Gea2Interface_SingleWire_t *instance)
{
   Gea2PacketQueue_Dequeue(instance->send.packetQueue, (Gea2Packet_t * )instance->sendReceiveBuffer, &instance->send.retries);
   instance->send.inProgress = false;
}

static void HandleSendSuccess(Gea2Interface_SingleWire_t *instance)
{
   FinishSending(instance);
   Fsm_Transition(&instance->fsm, State_IdleCooldown);
}

static void HandleSendFailure(Gea2Interface_SingleWire_t *instance)
{
   if(instance->send.retries > 0)
   {
      instance->send.retries--;
   }
   else
   {
      FinishSending(instance);
   }

   Fsm_Transition(&instance->fsm, State_CollisionCooldown);
}

static void State_Send(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);
   (void)data;

   switch(signal)
   {
      case FSM_ENTRY:
         PrepareSendPacket(instance);

         instance->send.inProgress = true;
         instance->send.state = SEND_STATE_STX;
         instance->send.escaping = false;

         SendNextByte(instance);
         break;

      case FSM_BYTE_RECEIVED:
         {
         const uint8_t byte = *(const uint8_t *)data;

         if(instance->send.expectedReflection == byte)
         {
            if(SEND_STATE_DONE == instance->send.state)
            {
               SendPacket_t *sendPacket = (SendPacket_t *)instance->sendReceiveBuffer;

               if(IsBroadcastAddress(sendPacket->destination))
               {
                  HandleSendSuccess(instance);
               }
               else
               {
                  Fsm_Transition(fsm, State_WaitForAck);
               }
            }
            else
            {
               SendNextByte(instance);
            }
         }
         else
         {
            HandleSendFailure(instance);
         }
         break;
      }

      case FSM_SERIAL_ERROR:
         HandleSendFailure(instance);
         break;

      case FSM_REFLECTION_TIMEOUT:
         HandleSendFailure(instance);
         Fsm_Transition(fsm, State_IdleCooldown);
         break;

      case FSM_EXIT:
         TimerModule_Stop(&instance->timerModule, &instance->timer);
         break;

      default:
         break;
   }
}

static void AckTimeout(void *context)
{
   Gea2Interface_SingleWire_t *instance = context;
   Fsm_SendSignal(&instance->fsm, FSM_ACK_TIMEOUT, NULL);
}

static void StartAckTimeoutTimer(Gea2Interface_SingleWire_t *instance)
{
   TimerModule_StartOneShot(&instance->timerModule, &instance->timer, GEA2_ACK_TIMEOUT_MSEC, AckTimeout, instance);
}

static void State_WaitForAck(Fsm_t *fsm, FsmSignal_t signal, const void *data)
{
   Gea2Interface_SingleWire_t *instance = InterfaceFromFsm(fsm);

   switch(signal)
   {
      case FSM_ENTRY:
         StartAckTimeoutTimer(instance);
         break;

      case FSM_BYTE_RECEIVED:
         {
         const uint8_t byte = *((const uint8_t *)data);

         if(GEA2_ACK == byte)
         {
            HandleSendSuccess(instance);
         }
         else
         {
            HandleSendFailure(instance);
         }
         break;
      }

      case FSM_ACK_TIMEOUT:
         HandleSendFailure(instance);
         break;

      case FSM_EXIT:
         TimerModule_Stop(&instance->timerModule, &instance->timer);
         break;

      default:
         break;
   }
}

static uint8_t Address(I_Gea2Interface_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);
   return instance->address;
}

static uint8_t MaxPayloadLength(I_Gea2Interface_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);
   return instance->sendReceiveBufferSize + UnbufferedBytes - GEA2PACKET_TRANSMISSION_OVERHEAD;
}

static size_t SendQueueCount(I_Gea2Interface_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);
   return Gea2PacketQueue_Count(instance->send.packetQueue);
}

static void Send(I_Gea2Interface_t *_instance, const Gea2Packet_t *packet, const uint8_t retries)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);

   if(packet->payloadLength <= MaxPayloadLength(_instance))
   {
      Gea2PacketQueue_Enqueue(instance->send.packetQueue, packet, retries);
   }
}

static void SetAcceptDelegate(I_Gea2Interface_t *_instance, const Gea2InterfaceAcceptDelegate_t *delegate)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);
   instance->acceptDelegate = delegate;
}

static I_Event_t * GetOnReceiveEvent(I_Gea2Interface_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2Interface_SingleWire_t *);
   return &instance->OnReceive.interface;
}

static const I_Gea2Interface_Api_t interfaceApi =
   { Send, SetAcceptDelegate, Address, MaxPayloadLength, SendQueueCount, GetOnReceiveEvent };

static void SerialByteReceived(void *context, const void *args)
{
   REINTERPRET(instance, context, Gea2Interface_SingleWire_t *);
   REINTERPRET(onReceiveArgs, args, const UartOnReceiveArgs_t *);
   Fsm_SendSignal(&instance->fsm, FSM_BYTE_RECEIVED, &onReceiveArgs->byte);
}

static void SerialErrorOccurred(void *context, const void *args)
{
   REINTERPRET(instance, context, Gea2Interface_SingleWire_t *);
   IGNORE_ARG(args);
   Fsm_SendSignal(&instance->fsm, FSM_SERIAL_ERROR, NULL);
}

void Gea2Interface_SingleWire_Init(
   Gea2Interface_SingleWire_t *instance,
   I_Uart_t *serial,
   uint8_t address,
   uint8_t *sendReceiveBuffer,
   size_t sendReceiveBufferSize,
   I_TimeSource_t *timeSourceMsec,
   I_Gea2PacketQueue_t *sendPacketQueue,
   I_Crc16Calculator_t *crc16Calculator)
{
   uassert(sendReceiveBufferSize >= sizeof(Gea2Packet_t));
   uassert(!IsBroadcastAddress(address));
   uassert(sendReceiveBufferSize <= (UINT8_MAX - UnbufferedBytes));

   Event_Synchronous_Init(&instance->OnReceive);

   instance->interface.api = &interfaceApi;
   instance->serial = serial;
   instance->address = address;
   instance->sendReceiveBuffer = sendReceiveBuffer;
   instance->sendReceiveBufferSize = (size_t)sendReceiveBufferSize;
   instance->receive.escaped = false;
   instance->crc16Calculator = crc16Calculator;
   instance->acceptDelegate = NULL;
   instance->send.inProgress = false;
   instance->timeSource = timeSourceMsec;
   instance->send.packetQueue = sendPacketQueue;

   Fsm_Init(&instance->fsm, State_Idle);
   TimerModule_Init(&instance->timerModule, timeSourceMsec);

   EventSubscription_Init(&instance->onReceiveSubscription, instance, SerialByteReceived);
   Event_Subscribe(Uart_GetOnReceiveEvent(serial), &instance->onReceiveSubscription);

   EventSubscription_Init(&instance->onErrorSubscription, instance, SerialErrorOccurred);
   Event_Subscribe(Uart_GetOnErrorEvent(serial), &instance->onErrorSubscription);

   // If this isn't satisfied then it's possible that we can overrun our send buffer on dequeue
   uassert(Gea2PacketQueue_MaxPayloadLength(instance->send.packetQueue) <= MaxPayloadLength(&instance->interface));
}

void Gea2Interface_SingleWire_Run(Gea2Interface_SingleWire_t *instance)
{
   PublishSendReadyIfPacketQueued(instance);
   (void)TimerModule_Run(&instance->timerModule);
}
