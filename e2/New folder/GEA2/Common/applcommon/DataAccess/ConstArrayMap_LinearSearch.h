/*!
 * @file
 * @brief ConstArrayMap that performs linear searches on provided data.  Ideal for small data sets where
 * configuration constraints are not desirable.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef CONSTARRAYMAP_LINEARSEARCH_H
#define CONSTARRAYMAP_LINEARSEARCH_H

#include <stdint.h>
#include "I_ConstArrayMap.h"
#include "utils.h"

#define CONSTARRAYMAP_LINEARSEARCH_CONFIG(array, type, key) \
{                                                           \
   array,                                                   \
   ELEMENT_COUNT(array),                                    \
   ELEMENT_SIZE(array),                                     \
   MEMBER_SIZE(type, key),                                  \
   OFFSET_OF(type, key)                                     \
}                                                           \

typedef struct
{
   const void *array;
   uint16_t elementCount;
   uint16_t elementSize;
   uint16_t keySize;
   uint16_t keyOffset;
} ConstArrayMap_LinearSearchConfiguration_t;

typedef struct
{
   I_ConstArrayMap_t interface;

   struct
   {
      const ConstArrayMap_LinearSearchConfiguration_t *configuration;
   } _private;
} ConstArrayMap_LinearSearch_t;

/*!
 * Initialize a const array map with linear search
 * @param instance The instance
 * @param configuration Configuration for the array map
 */
void ConstArrayMap_LinearSearch_Init(
   ConstArrayMap_LinearSearch_t *instance,
   const ConstArrayMap_LinearSearchConfiguration_t *configuration);

#endif
