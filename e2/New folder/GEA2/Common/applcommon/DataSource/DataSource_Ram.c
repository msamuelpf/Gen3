/*!
 * @file
 * @brief Implementation of DataSource_Ram
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include <stdio.h>
#include "DataSource_Ram.h"
#include "uassert.h"
#include "utils.h"
#include "StackAllocator.h"

#define IS_ALIGNED_ON_BOUNDARY(ptr, boundary) ((intptr_t)(ptr) % (boundary) == 0)

static uint8_t ErdSize(DataSource_Ram_t *instance, uint16_t erdIndex, uint16_t erdOffset)
{
   if(erdIndex == ConstArrayMap_NumberOfEntries(instance->_private.erdConfiguration) - 1)
   {
      return (uint8_t)(instance->_private.erdRamSize - erdOffset);
   }
   else
   {
      DataSource_RamErdConfigurationElement_t next;
      ConstArrayMap_Read(instance->_private.erdConfiguration, (uint16_t )(erdIndex + 1), &next);

      return (uint8_t)(next.offset - erdOffset);
   }
}

static void * ErdData(DataSource_Ram_t *instance, uint16_t erdOffset)
{
   return ((uint8_t *)instance->_private.erdRam) + erdOffset;
}

static void Read(I_DataSource_t *_instance, const Erd_t erd, void *data)
{
   REINTERPRET(instance, _instance, DataSource_Ram_t *);
   uint16_t index;
   DataSource_RamErdConfigurationElement_t entry;

   if(ConstArrayMap_Find(instance->_private.erdConfiguration, &erd, &index, &entry))
   {
      uint8_t erdSize = ErdSize(instance, index, entry.offset);
      void *erdData = ErdData(instance, entry.offset);
      memcpy(data, erdData, (size_t )erdSize);
   }
   else
   {
      uassert(!"Erd not supported");
   }
}

typedef struct
{
   DataSource_Ram_t *instance;
   const void *data;
   Erd_t erd;
   uint8_t erdSize;
} AlignedPublicationContext_t;

static void PublishAligned(void *_context, void *block)
{
   REINTERPRET(context, _context, AlignedPublicationContext_t *);

   DataSourceOnDataChangeArgs_t args;
   args.erd = context->erd;
   args.data = block;

   memcpy(block, context->data, context->erdSize);

   Event_Synchronous_Publish(&context->instance->_private.dataChangeEvent, &args);
}

static void Write(I_DataSource_t *_instance, const Erd_t erd, const void *dataToWrite)
{
   REINTERPRET(instance, _instance, DataSource_Ram_t *);
   uint16_t index;
   DataSource_RamErdConfigurationElement_t entry;

   if(ConstArrayMap_Find(instance->_private.erdConfiguration, &erd, &index, &entry))
   {
      uint8_t erdSize = ErdSize(instance, index, entry.offset);
      void *erdData = ErdData(instance, entry.offset);

      if(0 != memcmp(erdData, dataToWrite, (size_t)erdSize))
      {
         memcpy(erdData, dataToWrite, (size_t )erdSize);

         if(IS_ALIGNED_ON_BOUNDARY(dataToWrite, erdSize))
         {
            DataSourceOnDataChangeArgs_t args;
            args.erd = erd;
            args.data = dataToWrite;

            Event_Synchronous_Publish(&instance->_private.dataChangeEvent, &args);
         }
         else
         {
            AlignedPublicationContext_t context;
            context.instance = instance;
            context.data = dataToWrite;
            context.erd = erd;
            context.erdSize = erdSize;

            StackAllocator_AllocateAligned(erdSize, PublishAligned, &context);
         }
      }
   }
   else
   {
      uassert(!"Erd not supported");
   }
}

static bool Has(const I_DataSource_t *_instance, const Erd_t erd)
{
   REINTERPRET(instance, _instance, DataSource_Ram_t *);
   uint16_t unusedIndex;
   DataSource_RamErdConfigurationElement_t unusedEntry;

   return ConstArrayMap_Find(instance->_private.erdConfiguration, &erd, &unusedIndex, &unusedEntry);
}

static uint8_t SizeOf(const I_DataSource_t *_instance, const Erd_t erd)
{
   REINTERPRET(instance, _instance, DataSource_Ram_t *);
   uint16_t index;
   DataSource_RamErdConfigurationElement_t entry;

   if(ConstArrayMap_Find(instance->_private.erdConfiguration, &erd, &index, &entry))
   {
      return ErdSize(instance, index, entry.offset);
   }
   else
   {
      uassert(!"Erd not supported");
      return 0;
   }
}

static const I_DataSource_Api_t api =
   { Read, Write, Has, SizeOf };

static bool RamIsLargeEnough(DataSource_Ram_t *instance)
{
   uint16_t entryCount = ConstArrayMap_NumberOfEntries(instance->_private.erdConfiguration);
   DataSource_RamErdConfigurationElement_t lastEntry;
   (void)ConstArrayMap_Read(instance->_private.erdConfiguration, (uint16_t )(entryCount - 1), &lastEntry);

   return (bool)(instance->_private.erdRamSize > lastEntry.offset);
}

void DataSource_Ram_Init(
   DataSource_Ram_t *instance,
   void *erdRam,
   uint16_t erdRamSize,
   I_ConstArrayMap_t *erdConfiguration)
{
   instance->interface.api = &api;
   instance->_private.erdConfiguration = erdConfiguration;
   instance->_private.erdRam = erdRam;
   instance->_private.erdRamSize = erdRamSize;

   uassert(RamIsLargeEnough(instance));

   memset(erdRam, 0, (size_t )erdRamSize);

   Event_Synchronous_Init(&instance->_private.dataChangeEvent);
   instance->interface.OnDataChange = &instance->_private.dataChangeEvent.interface;
}
