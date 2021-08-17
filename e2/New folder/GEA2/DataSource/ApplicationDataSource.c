/*!
 * @file
 * @brief Application data source for Centauro UI
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "ApplicationDataSource.h"

#define EXPAND_AS_CONFIGURATION(ErdEnum, Number, DataType, EndiannessAware, EnableIn, EnableOut) \
   {ErdEnum COMMA OFFSET_OF(ApplicationDataSourceRamErdConfiguration_t, MACRO_SAFE_CONCATENATE(erd, ErdEnum))} COMMA

#define GENERATE_CONFIG(_table, _name) \
   static const DataSource_RamErdConfigurationElement_t _name[] = { _table(EXPAND_AS_CONFIGURATION) };

GENERATE_CONFIG(ERD_TABLE, erdConfigurations)

static const ConstArrayMap_LinearSearchConfiguration_t erdConfigurationList =
   {
      erdConfigurations,	// .array = 
      ELEMENT_COUNT(erdConfigurations),	// .elementCount = 
      ELEMENT_SIZE(erdConfigurations),	// .elementSize = 
      MEMBER_SIZE(DataSource_RamErdConfigurationElement_t, erd),	// .keySize = 
      OFFSET_OF(DataSource_RamErdConfigurationElement_t, erd),	// .keyOffset = 
   };

static const DataSource_EndiannessSwappedSwappedField_t swappedFields[] =
   {
		   SWAPPED_FIELD(Erd_WaterFilterStatus, TS_EntityWaterFilterStatus, U16DaysRemaining),
		   SWAPPED_FIELD(Erd_WaterFilterStatus, TS_EntityWaterFilterStatus, u16DaysOverDue),
		   SWAPPED_FIELD(Erd_WaterFilterStatus, TS_EntityWaterFilterStatus, u16DispensesOverDue),
   };

static const ConstMultiMap_LinearSearchConfiguration_t swappedMultiMapConfiguration =
   {
      swappedFields,	// .array = 
      NUM_ELEMENTS(swappedFields),	// .elementCount = 
      ELEMENT_SIZE(swappedFields),	// .elementSize = 
      MEMBER_SIZE(DataSource_EndiannessSwappedSwappedField_t, erd),	// .keySize = 
      OFFSET_OF(DataSource_EndiannessSwappedSwappedField_t, erd),	// .keyOffset = 
      sizeof(DataSource_EndiannessSwappedSwappedField_t),	// .valueSize = 
      0,	// .valueOffset = 
   };

void ApplicationDataSource_Init(ApplicationDataSource_t *instance)
{
   ConstArrayMap_LinearSearch_Init(&instance->_private.linearSearch, &erdConfigurationList);

   DataSource_Ram_Init(
      &instance->_private.dataSourceRam,
      instance->_private.erd_Ram,
      sizeof(instance->_private.erd_Ram),
      &instance->_private.linearSearch.interface);

   ConstMultiMap_LinearSearch_Init(&instance->_private.swappedMultiMap, &swappedMultiMapConfiguration);

   DataSource_EndiannessSwapped_Init(
      &instance->_private.swappedDataSource,
      &instance->_private.dataSourceRam.interface,
      &instance->_private.swappedMultiMap.interface);
}

I_DataSource_t * ApplicationDataSource_GetInternalDataSource(ApplicationDataSource_t *instance)
{
   return &instance->_private.dataSourceRam.interface;
}

I_DataSource_t * ApplicationDataSource_GetExternalDataSource(ApplicationDataSource_t *instance)
{
   return &instance->_private.swappedDataSource.interface;
}
