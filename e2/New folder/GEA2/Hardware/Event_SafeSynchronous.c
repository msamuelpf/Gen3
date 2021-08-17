/*!
 * @file
 * @brief Safe synchronous event implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Event_SafeSynchronous.h"
#include "StackAllocator.h"
#include "uassert.h"
#include "utils.h"

static bool ForEach_PopulateSubscriptionArray(LinkedListNode_t *node, void *context, size_t index)
{
   REINTERPRET(subscriptionArray, context, EventSubscription_t **);
   REINTERPRET(subscription, node, EventSubscription_t *);

   subscriptionArray[index] = subscription;

   return true;
}

typedef struct
{
   Event_SafeSynchronous_t *instance;
   const void *args;
   size_t subscriberCount;
} PublishAllocationCallbackContext_t;

static void PublishAllocationCallback(void *_context, void *block)
{
   REINTERPRET(context, _context, PublishAllocationCallbackContext_t *);
   REINTERPRET(subscriptionArray, block, EventSubscription_t **);
   size_t i;

   LinkedList_ForEach(&context->instance->_private.subscriptionList, ForEach_PopulateSubscriptionArray, block);

   for(i = 0; i < context->subscriberCount; i++)
   {
      if(LinkedList_Contains(&context->instance->_private.subscriptionList, (LinkedListNode_t *)subscriptionArray[i]))
      {
         EventSubscription_Publish(subscriptionArray[i], context->args);
      }
   }
}

void Event_SafeSynchronous_Publish(Event_SafeSynchronous_t *instance, const void *args)
{
   PublishAllocationCallbackContext_t context;
   context.instance = instance;
   context.args = args;
   context.subscriberCount = LinkedList_Count(&instance->_private.subscriptionList);
   StackAllocator_AllocateAligned(sizeof(EventSubscription_t *) * context.subscriberCount, PublishAllocationCallback, &context);
}

static void Subscribe(I_Event_t *_instance, EventSubscription_t *subscription)
{
   REINTERPRET(instance, _instance, Event_SafeSynchronous_t *);

   if(false == LinkedList_Contains(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription))
   {
      LinkedList_PushFront(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription);
   }
}

static void Unsubscribe(I_Event_t *_instance, EventSubscription_t *subscription)
{
   REINTERPRET(instance, _instance, Event_SafeSynchronous_t *);
   LinkedList_Remove(&instance->_private.subscriptionList, (LinkedListNode_t *)subscription);
}

static const I_Event_Api_t api =
   { Subscribe, Unsubscribe };

void Event_SafeSynchronous_Init(Event_SafeSynchronous_t *instance)
{
   LinkedList_Init(&instance->_private.subscriptionList);
   instance->interface.api = &api;
}
