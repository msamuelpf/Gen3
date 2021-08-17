/*!
 * @file
 * @brief Utility for allocating an arbitrary amount of memory on the stack at runtime.  The amount
 * allocated can be determined at runtime.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

#include <stddef.h>

enum
{
   StackAllocator_MaxSupportedAllocation = 2048
};

/*!
 * Callback invoked after the memory has been allocated.
 * @param context The context provided in the Allocate() call.
 * @param allocatedBlock The block that was allocated by the allocator.
 *
 * @warning Because the block is allocated on the caller's stack, all use of the allocated block
 *    _must_ occur within this callback.  If it is retained and used after this call the result is
 *    undefined.
 */
typedef void (*StackAllocatorCallback_t)(void *context, void *allocatedBlock);

/*!
 * Allocate a block of memory on the stack.
 * @param size The size of the block in bytes.
 * @param callback The function that will be invoked after the block has been allocated.
 * @param context The context parameter that will be passed to the callback.
 */
void StackAllocator_Allocate(size_t size, StackAllocatorCallback_t callback, void *context);

/*!
 * Allocate an aligned block of memory on the stack. This can use more stack than an unaligned allocation,
 *    but is required when allocating data that has an alignment >1 that will be used as more than just a
 *    temporary buffer. If in doubt, ask an expert.
 * @param size The size of the block in bytes.
 * @param callback The function that will be invoked after the block has been allocated.
 * @param context The context parameter that will be passed to the callback.
 */
void StackAllocator_AllocateAligned(size_t size, StackAllocatorCallback_t callback, void *context);

#endif
