/*!
 * @file
 * @brief ERD typedef.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef ERD_H
#define ERD_H

#include <stdint.h>

enum
{
   Erd_Invalid = -1  // Cubesuite uses only int16_t 0xFFFF
};

/*!
 * Entity Reference Designator - basically an identifier for a data element.
 */
typedef uint16_t Erd_t;

#endif
