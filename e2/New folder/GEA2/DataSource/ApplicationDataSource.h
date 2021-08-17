/*!
 * @file
 * @brief Application data source for Centauro UI
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef APPLICATIONDATASOURCE_H
#define APPLICATIONDATASOURCE_H

#include <WasherErds.h>
#include "DataSource_Ram.h"
#include "ConstArrayMap_LinearSearch.h"
#include "utils.h"
#include "XMacroUtils.h"
#include "DataSource_EndiannessSwapped.h"
#include "ConstMultiMap_LinearSearch.h"

#define EXPAND_AS_OFFSET_STRUCT_MEMBER(ErdEnum, Number, DataType, EndiannessAware, EnableIn, EnableOut) \
   uint8_t MACRO_SAFE_CONCATENATE(erd, ErdEnum)[sizeof(DataType)];

typedef struct
{
   ERD_TABLE(EXPAND_AS_OFFSET_STRUCT_MEMBER)
} ApplicationDataSourceRamErdConfiguration_t;

typedef struct
{
   struct
   {
      DataSource_Ram_t dataSourceRam;
      ConstArrayMap_LinearSearch_t linearSearch;
      uint8_t erd_Ram[sizeof(ApplicationDataSourceRamErdConfiguration_t)];
      DataSource_EndiannessSwapped_t swappedDataSource;
      ConstMultiMap_LinearSearch_t swappedMultiMap;
   } _private;
} ApplicationDataSource_t;

/*!
 * Initialize the application data source
 * @param instance
 */
void ApplicationDataSource_Init(ApplicationDataSource_t *instance);

/*!
 * Get the data source from the application data source
 * @param instance
 * @return data source
 */
I_DataSource_t * ApplicationDataSource_GetInternalDataSource(ApplicationDataSource_t *instance);

/*!
 * Get the external data source
 * @param instance
 * @return The external data source
 */
I_DataSource_t * ApplicationDataSource_GetExternalDataSource(ApplicationDataSource_t *instance);

#endif
