/*!
 * @file
 * @brief Front-end to a subscription manager that parses packets and forwards request to the subscription
 * manager.  Also generates publish packets on behalf of the subscription manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_DATASOURCEPACKETSUBSCRIPTIONFRONTEND_H
#define I_DATASOURCEPACKETSUBSCRIPTIONFRONTEND_H

#include <stdbool.h>
#include <stdint.h>

struct I_DataSourcePacketSubscriptionFrontEnd_Api_t;

/*!
 * Generic packet-based data source subscription front-end.
 */
typedef struct
{
   const struct I_DataSourcePacketSubscriptionFrontEnd_Api_t *api;
} I_DataSourcePacketSubscriptionFrontEnd_t;

/*!
 * Methods for interacting with a packet-based data source subscription front-end.  Methods should
 * not be invoked directly, they should be invoked using wrapper calls below.
 */
typedef struct I_DataSourcePacketSubscriptionFrontEnd_Api_t
{
   /*!
    * Process a subscribe request and generate a response.
    * @pre instance != NULL
    * @pre request != NULL
    * @pre responseBuffer != NULL
    * @pre responseSize != NULL
    * @param instance The subscription front-end.
    * @param request The subscribe request buffer.
    * @param responseBuffer The buffer that will be filled with the response.
    * @param responseBufferSize The maximum size of the response.
    * @param responseSize The actual size of the response.  This is an output parameter.
    * @param subscriberId The entity requesting to subscribe.
    */
   void (*SubscribeRequest)(I_DataSourcePacketSubscriptionFrontEnd_t *instance, const void *request,
      void *responseBuffer, const uint8_t responseBufferSize, uint8_t *responseSize, const uint8_t subscriberId);

   /*!
    * Process an unsubscribe request and generate a response.
    * @pre instance != NULL
    * @pre request != NULL
    * @pre responseBuffer != NULL
    * @pre responseSize != NULL
    * @pre responseBufferSize > 0
    * @param instance The subscription front-end.
    * @param request The unsubscribe request buffer.
    * @param responseBuffer The buffer that will be filled with the response.
    * @param responseBufferSize The maximum size of the response.
    * @param responseSize The actual size of the response.  This is an output parameter.
    * @param subscriberId The entity requesting to unsubscribe.
    */
   void (*UnsubscribeRequest)(I_DataSourcePacketSubscriptionFrontEnd_t *instance, const void *request,
      void *responseBuffer, const uint8_t responseBufferSize, uint8_t *responseSize, const uint8_t subscriberId);

   /*!
    * Process a subscription list request and generate a response.
    * @pre instance != NULL
    * @pre responseBuffer != NULL
    * @pre responseSize != NULL
    * @param instance The subscription front-end.
    * @param responseBuffer The buffer that will be filled with the response.
    * @param responseBufferSize The maximum size of the response.
    * @param responseSize The actual size of the response.  This is an output parameter.
    * @param subscriberId The entity requesting its subscription list.
    */
   void (*ListRequest)(I_DataSourcePacketSubscriptionFrontEnd_t *instance, void *responseBuffer,
      const uint8_t responseBufferSize, uint8_t *responseSize, const uint8_t subscriberId);

   /*!
    * Process a publish acknowledgement.
    * @pre instance != NULL
    * @param instance The subscription front-end.
    * @param subscriberId The entity acknowledging publish.
    */
   void (*PublishAcknowledge)(I_DataSourcePacketSubscriptionFrontEnd_t *instance, const uint8_t subscriberId);

   /*!
    * Service pending subscriptions for at most one subscriber.
    * @pre instance != NULL
    * @pre publishBuffer != NULL
    * @pre publishSize != NULL
    * @pre subscriberId != NULL
    * @param instance The subscription front-end.
    * @param publishBuffer The buffer that will be filled with the publish.
    * @param publishBufferSize The maximum size of a  publish.
    * @param publishSize The actual size of the publish.  This is an output parameter.
    * @param subscriberId The subscriber being published to.
    * @return True if the publish buffer contains a valid publish, false otherwise.  There will be no
    * valid publish if no publishes are pending or if the publish buffer cannot fit the pending publish.
    */
   bool (*ServiceSubscriptions)(I_DataSourcePacketSubscriptionFrontEnd_t *instance, void *publishBuffer,
      const uint8_t publishBufferSize, uint8_t *publishSize, uint8_t *subscriberId);
} I_DataSourcePacketSubscriptionFrontEnd_Api_t;

#define DataSourcePacketSubscriptionFrontEnd_SubscribeRequest(instance, request, responseBuffer, responseBufferSize, responseSize, subscriberId) \
   (instance)->api->SubscribeRequest((instance), (request), (responseBuffer), (responseBufferSize), (responseSize), (subscriberId))

#define DataSourcePacketSubscriptionFrontEnd_UnsubscribeRequest(instance, request, responseBuffer, responseBufferSize, responseSize, subscriberId) \
   (instance)->api->UnsubscribeRequest((instance), (request), (responseBuffer), (responseBufferSize), (responseSize), (subscriberId))

#define DataSourcePacketSubscriptionFrontEnd_ListRequest(instance, responseBuffer, responseBufferSize, responseSize, subscriberId) \
   (instance)->api->ListRequest((instance), (responseBuffer), (responseBufferSize), (responseSize), (subscriberId))

#define DataSourcePacketSubscriptionFrontEnd_PublishAcknowledge(instance, subscriberId) \
   (instance)->api->PublishAcknowledge((instance), (subscriberId))

#define DataSourcePacketSubscriptionFrontEnd_ServiceSubscriptions(instance, publishBuffer, publishBufferSize, publishSize, subscriberId) \
   (instance)->api->ServiceSubscriptions((instance), (publishBuffer), (publishBufferSize), (publishSize), (subscriberId))

#endif
