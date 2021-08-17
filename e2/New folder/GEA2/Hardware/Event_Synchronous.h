/*!
 * @file
 * @brief Simple synchronous implementation of an event. Only guarantees correct operation when the
 * currently-being-published-to subscriber unsubscribes during publication.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef EVENT_SYNCHRONOUS_H
#define EVENT_SYNCHRONOUS_H

#include "I_Event.h"
#include "LinkedList.h"

typedef struct
{
   I_Event_t interface;

   struct
   {
      LinkedList_t subscriptionList;
   } _private;
} Event_Synchronous_t;

/*!
 * Initialize a event.
 * @param instance The event.
 */
void Event_Synchronous_Init(Event_Synchronous_t *instance);

/*!
 * Publish to the current subscription list.
 * @param instance The event.
 * @param args Event specific arguments.
 */
void Event_Synchronous_Publish(Event_Synchronous_t *instance, const void *args);

#endif
