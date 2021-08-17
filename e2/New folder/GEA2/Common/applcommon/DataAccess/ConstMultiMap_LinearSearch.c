/*!
 * @file
 * @brief Implementation of the linear search const multi map
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include <string.h>
#include <stdint.h>
#include "ConstMultiMap_LinearSearch.h"
#include "utils.h"

typedef struct
{
   I_Iterator_t interface;
   const void *searchKey;
   const ConstMultiMap_LinearSearchConfiguration_t *configuration;
   uint16_t currentIndex;
} MultiMapIterator_t;

static bool KeyMatchesSearchKey(MultiMapIterator_t *iterator, const void *currentKey)
{
   return (0 == memcmp(currentKey, iterator->searchKey, iterator->configuration->keySize));
}

static const uint8_t * CurrentEntry(MultiMapIterator_t *iterator)
{
   return (const uint8_t *)iterator->configuration->array + (iterator->currentIndex * iterator->configuration->elementSize);
}

static bool GetNext(I_Iterator_t *_iterator, void *entry)
{
   REINTERPRET(iterator, _iterator, MultiMapIterator_t *);

   while(iterator->currentIndex < iterator->configuration->elementCount)
   {
      const uint8_t *currentEntry = CurrentEntry(iterator);
      const void *currentKey = currentEntry + iterator->configuration->keyOffset;
      const void *currentValue = currentEntry + iterator->configuration->valueOffset;

      iterator->currentIndex++;

      if(KeyMatchesSearchKey(iterator, currentKey))
      {
         memcpy(entry, currentValue, iterator->configuration->valueSize);

         return true;
      }
   }

   return false;
}

static const I_Iterator_Api_t iteratorApi =
   { GetNext };

static void Find(I_ConstMultiMap_t *_instance, const void *key, ConstMultiMapCallback_t callback, void *clientContext)
{
   REINTERPRET(instance, _instance, ConstMultiMap_LinearSearch_t *);
   MultiMapIterator_t iterator;

   iterator.interface.api = &iteratorApi;
   iterator.searchKey = key;
   iterator.configuration = instance->_private.configuration;
   iterator.currentIndex = 0;

   callback(clientContext, &iterator.interface);
}

static const I_ConstMultiMap_Api_t api =
   { Find };

void ConstMultiMap_LinearSearch_Init(
   ConstMultiMap_LinearSearch_t *instance,
   const ConstMultiMap_LinearSearchConfiguration_t *configuration)
{
   instance->interface.api = &api;
   instance->_private.configuration = configuration;
}
