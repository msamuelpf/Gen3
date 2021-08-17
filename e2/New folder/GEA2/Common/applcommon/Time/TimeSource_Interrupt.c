/*!
 * @file
 * @brief Implementation of interrupt-driven time source.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "TimeSource_Interrupt.h"
#include "EventSubscription.h"
#include "uassert.h"
#include "utils.h"

static TimeSourceTickCount_t GetTicks(I_TimeSource_t *_instance)
{
   REINTERPRET(instance, _instance, TimeSource_Interrupt_t *);

   TimeSourceTickCount_t last;
   TimeSourceTickCount_t current;

   current = instance->_private.tickCount;

   // Note: this provides interrupt-safety and means that we do not ever have to disable interrupts.
   // Keep reading the tick count until it reads the same two times in a row so that we know the value
   // is correct.
   // Unless the interrupt is coming so fast that the few cycles of the loop don't guarantee that we
   // can do two reads without the ISR coming this will work.  If the interrupt comes so fast that we
   // can't execute a few cycles in between invocations then we have a bigger problem.
   do
   {
      last = current;
      current = instance->_private.tickCount;
   } while(last != current);

   return current;
}

static const I_TimeSource_Api_t api =
   { GetTicks };

static void InterruptCallback(void *_instance, const void *args)
{
   REINTERPRET(instance, _instance, TimeSource_Interrupt_t *);
   IGNORE_ARG(args);
   instance->_private.tickCount++;
}

void TimeSource_Interrupt_Init(TimeSource_Interrupt_t *instance, I_Interrupt_t *interrupt)
{
   instance->interface.api = &api;
   instance->_private.tickCount = 0;

   EventSubscription_Init(&instance->_private.interruptEventSubscription, instance, InterruptCallback);
   Event_Subscribe(interrupt->OnInterrupt, &instance->_private.interruptEventSubscription);
}
