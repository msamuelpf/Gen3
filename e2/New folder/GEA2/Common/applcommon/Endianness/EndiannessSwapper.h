/*!
 * @file
 * @brief Component that can swap the endianness of a field unconditionally or to a target endianness.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef ENDIANNESSSWAPPER_H
#define ENDIANNESSSWAPPER_H

#include <stddef.h>
#include "Endianness.h"

/*!
 * Swap the endianness of a field.
 * @param field The field to swap.
 * @param fieldSize The size of the field to swap.
 */
void EndiannessSwapper_SwapField(void *field, size_t fieldSize);

/*!
 * Convert (if necessary) a field in native endianness to a target endianness.
 * @param field The field to convert.
 * @param fieldSize The size of the field to convert.
 * @param target The target endianness that the field will be in after the call.
 */
void EndiannessSwapper_ConvertFieldFromNativeToTarget(void *field, size_t fieldSize, Endianness_t target);

/*!
 * Convert (if necessary) a field to native endianness from a source endianness.
 * @param field The field to convert.
 * @param fieldSize The size of the field to convert.
 * @param source The source endianness that the field is currently in.
 */
void EndiannessSwapper_ConvertFieldFromSourceToNative(void *field, size_t fieldSize, Endianness_t source);

#endif
