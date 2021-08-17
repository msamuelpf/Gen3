/*!
 * @file
 * @brief Subscription for generic events.
 *
 * Event subscriptions are linked list nodes that allow event implementations to store their subscriptions
 * in linked lists (so that they don't need to know the number of subscribers beforehand).
 *
 * Event subscriptions also capture a context pointer that will be provided to the subscription callback
 * when the subscription is published to.  This is useful for providing an object pointer (ie: 'this'
 * in C++) to the callback.
 *
 * @warning Note that subscriptions can only be used to subscribe to one event at a time.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef EVENTSUBSCRIPTION_H
#define EVENTSUBSCRIPTION_H

#include "LinkedList.h"

/*!
 * Callback used for subscription publish.
 */
typedef void (*EventSubscriptionCallback_t)(void *context, const void *args);

/*!
 * Event subscription.  Struct members should be considered private.
 */
typedef struct
{
   struct
   {
      LinkedListNode_t node;
      void *context;
      EventSubscriptionCallback_t callback;
   }_private;
} EventSubscription_t;

/*!
 * Initialize a subscription.
 * @pre instance != NULL
 * @pre callback != NULL
 * @param instance The subscription.
 * @param context Callback context.
 * @param callback Callback for publish.
 */
void EventSubscription_Init(EventSubscription_t *instance, void *context, EventSubscriptionCallback_t callback);

/*!
 * Publish a subscription.
 * @pre instance != NULL
 * @param instance The subscription.
 * @param args Pointer to event specific data.
 */
void EventSubscription_Publish(const EventSubscription_t *instance, const void *args);

#endif
