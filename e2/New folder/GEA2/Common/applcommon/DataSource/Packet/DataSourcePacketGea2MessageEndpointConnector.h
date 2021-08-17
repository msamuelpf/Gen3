/*!
 * @file
 * @brief 'Wires' a DataSourcePacketReadWriteManager and a DataSourcePacketSubscriptionFrontEnd to a
 * Gea2MessageEndpoint.
 *
 * When ERD requests are received on the message endpoint they will be forwarded to the appropriate
 * object (read/write requests will go to the read/write manager, all subscription requests will go
 * to the subscription front-end).
 *
 * Additionally, any subscription publications from the subscription front-end will be sent using
 * the message endpoint.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETGEA2MESSAGEENDPOINTCONNECTOR_H
#define DATASOURCEPACKETGEA2MESSAGEENDPOINTCONNECTOR_H

#include "I_Gea2MessageEndpoint.h"
#include "I_DataSourcePacketReadWriteManager.h"
#include "I_DataSourcePacketSubscriptionFrontEnd.h"

typedef struct
{
   struct
   {
      EventSubscription_t messageReceivedSubscription;
      I_Gea2MessageEndpoint_t *messageEndpoint;
      I_DataSourcePacketReadWriteManager_t *readWriteManager;
      I_DataSourcePacketSubscriptionFrontEnd_t *subscriptionFrontEnd;
      uint8_t maxMessagePayloadSize;
      uint8_t responseRetries;
      uint8_t publishRetries;
   } _private;
} DataSourcePacketGea2MessageEndpointConnector_t;

/*!
 * Initialize a connector.
 * @pre instance != NULL
 * @pre messageEndpoint != NULL
 * @pre readWriteManager != NULL
 * @pre subscriptionFrontEnd != NULL
 * @param instance The connector.
 * @param messageEndpoint The message endpoint that will be used to receive requests and to send responses/publications.
 * @param readWriteManager Will be used to execute packet-based data source reads.
 * @param subscriptionFrontEnd Will be used to execute packet-based subscription requests and get publications.
 * @param maxMessagePayloadSize The maximum payload size of any responses/publishes.
 * @param responseRetries The number of retries to use when sending a response.
 * @param publishRetries The number of retries to use when sending a publication.
 */
void DataSourcePacketGea2MessageEndpointConnector_Init(
   DataSourcePacketGea2MessageEndpointConnector_t *instance,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   I_DataSourcePacketReadWriteManager_t *readWriteManager,
   I_DataSourcePacketSubscriptionFrontEnd_t *subscriptionFrontEnd,
   const uint8_t maxMessagePayloadSize,
   const uint8_t responseRetries,
   const uint8_t publishRetries);

/*!
 * Give the connector an opportunity to service subscriptions.  Should be called at an appropriate rate
 * for the desired subscription latency.
 * @pre instance != NULL
 * @param instance The connector.
 */
void DataSourcePacketGea2MessageEndpointConnector_Run(DataSourcePacketGea2MessageEndpointConnector_t * instance);

#endif
