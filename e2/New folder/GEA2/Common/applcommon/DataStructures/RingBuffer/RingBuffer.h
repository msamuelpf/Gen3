/*!
 * @file
 * @brief Generic ring buffer.
 *
 * This is multi-context-safe if never allowed to be full and one context feeds (adds) while the other
 * consumes (removes).  This means the ring buffer is suitable to transfer data between contexts without
 * other context-protection.  Note that Init and Clear overwrite the entire state state of the ring
 * buffer and should not be called when the ring buffer is being accessed by more than one context
 * without other protection.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/*!
 * Ring buffer.  Struct members should be considered private.
 */
typedef struct
{
   uint8_t *buffer;
   unsigned capacity;
   unsigned elementSize;
   unsigned head;
   unsigned tail;
   bool full;
} RingBuffer_t;

/*!
 * Initialize a ring buffer.
 * @pre capacity > 0
 * @pre elementSize > 0
 * @param rbuf The ring buffer.
 * @param buffer Pre-allocated storage buffer that the ring buffer will use.
 * @param capacity The number of elements that can fit in the pre-allocated buffer.
 * @param elementSize The size of each element (in bytes).
 */
void RingBuffer_Init(RingBuffer_t *rbuf, void *buffer, const unsigned capacity, const unsigned elementSize);

/*!
 * Add an element to the ring buffer. If the ring buffer is full, the new element will overwrite the oldest element.
 * @param rbuf The ring buffer.
 * @param element The element to add.
 */
void RingBuffer_Add(RingBuffer_t *rbuf, const void *element);

/*!
 * Remove an element from the ring buffer.
 * @pre Count(rbuf) > 0
 * @param rbuf The ring buffer.
 * @param element Storage for the removed item.
 */
void RingBuffer_Remove(RingBuffer_t *rbuf, void *element);

/*!
 * Similar to Remove but the element is not retrieved.
 * @pre Count(rbuf) > 0
 * @param rbuf The ring buffer.
 */
void RingBuffer_Discard(RingBuffer_t *rbuf);

/*!
 * Access the element at a specific index.  Indices are numbered oldest to newest.
 * @pre 0 < index < Count(rbuf)
 * @param rbuf The ring buffer.
 * @param element The accessed element will be copied here.
 * @param index The index to access.
 */
void RingBuffer_At(const RingBuffer_t *rbuf, void *element, const unsigned index);

/*!
 * Get the number of items currently stored in the ring buffer.
 * @param rbuf The ring buffer.
 * @return The number of items currently stored in the ring buffer.
 */
unsigned RingBuffer_Count(const RingBuffer_t *rbuf);

/*!
 * Get the maximum capacity of the ring buffer.
 * @param rbuf The ring buffer.
 * @return The capacity of the ring buffer.
 */
unsigned RingBuffer_Capacity(const RingBuffer_t *rbuf);

/*!
 * Reset a ring buffer so that it contains 0 items.
 * @param rbuf The ring buffer.
 */
void RingBuffer_Clear(RingBuffer_t *rbuf);

#endif
