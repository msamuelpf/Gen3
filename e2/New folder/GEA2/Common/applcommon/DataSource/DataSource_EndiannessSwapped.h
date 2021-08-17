/*!
 * @file
 * @brief DataSource wrapper that selectively swaps endianness for a list of ERDs.
 *
 * When an ERD is written to, the data is assumed to be of the 'wrong' endianness.  The endianness
 * will be swapped before being passed to the wrapped DataSource.
 *
 * When an ERD is read (or a change is published), the ERD data will be converted to the opposite
 * endianness before being passed to a client.
 *
 * This component will allow a DataSource that contains data stored in the current system endianness
 * to be accessed and written by an entity (ex: an external entity connected via GEA2 bus) with another
 * endianness (big endian for GEA2).
 *
 * The range version allows ranges of ERDs which have the same structure and are next to each
 * other in the datasource to be swapped with one table entry. This will save ROM and copy/paste
 * code. The edges of the range are valid swap entries.
 *
 * @note This module only supports big/little endianness, not any of the more exotic endiannesses.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCE_ENDIANNESSSWAPPED_H
#define DATASOURCE_ENDIANNESSSWAPPED_H

#include "I_ConstMultiMap.h"
#include "I_DataSource.h"
#include "Event_Synchronous.h"
#include "utils.h"

#define SWAPPED_FIELD(erd, container_type, field_name) \
   { erd, (uint8_t)OFFSET_OF(container_type, field_name), (uint8_t)MEMBER_SIZE(container_type, field_name) }

#define SWAPPED_ERD(erd, data_size) \
   { erd, 0, data_size }

typedef struct
{
   Erd_t erd;
   uint8_t fieldOffset;
   uint8_t fieldSize;
} DataSource_EndiannessSwappedSwappedField_t;

typedef struct
{
   I_DataSource_t interface;

   struct
   {
      I_DataSource_t *wrappedDataSource;
      Event_Synchronous_t concreteOnDataChangeEvent;
      EventSubscription_t dataChangeSubscription;
      I_ConstMultiMap_t *swapMap;
   } _private;
} DataSource_EndiannessSwapped_t;

/*!
 * Initialize an endianness swapping data source.
 * @param instance The data source.
 * @param dataSourceToWrap The data source that will have its endianness swapped.
 * @param configuration Configuration data for swapping fields.
 */
void DataSource_EndiannessSwapped_Init(
   DataSource_EndiannessSwapped_t *instance,
   I_DataSource_t *dataSourceToWrap,
   I_ConstMultiMap_t *swapMap);

#endif
