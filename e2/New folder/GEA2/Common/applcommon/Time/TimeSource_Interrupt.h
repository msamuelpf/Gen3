/*!
 * @file
 * @brief Time source using an interrupt tick to keep time.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef TIMESOURCE_INTERRUPT_H
#define TIMESOURCE_INTERRUPT_H

#include "I_TimeSource.h"
#include "I_Interrupt.h"

typedef struct
{
   I_TimeSource_t interface;

   struct
   {
      TimeSourceTickCount_t tickCount;
      EventSubscription_t interruptEventSubscription;
   } _private;
} TimeSource_Interrupt_t;

/*!
 * Initialize an interrupt-driven time source.  The time source tick count will be zero after init.
 * @param instance The time source.
 * @param interrupt The interrupt to use as the 'tick'.
 */
void TimeSource_Interrupt_Init(TimeSource_Interrupt_t *instance, I_Interrupt_t *interrupt);

#endif
