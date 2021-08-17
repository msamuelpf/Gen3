/*!
 * @file
 * @brief CRC16 calculation interface.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_CRC16CALCULATOR_H
#define I_CRC16CALCULATOR_H

#include <stddef.h>

#include "Crc16.h"

struct I_Crc16Calculator_Api_t;

/*!
 * A CRC16 calculator.
 */
typedef struct
{
   /*!
    * API for interacting with the CRC16 calculator.
    */
   const struct I_Crc16Calculator_Api_t *api;
} I_Crc16Calculator_t;

/*!
 * API for interacting with the CRC16 calculator.
 */
typedef struct I_Crc16Calculator_Api_t
{
   /*!
    * Generate a CRC of a byte string.
    * @pre calculator != NULL
    * @param calculator The CRC calculator to use.
    * @param seed The seed value.
    * @param start Starting address.
    * @param count The number of bytes to process.
    * @return The CRC16 of the byte string.
    */
   Crc16_t (*ProcessString)(I_Crc16Calculator_t *instance, Crc16_t seed, const void *start, size_t count);
} I_Crc16Calculator_Api_t;

#define Crc16Calculator_ProcessString(instance, seed, start, count) \
   (instance)->api->ProcessString((instance), (seed), (start), (count))

#endif
