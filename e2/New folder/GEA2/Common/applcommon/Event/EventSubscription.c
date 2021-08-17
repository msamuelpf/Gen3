/*!
 * @file
 * @brief Subscription for a generic event.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "uassert.h"
#include "EventSubscription.h"

void EventSubscription_Init(EventSubscription_t *instance, void *context, EventSubscriptionCallback_t callback)
{
   uassert(callback);

   instance->_private.callback = callback;
   instance->_private.context = context;
}

void EventSubscription_Publish(const EventSubscription_t *instance, const void *args)
{
   instance->_private.callback(instance->_private.context, args);
}
