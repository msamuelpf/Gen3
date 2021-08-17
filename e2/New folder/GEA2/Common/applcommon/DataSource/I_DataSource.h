/*!
 * @file
 * @brief Generic ERD access interface.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_DATASOURCE_H
#define I_DATASOURCE_H

#include "Erd.h"
#include "I_Event.h"

typedef struct
{
   Erd_t erd;
   const void *data;
} DataSourceOnDataChangeArgs_t;

struct I_DataSource_Api_t;

/*!
 * Generic data source.
 */
typedef struct
{
   /*!
    * API for interacting with the particular instance of data source.
    */
   const struct I_DataSource_Api_t *api;

   /*!
    * Event raised when the data corresponding to an ERD changes.  An instance of DataSoruceOnChangeArgs_t
    * is provided as the argument parameter.
    */
   I_Event_t *OnDataChange;
} I_DataSource_t;

/*!
 * Interface for interacting with a data source.  API should be accessed using wrapper calls below.
 */
typedef struct I_DataSource_Api_t
{
   /*!
    * Read an ERD.
    * @pre instance != NULL
    * @pre data != NULL
    * @pre Has(instance, erd)
    * @param instance Data source to read from.
    * @param erd ERD to read.
    * @param data ERD data to populate.
    */
   void (*Read)(I_DataSource_t *instance, const Erd_t erd, void *data);

   /*!
    * Write an ERD.
    * @pre instance != NULL
    * @pre data != NULL
    * @pre Has(instance, erd)
    * @param instance Data source to write to.
    * @param erd ERD to write.
    * @param data ERD data to write.
    * @return True if write successful, false otherwise.
    */
   void (*Write)(I_DataSource_t *instance, const Erd_t erd, const void *data);

   /*!
    * Determine whether a data source contains an ERD.
    * @pre instance != NULL
    * @param instance Data source to check.
    * @param erd ERD to check.
    * @return True if the data source has the ERD, false otherwise.
    */
   bool (*Has)(const I_DataSource_t *instance, const Erd_t erd);

   /*!
    * Get the size of the data associated with an ERD.
    * @pre instance != NULL
    * @pre Has(instance, erd)
    * @param instance Data source that contains ERD.
    * @param erd The ERD.
    * @return The size of the ERD data.
    */
   uint8_t (*SizeOf)(const I_DataSource_t *instance, const Erd_t erd);
} I_DataSource_Api_t;

#define DataSource_Read(instance, erd, data) \
   (instance)->api->Read((instance), (erd), (data))

#define DataSource_Write(instance, erd, data) \
   (instance)->api->Write((instance), (erd), (data))

#define DataSource_Has(instance, erd) \
   (instance)->api->Has((instance), (erd))

#define DataSource_SizeOf(instance, erd) \
   (instance)->api->SizeOf((instance), (erd))

#endif
