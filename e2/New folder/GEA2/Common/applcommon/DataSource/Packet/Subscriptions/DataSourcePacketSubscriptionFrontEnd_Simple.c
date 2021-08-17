/*!
 * @file
 * @brief Implementation of the no-frills version of a front end for a packet-based data source subscription manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdbool.h>
#include "DataSourcePacketSubscriptionFrontEnd_Simple.h"
#include "DataSourcePacketParser.h"
#include "DataSourcePacketBuilder.h"
#include "uassert.h"
#include "utils.h"

static void SubscribeRequest(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   const void *request,
   void *responseBuffer,
   const uint8_t responseBufferSize,
   uint8_t *responseSize,
   const uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionFrontEnd_Simple_t *);
   DataSourcePacketParser_t parser;
   DataSourcePacketBuilder_t builder;
   Erd_t erd;
   uint8_t subscriptionTime;

   DataSourcePacketParser_Init(&parser, request);
   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);

   while(DataSourcePacketParser_ExtractSubscriptionItem(&parser, &erd, &subscriptionTime))
   {
      if(DataSourcePacketSubscriptionManager_AddSubscription(instance->_private.subscriptionManager, subscriberId, erd, subscriptionTime))
      {
         DataSourcePacketBuilder_AddErd(&builder, erd);
      }
   }

   *responseSize = DataSourcePacketBuilder_GetSize(&builder);
}

static void UnsubscribeRequest(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   const void *request,
   void *responseBuffer,
   const uint8_t responseBufferSize,
   uint8_t *responseSize,
   const uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionFrontEnd_Simple_t *);
   REINTERPRET(anyErdUnsubscribed, responseBuffer, bool *);
   DataSourcePacketParser_t parser;
   Erd_t erd;

   uassert(responseBufferSize > 0);

   DataSourcePacketParser_Init(&parser, request);

   *anyErdUnsubscribed = false;

   while(DataSourcePacketParser_ExtractErd(&parser, &erd))
   {
      *anyErdUnsubscribed |=
         DataSourcePacketSubscriptionManager_RemoveSubscription(instance->_private.subscriptionManager, subscriberId, erd);
   }

   *(uint8_t *)responseSize = 1;
}

static void ListRequestForEachCallback(void *context, Erd_t erd, uint8_t subscriptionTime)
{
   REINTERPRET(builder, context, DataSourcePacketBuilder_t *);
   DataSourcePacketBuilder_AddSubscriptionItem(builder, erd, subscriptionTime);
}

static void ListRequest(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   void *responseBuffer,
   const uint8_t responseBufferSize,
   uint8_t *responseSize,
   const uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionFrontEnd_Simple_t *);
   DataSourcePacketBuilder_t builder;

   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);

   DataSourcePacketSubscriptionManager_GetSubscriptionList(instance->_private.subscriptionManager,
      ListRequestForEachCallback, &builder, subscriberId);

   *responseSize = DataSourcePacketBuilder_GetSize(&builder);
}

static void PublishAcknowledge(I_DataSourcePacketSubscriptionFrontEnd_t *_instance, const uint8_t subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionFrontEnd_Simple_t *);
   DataSourcePacketSubscriptionManager_NotifyPublishResponse(instance->_private.subscriptionManager, subscriberId);
}

static bool ServiceSubscriptionsForEachCallback(void *context, Erd_t erd, I_DataSource_t *dataSource)
{
   REINTERPRET(instance, context, DataSourcePacketBuilder_t *);

   uint8_t dataSize = DataSource_SizeOf(dataSource, erd);
   void *reservedStorage;
   bool roomToAdd = DataSourcePacketBuilder_AddErdAndReserveStorageForData(instance, erd, dataSize, &reservedStorage);

   if(roomToAdd)
   {
      DataSource_Read(dataSource, erd, reservedStorage);
   }

   return roomToAdd;
}

static bool ServiceSubscriptions(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   void *publishBuffer,
   const uint8_t publishBufferSize,
   uint8_t *publishSize,
   uint8_t *subscriberId)
{
   REINTERPRET(instance, _instance, DataSourcePacketSubscriptionFrontEnd_Simple_t *);
   DataSourcePacketBuilder_t builder;
   bool published = false;

   DataSourcePacketBuilder_Init(&builder, publishBuffer, publishBufferSize);

   published = DataSourcePacketSubscriptionManager_ServiceSubscriptions(instance->_private.subscriptionManager,
      ServiceSubscriptionsForEachCallback, &builder, subscriberId);

   *publishSize = DataSourcePacketBuilder_GetSize(&builder);

   return published;
}

static const I_DataSourcePacketSubscriptionFrontEnd_Api_t api =
   { SubscribeRequest, UnsubscribeRequest, ListRequest, PublishAcknowledge, ServiceSubscriptions };

void DataSourcePacketSubscriptionFrontEnd_Simple_Init(DataSourcePacketSubscriptionFrontEnd_Simple_t *instance,
   I_DataSourcePacketSubscriptionManager_t *subscriptionManager)
{
   instance->interface.api = &api;
   instance->_private.subscriptionManager = subscriptionManager;
}
