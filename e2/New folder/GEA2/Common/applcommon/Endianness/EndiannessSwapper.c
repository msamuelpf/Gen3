/*!
 * @file
 * @brief Endianness swapper.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "EndiannessSwapper.h"
#include "EndiannessDetector.h"
#include "utils.h"

void EndiannessSwapper_SwapField(void *_field, size_t fieldSize)
{
   REINTERPRET(field, _field, uint8_t *);

   size_t i;
   for(i = 0; i < fieldSize / 2; i++)
   {
      uint8_t temp = field[i];
      field[i] = field[fieldSize - (i + 1)];
      field[fieldSize - (i + 1)] = temp;
   }
}

void EndiannessSwapper_ConvertFieldFromNativeToTarget(void *field, size_t fieldSize, Endianness_t target)
{
   if(EndiannessDetector_GetEndianness() != target)
   {
      EndiannessSwapper_SwapField(field, fieldSize);
   }
}

void EndiannessSwapper_ConvertFieldFromSourceToNative(void *field, size_t fieldSize, Endianness_t source)
{
   EndiannessSwapper_ConvertFieldFromNativeToTarget(field, fieldSize, source);
}
