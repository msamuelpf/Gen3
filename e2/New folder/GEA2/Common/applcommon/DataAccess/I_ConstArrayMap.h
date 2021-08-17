/*!
 * @file
 * @brief Define the interface to a constant ConstTableMap storage that can be accessed via index or key
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_CONSTARRAYMAP_H
#define I_CONSTARRAYMAP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct I_ConstArrayMap_Api_t;

typedef struct
{
   const struct I_ConstArrayMap_Api_t *api;
} I_ConstArrayMap_t;

typedef struct I_ConstArrayMap_Api_t
{
   /*!
    * Find a Key.
    * @param Instance of I_ConstArrayMap_t
    * @param key A pointer to the value to be found.
    * @param currentIndex Index of the current occurrence of the key value
    * @param entry Returned ConstArrayMap entry is copied to the location pointed to by entry if key exists,
    *    Unchanged if entry not found
    * @return bool Return True if entry found, False if entry not found
    * @note Search method is left to the implementation
    * @note Key match method is left to the implementation
    */
   bool (*Find)(I_ConstArrayMap_t *instance, const void *key, uint16_t *currentIndex, void *entry);

   /*!
    * Return a pointer to the ConstArrayMap at the index
    * @param instance Instance of I_ConstArrayMap_t
    * @param index Index of the ConstArrayMap entry to read
    * @param entry Returned ConstArrayMap entry is copied to the location pointed to by index if the index exists,
    *    Unchanged if the index does not exist
    * @return bool True if Index exists and False if Index does not exist
    */
   bool (*Read)(I_ConstArrayMap_t *instance, uint16_t index, void *entry);

   /*!
    * Return the number of entries in the ConstArrayMap
    * @param instance Instance of I_ConstArrayMap_t
    * @return size_t count of entries in the object
    */
   uint16_t (*NumberOfEntries)(I_ConstArrayMap_t *instance);
} I_ConstArrayMap_Api_t;

#define ConstArrayMap_Find(instance, key, index, entry) \
   (instance)->api->Find((instance), (key), (index), (entry))

#define ConstArrayMap_Read(instance, index, entry) \
   (instance)->api->Read((instance), (index), (entry))

#define ConstArrayMap_NumberOfEntries(instance) \
   (instance)->api->NumberOfEntries((instance))

#endif
