/*!
 * @file
 * @brief Implementation of stack allocator.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "StackAllocator.h"
#include "AlignmentDetector.h"
#include "utils.h"
#include "uassert.h"

typedef void (*AllocatorWorker_t)(StackAllocatorCallback_t callback, void *context);

typedef struct
{
   size_t maxSize;
   AllocatorWorker_t worker;
} AllocatorWorkerMapping_t;

#define WORKER_DEFINITION(size) \
   static void Worker##size(StackAllocatorCallback_t callback, void *context) \
   { \
      uint8_t block[size]; \
      callback(context, block); \
   }

WORKER_DEFINITION(8)
WORKER_DEFINITION(16)
WORKER_DEFINITION(32)
WORKER_DEFINITION(64)
WORKER_DEFINITION(128)
WORKER_DEFINITION(256)
WORKER_DEFINITION(512)
WORKER_DEFINITION(1024)
WORKER_DEFINITION(1536)
WORKER_DEFINITION(2048)

#define WORKER_TABLE_ENTRY(size) { size, Worker##size }

static const AllocatorWorkerMapping_t workerTable[] =
   {
   WORKER_TABLE_ENTRY(8),
   WORKER_TABLE_ENTRY(16),
   WORKER_TABLE_ENTRY(32),
   WORKER_TABLE_ENTRY(64),
   WORKER_TABLE_ENTRY(128),
   WORKER_TABLE_ENTRY(256),
   WORKER_TABLE_ENTRY(512),
   WORKER_TABLE_ENTRY(1024),
   WORKER_TABLE_ENTRY(1536),
   WORKER_TABLE_ENTRY(2048)
   };

void StackAllocator_Allocate(size_t size, StackAllocatorCallback_t callback, void *context)
{
   uint8_t i;

   for(i = 0; i < NUM_ELEMENTS(workerTable); i++)
   {
      if(size <= workerTable[i].maxSize)
      {
         workerTable[i].worker(callback, context);
         return;
      }
   }

   uassert(!"Allocation size not supported, need to expand implementation");
}

#define STRICTEST_ALIGNMENT_TYPE long long

#define ALIGNED_WORKER_DEFINITION(size) \
   static void AlignedWorker##size(StackAllocatorCallback_t callback, void *context) \
   { \
   STRICTEST_ALIGNMENT_TYPE block[size / sizeof(STRICTEST_ALIGNMENT_TYPE) + !!(size % sizeof(STRICTEST_ALIGNMENT_TYPE))]; \
      callback(context, block); \
   }

ALIGNED_WORKER_DEFINITION(8)
ALIGNED_WORKER_DEFINITION(16)
ALIGNED_WORKER_DEFINITION(32)
ALIGNED_WORKER_DEFINITION(64)
ALIGNED_WORKER_DEFINITION(128)
ALIGNED_WORKER_DEFINITION(256)
ALIGNED_WORKER_DEFINITION(512)
ALIGNED_WORKER_DEFINITION(1024)
ALIGNED_WORKER_DEFINITION(1536)
ALIGNED_WORKER_DEFINITION(2048)

#define ALIGNED_WORKER_TABLE_ENTRY(size) { size, AlignedWorker##size }

static const AllocatorWorkerMapping_t alignedWorkerTable[] =
   {
   ALIGNED_WORKER_TABLE_ENTRY(8),
   ALIGNED_WORKER_TABLE_ENTRY(16),
   ALIGNED_WORKER_TABLE_ENTRY(32),
   ALIGNED_WORKER_TABLE_ENTRY(64),
   ALIGNED_WORKER_TABLE_ENTRY(128),
   ALIGNED_WORKER_TABLE_ENTRY(256),
   ALIGNED_WORKER_TABLE_ENTRY(512),
   ALIGNED_WORKER_TABLE_ENTRY(1024),
   ALIGNED_WORKER_TABLE_ENTRY(1536),
   ALIGNED_WORKER_TABLE_ENTRY(2048),
   };

void StackAllocator_AllocateAligned(size_t size, StackAllocatorCallback_t callback, void *context)
{
   uint8_t i;

   uassert(sizeof(STRICTEST_ALIGNMENT_TYPE) >= AlignmentDetector_GetAlignment());

   for(i = 0; i < NUM_ELEMENTS(workerTable); i++)
   {
      if(size <= workerTable[i].maxSize)
      {
         alignedWorkerTable[i].worker(callback, context);
         return;
      }
   }

   uassert(!"Allocation size not supported, need to expand implementation");
}
