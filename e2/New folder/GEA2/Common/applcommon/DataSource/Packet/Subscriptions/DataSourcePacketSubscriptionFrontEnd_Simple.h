/*!
 * @file
 * @brief No-frills version of a front end for a packet-based data source subscription manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETSUBSCRIPTIONFRONTEND_SIMPLE_H
#define DATASOURCEPACKETSUBSCRIPTIONFRONTEND_SIMPLE_H

#include "I_DataSourcePacketSubscriptionFrontEnd.h"
#include "I_DataSourcePacketSubscriptionManager.h"

/*!
 * Simple subscription front-end.  Struct members should be considered private.
 */
typedef struct
{
   I_DataSourcePacketSubscriptionFrontEnd_t interface;
   struct
   {
      I_DataSourcePacketSubscriptionManager_t *subscriptionManager;
   } _private;
} DataSourcePacketSubscriptionFrontEnd_Simple_t;

/*!
 * Initialize a subscription front-end.
 * @pre instance != NULL
 * @pre subscriptionManager != NULL
 * @param instance The subscription front-end.
 * @param subscriptionManager The subscription manager that the front-end is for.
 */
void DataSourcePacketSubscriptionFrontEnd_Simple_Init(DataSourcePacketSubscriptionFrontEnd_Simple_t *instance,
   I_DataSourcePacketSubscriptionManager_t *subscriptionManager);

#endif
