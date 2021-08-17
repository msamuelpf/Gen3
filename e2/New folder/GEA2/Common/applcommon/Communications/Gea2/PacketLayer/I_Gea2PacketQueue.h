/*!
 * @file
 * @brief GEA2 packet FIFO queue interface. Packets are queued only when there is enough available space
 * in the packet queue, otherwise they are discarded.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_GEA2PACKETQUEUE_H
#define I_GEA2PACKETQUEUE_H

#include <stddef.h>
#include "Gea2Packet.h"

struct I_Gea2PacketQueue_Api_t;

typedef struct
{
   const struct I_Gea2PacketQueue_Api_t *api;
} I_Gea2PacketQueue_t;

typedef struct I_Gea2PacketQueue_Api_t
{
   /*!
    * Enqueue a packet.
    * @param instance The queue.
    * @param packet The packet to enqueue.
    * @param retries The number of retries associated with the packet.
    */
   void (*Enqueue)(I_Gea2PacketQueue_t *instance, const Gea2Packet_t *packet, const uint8_t retries);

   /*!
    * Dequeue a packet.
    * @pre Count(instance) > 0
    * @pre packet can fit MaxPayloadLength(instance)
    * @param instance The queue.
    * @param packet Storage for the dequeued packet.
    * @param retries Storage for the dequeued retry count.
    */
   void (*Dequeue)(I_Gea2PacketQueue_t *instance, Gea2Packet_t *packet, uint8_t *retries);

   /*!
    * Peek a packet. This is identical to dequeue except that the packet remains in the queue.
    * @pre Count(instance) > 0
    * @pre packet can fit MaxPayloadLength(instance)
    * @param instance The queue.
    * @param packet Storage for the dequeued packet.
    * @param retries Storage for the dequeued retry count.
    */
   void (*Peek)(I_Gea2PacketQueue_t *instance, Gea2Packet_t *packet, uint8_t *retries);

   /*!
    * Get the number of packets in the queue.
    * @param instance The queue.
    * @return The number of packets currently queued.
    */
   size_t (*Count)(I_Gea2PacketQueue_t *instance);

   /*!
    * Get the max payload length of a queue-able packet.
    * @param instance The queue.
    * @return The max payload length of a queue-able packet.
    */
   uint8_t (*MaxPayloadLength)(I_Gea2PacketQueue_t *instance);
} I_Gea2PacketQueue_Api_t;

#define Gea2PacketQueue_Enqueue(instance, packet, retries) \
   (instance)->api->Enqueue((instance), (packet), (retries))

#define Gea2PacketQueue_Dequeue(instance, packet, retries) \
   (instance)->api->Dequeue((instance), (packet), (retries))

#define Gea2PacketQueue_Peek(instance, packet, retries) \
   (instance)->api->Peek((instance), (packet), (retries))

#define Gea2PacketQueue_Count(instance) \
   (instance)->api->Count((instance))

#define Gea2PacketQueue_MaxPayloadLength(instance) \
   (instance)->api->MaxPayloadLength((instance))

#endif
