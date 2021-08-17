/*!
 * @file
 * @brief CRC16 calculator that uses a formula.  This method is slow, but uses little ROM.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef CRC16CALCULATOR_FORMULA_H
#define CRC16CALCULATOR_FORMULA_H

#include "I_Crc16Calculator.h"

/*!
 * CRC16 calculator that uses a formula.
 */
extern I_Crc16Calculator_t * const Crc16Calculator_Formula;

#endif
