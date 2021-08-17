/*!
 * @file
 * @brief No-frills packet-based subscription manager for a data source.  Does not support subscription time.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETSUBSCRIPTIONMANAGER_SIMPLE_H
#define DATASOURCEPACKETSUBSCRIPTIONMANAGER_SIMPLE_H

#include "I_DataSourcePacketSubscriptionManager.h"
#include "I_DataSource.h"

typedef struct
{
   Erd_t erd;
   uint8_t subscriberId;
   struct
   {
      bool inUse :1;
      uint8_t subscriptionStatus :2;
      uint8_t missedAckCount :5;
   } status;
} DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t;

typedef struct
{
   I_DataSourcePacketSubscriptionManager_t interface;
   struct
   {
      I_DataSource_t *dataSource;
      DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t *subscriptionList;
      uint8_t subscriptionListLength;
      uint8_t missedAckLimit;
      EventSubscription_t dataChangedSubscription;
   } _private;
} DataSourcePacketSubscriptionManager_Simple_t;

/*!
 * Initialize a simple packet-based subscription manager for a data source.
 * @pre instance != NULL
 * @pre dataSource != NULL
 * @pre subscriptionList != NULL
 * @pre missedAckLimit < 2^5 - 1
 * @param instance The subscription manager.
 * @param dataSource The data source that will be subscribed to.
 * @param subscriptionList The storage for the subscription list.
 * @param subscriptionListLength The size of the provided subscription list storage.
 * @param missedAckLimit The number of missed ACKs that are allowed before a subscriber is unsubscribed.
 */
void DataSourcePacketSubscriptionManager_Simple_Init(
   DataSourcePacketSubscriptionManager_Simple_t *instance,
   I_DataSource_t *dataSource,
   DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t *subscriptionList,
   const uint8_t subscriptionListLength,
   const uint8_t missedAckLimit);

#endif
