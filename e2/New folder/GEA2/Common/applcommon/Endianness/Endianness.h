/*!
 * @file
 * @brief Endianness typedefs.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef ENDIANNESS_H
#define ENDIANNESS_H

#include <stdint.h>

enum
{
   Endianness_Little,
   Endianness_Big
};
typedef uint8_t Endianness_t;

#endif
