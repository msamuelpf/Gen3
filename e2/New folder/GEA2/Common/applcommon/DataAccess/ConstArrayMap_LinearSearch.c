/*!
 * @file
 * @brief Implementation of the linear search const array map
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include "ConstArrayMap_LinearSearch.h"
#include "uassert.h"
#include "utils.h"

static bool Read(I_ConstArrayMap_t *_instance, uint16_t index, void *entry)
{
   REINTERPRET(instance, _instance, ConstArrayMap_LinearSearch_t *);

   if(index < instance->_private.configuration->elementCount)
   {
      uint32_t arrayOffset = (index * instance->_private.configuration->elementSize);
      const char *requestedEntry = (const char *)instance->_private.configuration->array + arrayOffset;

      memcpy(entry, requestedEntry, instance->_private.configuration->elementSize);
      return true;
   }

   return false;
}

static bool Find(I_ConstArrayMap_t *_instance, const void *key, uint16_t *currentIndex, void *entry)
{
   REINTERPRET(instance, _instance, ConstArrayMap_LinearSearch_t *);
   uint16_t index;

   for(index = 0; index < instance->_private.configuration->elementCount; index++)
   {
      uint32_t currentArrayOffset = (index * instance->_private.configuration->elementSize) + instance->_private.configuration->keyOffset;
      const char *currentKey = (const char *)instance->_private.configuration->array + currentArrayOffset;

      if(0 == memcmp(key, currentKey, instance->_private.configuration->keySize))
      {
         *currentIndex = index;
         return Read(_instance, index, entry);
      }
   }

   return false;
}

static uint16_t NumberOfEntries(I_ConstArrayMap_t *_instance)
{
   REINTERPRET(instance, _instance, ConstArrayMap_LinearSearch_t *);
   return instance->_private.configuration->elementCount;
}

static const I_ConstArrayMap_Api_t api =
   { Find, Read, NumberOfEntries };

void ConstArrayMap_LinearSearch_Init(
   ConstArrayMap_LinearSearch_t *instance,
   const ConstArrayMap_LinearSearchConfiguration_t *configuration)
{
   instance->interface.api = &api;
   instance->_private.configuration = configuration;
}
