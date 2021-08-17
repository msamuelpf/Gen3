/*!
 * @file
 * @brief Null DataSourcePacketSubscriptionFrontEnd implementation for systems that do not support subscriptions.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef DATASOURCEPACKETSUBSCRIPTIONFRONTEND_NULL_H
#define DATASOURCEPACKETSUBSCRIPTIONFRONTEND_NULL_H

#include "I_DataSourcePacketSubscriptionFrontEnd.h"

/*!
 * Gets the instance
 * @return The null front end instance
 */
I_DataSourcePacketSubscriptionFrontEnd_t * DataSourcePacketSubscriptionFrontEnd_Null_GetInstance(void);

#endif
