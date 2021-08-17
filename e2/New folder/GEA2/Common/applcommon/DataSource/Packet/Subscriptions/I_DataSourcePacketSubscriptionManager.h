/*!
 * @file
 * @brief Subscription manager for packet-based data source access.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_DATASOURCEPACKETSUBSCRIPTIONMANAGER_H
#define I_DATASOURCEPACKETSUBSCRIPTIONMANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include "Erd.h"
#include "I_DataSource.h"

struct I_DataSourcePacketSubscriptionManager_Api_t;

/*!
 * Generic data source subscription manager.
 */
typedef struct
{
   const struct I_DataSourcePacketSubscriptionManager_Api_t *api;
} I_DataSourcePacketSubscriptionManager_t;

/*!
 * Callback called for each ERD in a subscription list.
 * @param context The callback context.
 * @param erd The ERD in the subscription list.
 * @param subscriptionTime The ERD subscription time.
 */
typedef void (*DataSourcePacketSubscriptionManagerGetSubscriptionListForEachCallback_t)(
   void *context,
   Erd_t erd,
   uint8_t subscriptionTime);

/*!
 * Callback called for each changed item in a subscription update.
 * @param context The callback context.
 * @param erd The ERD being published.
 * @param dataSource The data source that has the updated ERD data.
 * @return The client must return true if the subscription publish for the was processed, false otherwise.
 */
typedef bool (*DataSourcePacketSubscriptionManagerServiceSubscriptionsForEachCallback_t)(
   void *context,
   Erd_t erd,
   I_DataSource_t *dataSource);

/*!
 * Methods for interacting with a data source packet subscription manager.  Methods should be accessed
 * using wrapper calls given below.
 */
typedef struct I_DataSourcePacketSubscriptionManager_Api_t
{
   /*!
    * Add a subscription to the list of managed subscriptions.
    * @pre instance != NULL
    * @param instance The subscription manager.
    * @param subscriberId The ID of the subscriber for which to add the subscription.
    * @param erd The ERD to subscribe to.
    * @param subscriptionTime The rate at which the ERD should be published even if the value has not changed.
    * @return True if subscription was able to be added, false otherwise.
    */
   bool (*AddSubscription)(
      I_DataSourcePacketSubscriptionManager_t *instance,
      const uint8_t subscriberId, const Erd_t erd,
      const uint8_t subscriptionTime);

   /*!
    * Remove a subscription from the list of managed subscriptions.
    * @pre instance != NULL
    * @param instance The subscription manager.
    * @param subscriberId The ID of the subscriber for which to remove the subscription.
    * @param erd The ERD to unsubscribe from.
    * @return True if the subscription was removed, false otherwise.
    */
   bool (*RemoveSubscription)(
      I_DataSourcePacketSubscriptionManager_t *instance,
      const uint8_t subscriberId,
      const Erd_t erd);

   /*!
    * Notify the subscription manager of a publish response.
    * @pre instance != NULL
    * @param instance The subscription manager.
    * @param subscriberId The ID of the subscriber from which the publish response was received.
    */
   void (*NotifyPublishResponse)(
      I_DataSourcePacketSubscriptionManager_t *instance,
      const uint8_t subscriberId);

   /*!
    * Get the subscription list for a subscriber.  A callback is invoked for each ERD in the subscription
    * list of the specified subscriber.
    * @pre instance != NULL
    * @pre callback != NULL
    * @param instance The subscription manager.
    * @param callback The callback invoked for each ERD in the subscription list of the subscriber.
    * @param context The context to be provided on each invocation of the callback.
    * @param subscriberId The ID of the subscriber for which to get the subscription list.
    */
   void (*GetSubscriptionList)(
      I_DataSourcePacketSubscriptionManager_t *instance,
      DataSourcePacketSubscriptionManagerGetSubscriptionListForEachCallback_t callback,
      void *context,
      const uint8_t subscriberId);

   /*!
    * Service a subscriber's subscriptions.  The callback is invoked for each ERD to be published to the
    * specified subscriber or until the callback returns false to indicate that the publish couldn't be
    * processed.  Services only a single subscriber per invocation.
    * @pre instance != NULL
    * @pre callback != NULL
    * @pre subscriberId != NULL
    * @param instance The subscription manager.
    * @param callback The callback invoked for each ERD pending publish.
    * @param context The context to be provided on each invocation of the callback.
    * @param subscriberId The ID of the subscriber that is being serviced.  This output parameter is only populated if there are publishes pending.
    * @return True if there were pending publishes, false otherwise.
    * @note If a publish can't be processed (ex: not enough space remaining in the publish buffer) then
    * the callback must return false to indicate that the publish is still pending.
    */
   bool (*ServiceSubscriptions)(
      I_DataSourcePacketSubscriptionManager_t *instance,
      DataSourcePacketSubscriptionManagerServiceSubscriptionsForEachCallback_t callback,
      void *context,
      uint8_t *subscriberId);
} I_DataSourcePacketSubscriptionManager_Api_t;

#define DataSourcePacketSubscriptionManager_AddSubscription(instance, subscriberId, erd, subscriptionTime) \
   (instance)->api->AddSubscription((instance), (subscriberId), (erd), (subscriptionTime))

#define DataSourcePacketSubscriptionManager_RemoveSubscription(instance, subscriberId, erd) \
   (instance)->api->RemoveSubscription((instance), (subscriberId), (erd))

#define DataSourcePacketSubscriptionManager_NotifyPublishResponse(instance, subscriberId) \
   (instance)->api->NotifyPublishResponse((instance), (subscriberId))

#define DataSourcePacketSubscriptionManager_GetSubscriptionList(instance, callback, context, subscriberId) \
   (instance)->api->GetSubscriptionList((instance), (callback), (context), (subscriberId))

#define DataSourcePacketSubscriptionManager_ServiceSubscriptions(instance, subscriberId, erd, subscriptionTime) \
   (instance)->api->ServiceSubscriptions((instance), (subscriberId), (erd), (subscriptionTime))

#endif
