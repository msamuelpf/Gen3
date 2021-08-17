/*!
 * @file
 * @brief Safe synchronous event. Allows unrestricted subscribing/unsubscribing to event during publication. This
 * safety comes at a cost to stack usage and run time. This should only be used when necessary or when the number
 * of subscribers will be low.
 *
 * The stack cost of publication is sizeof(void *) * n
 *
 * The runtime complexity of publication is O(n^2)
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef EVENT_SAFESYNCHRONOUS_H
#define EVENT_SAFESYNCHRONOUS_H

#include "I_Event.h"
#include "LinkedList.h"

typedef struct
{
   I_Event_t interface;

   struct
   {
      LinkedList_t subscriptionList;
   } _private;
} Event_SafeSynchronous_t;

/*!
 * Initialize an event.
 * @param instance The event.
 */
void Event_SafeSynchronous_Init(Event_SafeSynchronous_t *instance);

/*!
 * Publish to the current subscription list.
 * @param instance The event.
 * @param args Event specific arguments.
 */
void Event_SafeSynchronous_Publish(Event_SafeSynchronous_t *instance, const void *args);

#endif
