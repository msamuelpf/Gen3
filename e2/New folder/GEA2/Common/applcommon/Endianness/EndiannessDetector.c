/*!
 * @file
 * @brief Endianness detector.  What more do you want?
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "EndiannessDetector.h"

Endianness_t EndiannessDetector_GetEndianness(void)
{
   const uint16_t test = 0x11FF;

   return (*((uint8_t *)&test) == 0xFF) ? Endianness_Little : Endianness_Big;
}
