/*!
 * @file
 * @brief Implementation of efficient storage Gea2PacketQueue.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "Gea2PacketQueue_EfficientStorage.h"
#include "uassert.h"
#include "utils.h"

// Keeps a single uint8_t for payload length
#define QUEUE_HEADER_SIZE (1)
#define RETRY_SIZE (1)

static void Enqueue(I_Gea2PacketQueue_t *_instance, const Gea2Packet_t *packet, const uint8_t retries)
{
   REINTERPRET(instance, _instance, Gea2PacketQueue_EfficientStorage_t *);
   uint16_t index;
   size_t finalUsedStorage;

   uassert(packet->payloadLength <= instance->_private.maxPayloadLength);

   finalUsedStorage = RingBuffer_Count(&instance->_private.ringBuffer) + packet->payloadLength +
   GEA2PACKET_OVERHEAD + QUEUE_HEADER_SIZE + RETRY_SIZE;

   if(finalUsedStorage <= RingBuffer_Capacity(&instance->_private.ringBuffer))
   {
      RingBuffer_Add(&instance->_private.ringBuffer, &packet->payloadLength);

      for(index = 0; index < (uint16_t)(GEA2PACKET_OVERHEAD + packet->payloadLength); index++)
      {
         RingBuffer_Add(&instance->_private.ringBuffer, (const uint8_t *)packet + index);
      }

      RingBuffer_Add(&instance->_private.ringBuffer, &retries);

      instance->_private.count++;
   }
}

static void Dequeue(I_Gea2PacketQueue_t *_instance, Gea2Packet_t *packet, uint8_t *retries)
{
   REINTERPRET(instance, _instance, Gea2PacketQueue_EfficientStorage_t *);
   uint16_t index;
   uint8_t payloadLength;

   RingBuffer_Remove(&instance->_private.ringBuffer, &payloadLength);

   for(index = 0; index < (uint16_t)(GEA2PACKET_OVERHEAD + payloadLength); index++)
   {
      RingBuffer_Remove(&instance->_private.ringBuffer, (uint8_t *)packet + index);
   }

   RingBuffer_Remove(&instance->_private.ringBuffer, retries);

   instance->_private.count--;
}

static void Peek(I_Gea2PacketQueue_t *_instance, Gea2Packet_t *packet, uint8_t *retries)
{
   REINTERPRET(instance, _instance, Gea2PacketQueue_EfficientStorage_t *);
   uint16_t index;
   uint8_t payloadLength;

   RingBuffer_At(&instance->_private.ringBuffer, &payloadLength, 0);

   for(index = 0; index < (uint16_t)(GEA2PACKET_OVERHEAD + payloadLength); index++)
   {
      RingBuffer_At(&instance->_private.ringBuffer, (uint8_t *)packet + index, index + 1);
   }

   RingBuffer_At(&instance->_private.ringBuffer, retries, index + 1);
}

static size_t Count(I_Gea2PacketQueue_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2PacketQueue_EfficientStorage_t *);
   return instance->_private.count;
}

static uint8_t MaxPayloadLength(I_Gea2PacketQueue_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2PacketQueue_EfficientStorage_t *);
   return instance->_private.maxPayloadLength;
}

static const I_Gea2PacketQueue_Api_t api =
   {
      .Enqueue = Enqueue,
      .Dequeue = Dequeue,
      .Peek = Peek,
      .Count = Count,
      .MaxPayloadLength = MaxPayloadLength
   };

void Gea2PacketQueue_EfficientStorage_Init(
   Gea2PacketQueue_EfficientStorage_t *instance,
   void *storage,
   const unsigned storageSize,
   uint8_t maxPayloadLength)
{
   instance->interface.api = &api;
   instance->_private.count = 0;
   instance->_private.maxPayloadLength = maxPayloadLength;

   RingBuffer_Init(&instance->_private.ringBuffer, storage, storageSize, sizeof(uint8_t));
}
