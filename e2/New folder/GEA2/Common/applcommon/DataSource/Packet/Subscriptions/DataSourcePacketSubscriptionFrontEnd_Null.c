/*!
 * @file
 * @brief Null implementation of the DataSourcePacketSubscriptionFrontEnd that does not support subscriptions
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "DataSourcePacketSubscriptionFrontEnd_Null.h"
#include "utils.h"
#include "DataSourcePacketBuilder.h"
#include "uassert.h"

static void SubscribeRequest(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   const void *request,
   void *responseBuffer,
   const uint8_t responseBufferSize,
   uint8_t *responseSize,
   const uint8_t subscriberId)
{
   DataSourcePacketBuilder_t builder;
   IGNORE(_instance);
   IGNORE(request);
   IGNORE(subscriberId);

   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);
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
   REINTERPRET(unsubscribed, responseBuffer, bool *);
   IGNORE(_instance);
   IGNORE(request);
   IGNORE(subscriberId);

   uassert(responseBufferSize > 0);

   *unsubscribed = false;
   *responseSize = 1;
}

static void ListRequest(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   void *responseBuffer,
   const uint8_t responseBufferSize,
   uint8_t *responseSize,
   const uint8_t subscriberId)
{
   DataSourcePacketBuilder_t builder;
   IGNORE(_instance);
   IGNORE(subscriberId);

   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);
   *responseSize = DataSourcePacketBuilder_GetSize(&builder);
}

static void PublishAcknowledge(I_DataSourcePacketSubscriptionFrontEnd_t *_instance, const uint8_t subscriberId)
{
   IGNORE(_instance);
   IGNORE(subscriberId);
}

static bool ServiceSubscriptions(
   I_DataSourcePacketSubscriptionFrontEnd_t *_instance,
   void *publishBuffer,
   const uint8_t publishBufferSize,
   uint8_t *publishSize,
   uint8_t *subscriberId)
{
   IGNORE(_instance);
   IGNORE(publishBuffer);
   IGNORE(publishBufferSize);
   IGNORE(publishSize);
   IGNORE(subscriberId);

   return false;
}

static const I_DataSourcePacketSubscriptionFrontEnd_Api_t api =
   { SubscribeRequest, UnsubscribeRequest, ListRequest, PublishAcknowledge, ServiceSubscriptions };

I_DataSourcePacketSubscriptionFrontEnd_t * DataSourcePacketSubscriptionFrontEnd_Null_GetInstance(void)
{
   static I_DataSourcePacketSubscriptionFrontEnd_t instance;
   instance.api = &api;
   return &instance;
}
