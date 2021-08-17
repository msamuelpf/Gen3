/*!
 * @file
 * @brief Implementation of the alignment detector.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "AlignmentDetector.h"
#include "utils.h"

typedef struct
{
   uint8_t x;
   uint64_t y;
} AlignmentTestU64_t;

typedef struct
{
   uint8_t x;
   long long y;
} AlignmentTestLongLong_t;

typedef struct
{
   uint8_t x;
   void *y;
} AlignmentTestPointer_t;

typedef struct
{
   uint8_t x;
   const void *y;
} AlignmentTestConstPointer_t;

uint8_t AlignmentDetector_GetAlignment(void)
{
   uint8_t u64Alignment = sizeof(AlignmentTestU64_t) - sizeof(uint64_t);
   uint8_t longLongAlignment = sizeof(AlignmentTestLongLong_t) - sizeof(long long);
   uint8_t pointerAlignment = sizeof(AlignmentTestPointer_t) - sizeof(void *);
   uint8_t constPointerAlignment = sizeof(AlignmentTestConstPointer_t) - sizeof(const void *);

   return MAX(u64Alignment, MAX(longLongAlignment, MAX(pointerAlignment, constPointerAlignment)));
}
