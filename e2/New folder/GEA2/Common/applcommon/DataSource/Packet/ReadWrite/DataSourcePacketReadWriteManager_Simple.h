/*!
 * @file
 * @brief Packet-based data source read/write access manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETREADWRITEMANAGER_SIMPLE_H
#define DATASOURCEPACKETREADWRITEMANAGER_SIMPLE_H

#include <stdint.h>
#include <stdbool.h>
#include "Erd.h"
#include "I_DataSource.h"

#include "I_DataSourcePacketReadWriteManager.h"

/*!
 * No-frills data source packet read/write manager.  Struct members should be considered private.
 */
typedef struct
{
   I_DataSourcePacketReadWriteManager_t interface;

   struct
   {
      I_DataSource_t *dataSource;
   } _private;
} DataSourcePacketReadWriteManager_Simple_t;

/*!
 * Initialize the read/write manager.
 * @pre instance != NULL
 * @pre dataSource != NULL
 * @param instance The read/write manager.
 * @param dataSource Pointer to the data source that the manager will provide access to.
 */
void DataSourcePacketReadWriteManager_Init(DataSourcePacketReadWriteManager_Simple_t *instance, I_DataSource_t *dataSource);

#endif
