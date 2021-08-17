/*!
 * @file
 * @brief Single wire GEA2 bus.
 *
 * @warning Please note that everything in this implementation except for Init() must be run in the
 * same context or be surrounded in a context protect (ie: disabling interrupts and then restoring).
 * This includes all UART calls, TimeSource ticking, and the Run() method.
 *
 * It is recommended that interrupt-safety be achieved by implementing a context-protected GEA2
 * interface wrapper with a buffer for received messages, ticking the time source from an ISR, and
 * context-protectign calls to Run().
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2INTERFACE_SINGLEWIRE_H
#define GEA2INTERFACE_SINGLEWIRE_H

#include <stddef.h>
#include "Timer.h"
#include "I_TimeSource.h"
#include "I_Gea2Interface.h"
#include "I_Uart.h"
#include "Gea2Packet.h"
#include "I_Gea2PacketQueue.h"
#include "Fsm.h"
#include "I_Crc16Calculator.h"
#include "Event_Synchronous.h"

enum
{
   // Destination, data length, source
   Gea2Interface_SingleWireSendBufferOverhead = 3,

   // STX, ETX
   Gea2Interface_SingleWireUnbufferedBytes = 2,

   Gea2Interface_SingleWireMaxSendReceiveBufferSize = 253
};

typedef struct
{
   I_Gea2Interface_t interface;
   Fsm_t fsm;
   uint8_t address;
   I_Uart_t *serial;
   I_TimeSource_t *timeSource;
   const Gea2InterfaceAcceptDelegate_t *acceptDelegate;
   I_Crc16Calculator_t *crc16Calculator;
   TimerModule_t timerModule;
   EventSubscription_t onReceiveSubscription;
   EventSubscription_t onErrorSubscription;
   Timer_t timer;

   struct
   {
      I_Gea2PacketQueue_t *packetQueue;
      Crc16_t crc;
      uint8_t dataIndex;
      uint8_t dataSize;
      uint8_t expectedReflection;
      uint8_t retries;
      bool inProgress :1;
      bool escaping :1;
      uint8_t state :3;
   } send;

   struct
   {
      uint8_t count;
      bool escaped;
      Crc16_t crc;
   } receive;

   uint8_t *sendReceiveBuffer;
   uint8_t sendReceiveBufferSize;

   Event_Synchronous_t OnReceive;
} Gea2Interface_SingleWire_t;

/*!
 * Initialize a simple GEA2 interface.
 * @pre sendReceiveBufferSize >= sizeof(Gea2Packet_t)
 * @pre sendReceiveBufferSize <= Gea2Interface_SingleWireMaxSendReceiveBufferSize
 * @pre !IsBroadcastAddress(address)
 * @param interface The GEA2 interface.
 * @param uart The UART to use. Note that this UART must be configured for 19200 bps. Note also
 *    that this UART does not need to implement Uart::SetTransmitNotifier().
 * @param address Primary address.
 * @param sendReceiveBuffer Buffer used for sending and receiving packets.
 * @param sendReceiveBufferSize Size of the buffer used to hold in progress packets (sent or received).
 * @param timeSourceMsec Millisecond time source to use for bus timing.
 * @param sendPacketQueue
 * @param crc16Calculator CRC16 calculator used to perform CRC checks.
 */
void Gea2Interface_SingleWire_Init(
   Gea2Interface_SingleWire_t *interface,
   I_Uart_t *uart,
   uint8_t address,
   uint8_t *sendReceiveBuffer,
   size_t sendReceiveBufferSize,
   I_TimeSource_t *timeSourceMsec,
   I_Gea2PacketQueue_t *sendPacketQueue,
   I_Crc16Calculator_t *crc16Calculator);

/*!
 * "Tick" the GEA2 interface to allow it to manage timed events.
 * @pre interface != NULL
 * @param interface The GEA2 interface.
 */
void Gea2Interface_SingleWire_Run(Gea2Interface_SingleWire_t *interface);

#endif
