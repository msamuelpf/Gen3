/*!
 * @file
 * @brief Implementation of a DataSource to Gea2 Message Endpoint simple connector.
 *
 * Communications parameters are hard-coded in this implementation.
 * The Gea2MessageEndpointConnector component is given runtime via a Periodic Timer enabling
 * subscription services.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "SimpleDataSourceMessageEndpointConnector.h"
#include "Gea2Message.h"
#include "utils.h"
#include "uassert.h"

enum
{
   MissedAckLimit = 10,
   ResponseRetries = 2,
   PublishRetries = 2,
   Gea2MessageEndpointConnectorRunPeriod = 250
};
typedef uint8_t Configuration_t;

static void RunGea2MessageEndpointConnector(void *context)
{
   REINTERPRET(instance, context, SimpleDataSourceMessageEndpointConnector_t *);
   DataSourcePacketGea2MessageEndpointConnector_Run(&instance->_private.connector);
}

void SimpleDataSourceMessageEndpointConnector_Init(
   SimpleDataSourceMessageEndpointConnector_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t *subscriptionStorage,
   uint8_t numberOfSubscriptionItems,
   uint8_t maxMessagePayloadSize)
{
   uassert(numberOfSubscriptionItems != 0);
   uassert(maxMessagePayloadSize <= GEA2MESSAGE_MAXPAYLOAD);

   DataSourcePacketSubscriptionManager_Simple_Init(
      &instance->_private.subscriptionManager,
      dataSource,
      subscriptionStorage,
      numberOfSubscriptionItems,
      MissedAckLimit);

   DataSourcePacketSubscriptionFrontEnd_Simple_Init(
      &instance->_private.subscriptionFrontEnd,
      &instance->_private.subscriptionManager.interface);

   DataSourcePacketReadWriteManager_Init(
      &instance->_private.readWriteManager,
      dataSource);

   DataSourcePacketGea2MessageEndpointConnector_Init(
      &instance->_private.connector,
      messageEndpoint,
      &instance->_private.readWriteManager.interface,
      &instance->_private.subscriptionFrontEnd.interface,
      maxMessagePayloadSize,
      ResponseRetries,
      PublishRetries);

   TimerModule_StartPeriodic(
      timerModule, &instance->_private.messageEndpointTimer,
      Gea2MessageEndpointConnectorRunPeriod,
      RunGea2MessageEndpointConnector,
      instance);
}
