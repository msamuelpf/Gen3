/*!
 * @file
 * @brief Implementation of no-frills packet-based data source subscription manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "DataSourcePacketSubscriptionManager_Simple.h"
#include "uassert.h"
#include "utils.h"

#define MAGICAL_REMOVE_ALL_SUBSCRIPTIONS_ERD (0xFFFF)

typedef DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t SubscriptionListItem_t;

enum
{
   SubscriptionStatus_Clean,
   SubscriptionStatus_Dirty,
   SubscriptionStatus_StagedForPublication,
   SubscriptionStatus_Max
};
typedef uint8_t SubscriptionStatus_t;

static SubscriptionListItem_t * FindSubscriptionListItemForSubscription(
   DataSourcePacketSubscriptionManager_Simple_t *instance,
   uint8_t subscriberId,
   Erd_t erd)
{
   uint8_t i;

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if(item->status.inUse &&
         (item->subscriberId == subscriberId) &&
         (item->erd == erd))
      {
         return item;
      }
   }

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if(false == item->status.inUse)
      {
         return item;
      }
   }

   return NULL;
}

static bool AddSubscription(
   I_DataSourcePacketSubscriptionManager_t *_instance,
   const uint8_t subscriberId,
   const Erd_t erd,
   const uint8_t subscriptionTime)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionManager_Simple_t *);

   SubscriptionListItem_t *availableItem = FindSubscriptionListItemForSubscription(instance, subscriberId, erd);

   bool validErd = DataSource_Has(instance->_private.dataSource, erd);

   IGNORE_ARG(subscriptionTime);

   if(availableItem && validErd)
   {
      availableItem->status.inUse = true;
      availableItem->subscriberId = subscriberId;
      availableItem->erd = erd;
      availableItem->status.subscriptionStatus = SubscriptionStatus_Dirty;
      availableItem->status.missedAckCount = 0;

      return true;
   }

   return false;
}

static bool RemoveAllSubscriptionsForSubscriber(
   DataSourcePacketSubscriptionManager_Simple_t *instance,
   uint8_t subscriberId)
{
   bool removedAny = false;
   uint8_t i;

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if(item->status.inUse && (item->subscriberId == subscriberId))
      {
         item->status.inUse = false;
         removedAny = true;
      }
   }

   return removedAny;
}

static bool RemoveSubscription(I_DataSourcePacketSubscriptionManager_t *_instance, uint8_t subscriberId, Erd_t erd)
{
   bool removedAny = false;

   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionManager_Simple_t *);

   if(erd == MAGICAL_REMOVE_ALL_SUBSCRIPTIONS_ERD)
   {
      removedAny = RemoveAllSubscriptionsForSubscriber(instance, subscriberId);
   }
   else
   {
      uint8_t i;

      for(i = 0; i < instance->_private.subscriptionListLength; i++)
      {
         SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

         if((subscriberId == item->subscriberId) &&
            (erd == item->erd) &&
            (item->status.inUse))
         {
            item->status.inUse = false;
            removedAny = true;
         }
      }
   }

   return removedAny;
}

static void ResetMissedAckCountsForSubscriber(DataSourcePacketSubscriptionManager_Simple_t *instance, uint8_t subscriberId)
{
   uint8_t i;
   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if(item->subscriberId == subscriberId)
      {
         item->status.missedAckCount = 0;
      }
   }
}

static void NotifyPublishResponse(I_DataSourcePacketSubscriptionManager_t *_instance, uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionManager_Simple_t *);
   ResetMissedAckCountsForSubscriber(instance, subscriberId);
}

static void GetSubscriptionList(
   I_DataSourcePacketSubscriptionManager_t *_instance,
   DataSourcePacketSubscriptionManagerGetSubscriptionListForEachCallback_t callback,
   void *context,
   uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionManager_Simple_t *);
   uint8_t i;

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if((item->subscriberId == subscriberId) && (item->status.inUse))
      {
         callback(context, item->erd, 0);
      }
   }
}

static void StageAllDirtySubscriptionsForPublication(DataSourcePacketSubscriptionManager_Simple_t *instance)
{
   uint8_t i;
   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if(item->status.subscriptionStatus == SubscriptionStatus_Dirty)
      {
         item->status.subscriptionStatus = SubscriptionStatus_StagedForPublication;
      }
   }
}

static bool AnySubscriptionsStagedForPublication(DataSourcePacketSubscriptionManager_Simple_t *instance)
{
   uint8_t i;
   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if((item->status.inUse) &&
         (item->status.subscriptionStatus == SubscriptionStatus_StagedForPublication))
      {
         return true;
      }
   }

   return false;
}

static bool ServiceSubscriptions(
   I_DataSourcePacketSubscriptionManager_t *_instance,
   DataSourcePacketSubscriptionManagerServiceSubscriptionsForEachCallback_t callback,
   void *context,
   uint8_t *subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionManager_Simple_t *);
   bool published = false;
   bool foundSubscriber = false;
   uint8_t i;

   if(!AnySubscriptionsStagedForPublication(instance))
   {
      StageAllDirtySubscriptionsForPublication(instance);
   }

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];
      bool stagedForPublication = (bool)(item->status.subscriptionStatus == SubscriptionStatus_StagedForPublication);
      bool dirty = (bool)(item->status.subscriptionStatus == SubscriptionStatus_Dirty);
      bool readyForPublish = (bool)(stagedForPublication || (dirty && foundSubscriber));
      bool validSubscriber = (bool)(!foundSubscriber || item->subscriberId == *subscriberId);

      if(item->status.inUse && readyForPublish && validSubscriber)
      {
         if(callback(context, instance->_private.subscriptionList[i].erd, instance->_private.dataSource))
         {
            instance->_private.subscriptionList[i].status.subscriptionStatus = SubscriptionStatus_Clean;
            *subscriberId = instance->_private.subscriptionList[i].subscriberId;
            foundSubscriber = true;
            published = true;
         }
      }
   }

   return published;
}

static const I_DataSourcePacketSubscriptionManager_Api_t api =
   { AddSubscription, RemoveSubscription, NotifyPublishResponse, GetSubscriptionList, ServiceSubscriptions };

static void DataChanged(void *context, const void *_eventArgs)
{
   REINTERPRET(eventArgs, _eventArgs, const DataSourceOnDataChangeArgs_t *);
   REINTERPRET(instance, context, DataSourcePacketSubscriptionManager_Simple_t *);

   uint8_t i;

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      SubscriptionListItem_t *item = &instance->_private.subscriptionList[i];

      if((item->status.inUse) &&
         (item->erd == eventArgs->erd) &&
         (item->status.subscriptionStatus == SubscriptionStatus_Clean))
      {
         if(item->status.missedAckCount < instance->_private.missedAckLimit)
         {
            item->status.missedAckCount++;
            item->status.subscriptionStatus = SubscriptionStatus_Dirty;
         }
         else
         {
            RemoveAllSubscriptionsForSubscriber(instance, item->subscriberId);
         }
      }
   }
}

static bool MissedAckLimitWithinBounds(uint8_t missedAckLimit)
{
   SubscriptionListItem_t listItem;
   listItem.status.missedAckCount = missedAckLimit;
   return (bool)(listItem.status.missedAckCount == missedAckLimit);
}

static void RemoveAllSubscriptions(DataSourcePacketSubscriptionManager_Simple_t *instance)
{
   uint8_t i;

   for(i = 0; i < instance->_private.subscriptionListLength; i++)
   {
      instance->_private.subscriptionList[i].status.inUse = false;
   }
}

void DataSourcePacketSubscriptionManager_Simple_Init(
   DataSourcePacketSubscriptionManager_Simple_t *instance,
   I_DataSource_t *dataSource,
   DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t *subscriptionList,
   const uint8_t subscriptionListLength,
   const uint8_t missedAckLimit)
{
   uassert(missedAckLimit >= 10);
   uassert(MissedAckLimitWithinBounds(missedAckLimit));

   instance->interface.api = &api;

   instance->_private.dataSource = dataSource;
   instance->_private.subscriptionList = subscriptionList;
   instance->_private.subscriptionListLength = subscriptionListLength;
   instance->_private.missedAckLimit = missedAckLimit;

   RemoveAllSubscriptions(instance);

   EventSubscription_Init(&instance->_private.dataChangedSubscription, instance, DataChanged);
   Event_Subscribe(dataSource->OnDataChange, &instance->_private.dataChangedSubscription);
}
