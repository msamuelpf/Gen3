/*!
 * @file
 * @brief Ring buffer implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include "RingBuffer.h"
#include "uassert.h"

// Context-safety requirements:
// -Full must never be true so requirements only need to be met for paths where full is false
// -Requirements do not need to be met for Init/Clear
// -Head can only be changed in Add
// -Tail can only be changed in Remove
// -Head and tail indices must be updated after the read/write has occurred
// -Head and tail should only be read once in each routine that doesn't 'own' the value (have sole write privileges)

void RingBuffer_Clear(RingBuffer_t *rbuf)
{
   uassert(rbuf);

   rbuf->full = false;
   rbuf->head = 0;
   rbuf->tail = 0;
}

void RingBuffer_Init(RingBuffer_t *rbuf, void *buffer, const unsigned capacity, const unsigned elementSize)
{
   uassert(rbuf);
   uassert(buffer);
   uassert(elementSize);
   uassert(capacity);

   rbuf->buffer = (uint8_t *)buffer;
   rbuf->elementSize = elementSize;
   rbuf->capacity = capacity;

   RingBuffer_Clear(rbuf);
}

void RingBuffer_Add(RingBuffer_t *rbuf, const void *element)
{
   uassert(rbuf);
   uassert(element);

   (void)memcpy(rbuf->buffer + rbuf->head * rbuf->elementSize, element, (size_t)rbuf->elementSize);

   if(!rbuf->full)
   {
      // Are we becoming full?
      if(((rbuf->head + 1) % rbuf->capacity) == rbuf->tail)
      {
         rbuf->full = true;
      }
   }
   else
   {
      // We're full and overwrote the last element, need to move tail forward to the new last element
      rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
   }

   // Must be last to be ISR-safe
   rbuf->head = (rbuf->head + 1) % rbuf->capacity;
}

void RingBuffer_At(const RingBuffer_t *rbuf, void *element, const unsigned index)
{
   void *from;

   uassert(rbuf);
   uassert(element);
   uassert(index < RingBuffer_Count(rbuf));

   from = rbuf->buffer + ((rbuf->tail + index) % rbuf->capacity) * rbuf->elementSize;
   (void)memcpy(element, from, (size_t)rbuf->elementSize);
}

void RingBuffer_Remove(RingBuffer_t *rbuf, void *element)
{
   RingBuffer_At(rbuf, element, 0);

   rbuf->full = false;
   rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
}

void RingBuffer_Discard(RingBuffer_t *rbuf)
{
   uassert(RingBuffer_Count(rbuf) > 0);

   rbuf->full = false;
   rbuf->tail = (rbuf->tail + 1) % rbuf->capacity;
}

unsigned RingBuffer_Count(const RingBuffer_t *rbuf)
{
   uassert(rbuf);

   if(rbuf->full)
   {
      return rbuf->capacity;
   }
   else
   {
      unsigned head = rbuf->head;
      unsigned tail = rbuf->tail;

      if(head >= tail)
      {
         return head - tail;
      }
      else
      {
         return rbuf->capacity - (tail - head);
      }
   }
}

unsigned RingBuffer_Capacity(const RingBuffer_t *rbuf)
{
   uassert(rbuf);

   return rbuf->capacity;
}
