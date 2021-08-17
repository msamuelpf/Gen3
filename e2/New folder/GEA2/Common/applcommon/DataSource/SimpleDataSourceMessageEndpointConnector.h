/*!
 * @file
 * @brief Component that takes a DataSource and a Gea2MessageEndpoint and creates all the
 * components necessary to connect them.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef SIMPLEDATASOURCEMESSAGEENDPOINTCONNECTOR_H
#define SIMPLEDATASOURCEMESSAGEENDPOINTCONNECTOR_H

#define SIMPLEDATASOURCEMESSAGEENDPOINTCONNECTOR_SUBSCRIPTIONLISTLENGTH 50

#include "I_DataSource.h"
#include "I_Gea2MessageEndpoint.h"
#include "DataSourcePacketReadWriteManager_Simple.h"
#include "DataSourcePacketSubscriptionFrontEnd_Simple.h"
#include "DataSourcePacketSubscriptionManager_Simple.h"
#include "DataSourcePacketGea2MessageEndpointConnector.h"
#include "Timer.h"

typedef struct
{
   struct
   {
      DataSourcePacketSubscriptionManager_Simple_t subscriptionManager;
      DataSourcePacketSubscriptionFrontEnd_Simple_t subscriptionFrontEnd;
      DataSourcePacketReadWriteManager_Simple_t readWriteManager;
      DataSourcePacketGea2MessageEndpointConnector_t connector;
      Timer_t messageEndpointTimer;
   } _private;
} SimpleDataSourceMessageEndpointConnector_t;

/*!
 * Initialize a SimpleDataSourceMessageEndpointConnector object
 * @pre numberOfSubscriptionItems != 0
 * @pre maxMessagePayloadSize <= GEA2MESSAGE_MAXPAYLOAD
 * @param instance The instance
 * @param dataSource the DataSource to connect to the Message Endpoint
 * @param messageEndpoint The Message Endpoint to connect to the DataSource
 * @param timerModule Timer Module to give runtime to the Gea2MessageEndpoint
 * @param subscriptionStorage Storage for subscriptions to be used by the SubscriptionManager
 * @param numberOfSubscriptionItems Number of elements in subscriptionStorage
 * @param maxMessagePayloadSize Maximum size of message payload
 */
void SimpleDataSourceMessageEndpointConnector_Init(
   SimpleDataSourceMessageEndpointConnector_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t *subscriptionStorage,
   uint8_t numberOfSubscriptionItems,
   uint8_t maxMessagePayloadSize);

#endif
