/*!
 * @file
 * @brief Data source that stores its ERD data in RAM and uses a const array map module to manage ERD lookup
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCE_RAM_H
#define DATASOURCE_RAM_H

#include "I_DataSource.h"
#include "Event_Synchronous.h"
#include "I_ConstArrayMap.h"

typedef struct
{
   Erd_t erd;
   uint16_t offset; // Offset of the ERD into RAM
} DataSource_RamErdConfigurationElement_t;

typedef struct
{
   I_DataSource_t interface;

   struct
   {
      Event_Synchronous_t dataChangeEvent;
      void *erdRam;
      uint16_t erdRamSize;
      I_ConstArrayMap_t *erdConfiguration;
   } _private;
} DataSource_Ram_t;

/*!
 * Initialize the RAM data source that leverages ConstArrayMap for search routines
 * @pre Const array map entries must be of type DataSource_RamReplacementErdConfigurationElement_t
 * @param instance The instance
 * @param erdRam RAM where ERD data will exist
 * @param erdRamSize The size of the reserved RAM
 * @param erdConfiguration Const array map of ERD configuration
 */
void DataSource_Ram_Init(
   DataSource_Ram_t *instance,
   void *erdRam,
   uint16_t erdRamSize,
   I_ConstArrayMap_t *erdConfiguration);

#endif
