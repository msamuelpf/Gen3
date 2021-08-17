/*!
 * @file
 * @brief Linear implementation of the const multimap. Use this when search lists are short and code size is a priority.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef CONSTMULTIMAP_LINEARSEARCH_H
#define CONSTMULTIMAP_LINEARSEARCH_H

#include <stdint.h>
#include "I_ConstMultiMap.h"

typedef struct
{
   const void *array;
   uint16_t elementCount;
   uint16_t elementSize;
   uint16_t keySize;
   uint16_t keyOffset;
   uint16_t valueSize;
   uint16_t valueOffset;
} ConstMultiMap_LinearSearchConfiguration_t;

typedef struct
{
   I_ConstMultiMap_t interface;

   struct
   {
      const ConstMultiMap_LinearSearchConfiguration_t *configuration;
   } _private;
} ConstMultiMap_LinearSearch_t;

/*!
 * Initialize the linear search const multi map
 * @param instance The multi map instance
 * @param configuration Configuration data for the map
 */
void ConstMultiMap_LinearSearch_Init(
   ConstMultiMap_LinearSearch_t *instance,
   const ConstMultiMap_LinearSearchConfiguration_t *configuration);

#endif
