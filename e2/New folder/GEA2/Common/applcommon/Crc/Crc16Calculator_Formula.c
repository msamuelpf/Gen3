/*!
 * @file
 * @brief Implementation of formula-based CRC16 calculator.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "CrcSeed.h"
#include "Crc16Calculator_Formula.h"
#include "uassert.h"
#include "utils.h"

static Crc16_t ProcessByte(I_Crc16Calculator_t *instance, const Crc16_t seed, const uint8_t byte)
{
   size_t index;
   Crc16_t crc = seed;

   IGNORE_ARG(instance);

   crc ^= ((Crc16_t)byte << 8);

   for(index = 8; index > 0; --index)
   {
      if(crc & 0x8000)
      {
         crc = (Crc16_t)(crc << 1 ^ CrcSeed);
      }
      else
      {
         crc <<= 1;
      }
   }

   return crc;
}

static Crc16_t ProcessString(I_Crc16Calculator_t *instance, Crc16_t seed, const void *start, size_t count)
{
   size_t index;
   Crc16_t crc = seed;

   for(index = 0; index < count; index++)
   {
      const uint8_t current = *((const uint8_t *)start + index);
      crc = ProcessByte(instance, crc, current);
   }

   return crc;
}

static const I_Crc16Calculator_Api_t api =
   { ProcessString };

static I_Crc16Calculator_t calculator =
   {
      &api
   };

I_Crc16Calculator_t * const Crc16Calculator_Formula = &calculator;
