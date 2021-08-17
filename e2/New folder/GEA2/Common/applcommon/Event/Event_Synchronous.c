/*!
 * @file
 * @brief Synchronous event implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdbool.h>
#include "Event_Synchronous.h"
#include "utils.h"

typedef struct
{
   const void *args;
} PublishContext_t;

static bool ForEach_Publish(LinkedListNode_t *node, void *context, const size_t index)
{
   EventSubscription_t *subscription = (EventSubscription_t *)node;
   REINTERPRET(publishContext, context, PublishContext_t *);
   IGNORE_ARG(index);

   EventSubscription_Publish(subscription, publishContext->args);

   return true;
}

void Event_Synchronous_Publish(Event_Synchronous_t *instance, const void *args)
{
   PublishContext_t publishContext;

   publishContext.args = args;

   LinkedList_ForEach(&instance->_private.subscriptionList, ForEach_Publish, &publishContext);
}

static void Subscribe(I_Event_t *_instance, EventSubscription_t *subscription)
{
   REINTERPRET(instance, _instance, Event_Synchronous_t *);

   if(false == LinkedList_Contains(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription))
   {
      LinkedList_PushFront(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription);
   }
}

static void Unsubscribe(I_Event_t *_instance, EventSubscription_t *subscription)
{
   REINTERPRET(instance, _instance, Event_Synchronous_t *);
   LinkedList_Remove(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription);
}

static const I_Event_Api_t api =
   { Subscribe, Unsubscribe };

void Event_Synchronous_Init(Event_Synchronous_t *instance)
{
   LinkedList_Init(&instance->_private.subscriptionList);
   instance->interface.api = &api;
}
