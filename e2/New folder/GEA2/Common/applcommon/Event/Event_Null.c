/*!
 * @file
 * @brief Implementation of null event.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Event_Null.h"
#include "utils.h"

static void Subscribe(I_Event_t *instance, EventSubscription_t *subscription)
{
   IGNORE_ARG(instance);
   IGNORE_ARG(subscription);
}

static void Unsubscribe(I_Event_t *instance, EventSubscription_t *subscription)
{
   IGNORE_ARG(instance);
   IGNORE_ARG(subscription);
}

static const I_Event_Api_t api =
   { Subscribe, Unsubscribe };

I_Event_t * Event_Null_GetInstance(void)
{
   static I_Event_t instance = { &api };

   return &instance;
}
