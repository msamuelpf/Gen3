/*!
 * @file
 * @brief DataSource wrapper that selectively 'corrects' endianness for a list of ERDs.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include <stdbool.h>
#include "DataSource_EndiannessSwapped.h"
#include "StackAllocator.h"
#include "utils.h"
#include "uassert.h"
#include "EndiannessSwapper.h"

typedef struct
{
   DataSource_EndiannessSwapped_t *instance;
   uint8_t *data;
} IterateContext_t;

static void SwapDataForErdWorker(void *_context, I_Iterator_t *iterator)
{
   REINTERPRET(context, _context, IterateContext_t *);

   DataSource_EndiannessSwappedSwappedField_t swapData;

   foreach(iterator, &swapData)
   {
      EndiannessSwapper_SwapField(context->data + swapData.fieldOffset, swapData.fieldSize);
   }
}

static void SwapDataForErd(DataSource_EndiannessSwapped_t *instance, Erd_t erd, void *data)
{
   IterateContext_t context;
   context.instance = instance;
   context.data = data;
   ConstMultiMap_Find(instance->_private.swapMap, &erd, SwapDataForErdWorker, &context);
}

typedef struct
{
   DataSource_EndiannessSwapped_t *instance;
   Erd_t erd;
   const uint8_t *data;
   uint8_t dataSize;
} StackAllocatorDataChangedContext_t;

static void StackAllocatorDataChangedCallback(void *_context, void *data)
{
   REINTERPRET(context, _context, const StackAllocatorDataChangedContext_t *);
   DataSourceOnDataChangeArgs_t republishArgs;

   memcpy(data, context->data, context->dataSize);
   SwapDataForErd(context->instance, context->erd, data);

   republishArgs.erd = context->erd;
   republishArgs.data = data;
   Event_Synchronous_Publish(&context->instance->_private.concreteOnDataChangeEvent, &republishArgs);
}

static void DataChanged(void *_context, const void *_args)
{
   REINTERPRET(instance, _context, DataSource_EndiannessSwapped_t *);
   REINTERPRET(args, _args, const DataSourceOnDataChangeArgs_t *);
   StackAllocatorDataChangedContext_t context;
   context.instance = instance;
   context.erd = args->erd;
   context.data = args->data;
   context.dataSize = DataSource_SizeOf(instance->_private.wrappedDataSource, args->erd);
   StackAllocator_AllocateAligned(context.dataSize, StackAllocatorDataChangedCallback, &context);
}

static void Read(I_DataSource_t *_instance, const Erd_t erd, void *data)
{
   REINTERPRET(instance, _instance, DataSource_EndiannessSwapped_t *);

   DataSource_Read(instance->_private.wrappedDataSource, erd, data);
   SwapDataForErd(instance, erd, data);
}

typedef struct
{
   DataSource_EndiannessSwapped_t *instance;
   Erd_t erd;
   const uint8_t *data;
   uint8_t dataSize;
} StackAllocatorWriteContext_t;

static void StackAllocatorWriteCallback(void *_context, void *data)
{
   REINTERPRET(context, _context, const StackAllocatorWriteContext_t *);

   memcpy(data, context->data, context->dataSize);
   SwapDataForErd(context->instance, context->erd, data);

   DataSource_Write(context->instance->_private.wrappedDataSource, context->erd, data);
}

static void Write(I_DataSource_t *_instance, const Erd_t erd, void const *data)
{
   REINTERPRET(instance, _instance, DataSource_EndiannessSwapped_t *);
   StackAllocatorWriteContext_t context;
   context.instance = instance;
   context.erd = erd;
   context.data = data;
   context.dataSize = DataSource_SizeOf(instance->_private.wrappedDataSource, erd);
   StackAllocator_AllocateAligned(context.dataSize, StackAllocatorWriteCallback, &context);
}

static bool Has(const I_DataSource_t *_instance, const Erd_t erd)
{
   REINTERPRET(instance, _instance, DataSource_EndiannessSwapped_t *);
   return DataSource_Has(instance->_private.wrappedDataSource, erd);
}

static uint8_t SizeOf(const I_DataSource_t *_instance, const Erd_t erd)
{
   REINTERPRET(instance, _instance, DataSource_EndiannessSwapped_t *);
   return DataSource_SizeOf(instance->_private.wrappedDataSource, erd);
}

static const I_DataSource_Api_t api =
   { Read, Write, Has, SizeOf };

void DataSource_EndiannessSwapped_Init(
   DataSource_EndiannessSwapped_t *instance,
   I_DataSource_t *dataSourceToWrap,
   I_ConstMultiMap_t *swapMap)
{
   instance->interface.api = &api;
   instance->interface.OnDataChange = &instance->_private.concreteOnDataChangeEvent.interface;

   instance->_private.wrappedDataSource = dataSourceToWrap;
   instance->_private.swapMap = swapMap;

   Event_Synchronous_Init(&instance->_private.concreteOnDataChangeEvent);

   EventSubscription_Init(&instance->_private.dataChangeSubscription, instance, DataChanged);
   Event_Subscribe(dataSourceToWrap->OnDataChange, &instance->_private.dataChangeSubscription);
}
