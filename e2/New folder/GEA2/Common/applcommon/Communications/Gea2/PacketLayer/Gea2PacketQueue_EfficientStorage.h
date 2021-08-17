/*!
 * @file
 * @brief Gea2PacketQueue implementation that allows storage of variable-sized packets with efficient
 * storage use.  Allows many small packets of a few large packets to be stored.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2PACKETQUEUE_EFFICIENTSTORAGE_H
#define GEA2PACKETQUEUE_EFFICIENTSTORAGE_H

#include "I_Gea2PacketQueue.h"
#include "RingBuffer.h"

enum
{
   Gea2PacketQueue_EfficientStorageOverhead = GEA2PACKET_OVERHEAD + 2
};

/*!
 * Efficient storage packet queue.  Struct members should be considered private.
 */
typedef struct
{
   I_Gea2PacketQueue_t interface;

   struct
   {
      RingBuffer_t ringBuffer;
      size_t count;
      uint8_t maxPayloadLength;
   } _private;
} Gea2PacketQueue_EfficientStorage_t;

/*!
 * Initialize an efficient storage packet queue.
 * @pre instance != NULL
 * @pre storage != NULL
 * @param instance The queue.
 * @param storage The storage buffer used for queueing messages.
 * @param storageSize The size of the storage buffer.
 * @param maxPayloadLength The max payload length of a packet that will be queued.
 */
void Gea2PacketQueue_EfficientStorage_Init(
   Gea2PacketQueue_EfficientStorage_t *instance,
   void *storage,
   const unsigned storageSize,
   uint8_t maxPayloadLength);

#endif
