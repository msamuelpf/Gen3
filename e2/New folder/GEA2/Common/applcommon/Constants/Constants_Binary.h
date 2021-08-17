/*!
 * @file
 * @brief Commonly used binary constants.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef CONSTANTS_BINARY_H
#define CONSTANTS_BINARY_H

#include <stdbool.h>

enum
{
   ON = true,
   OFF = false,
   SET = true,
   CLEAR = false,
   HIGH = true,
   LOW = false,
   ENABLED = true,
   DISABLED = false
};

extern const bool * const on;
extern const bool * const off;

extern const bool * const set;
extern const bool * const clear;

extern const bool * const high;
extern const bool * const low;

extern const bool * const enabled;
extern const bool * const disabled;

extern const bool constTrue;
extern const bool constFalse;

#endif
