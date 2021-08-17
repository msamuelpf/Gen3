/*!
 * @file
 * @brief Utilities that allow XMacros to be written more succinctly.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef XMACROUTILS_H
#define XMACROUTILS_H

#include <stdbool.h>

#define COMMA ,

#define OR_11 1
#define OR_10 1
#define OR_01 1
#define OR_00 0
#define OR(_left, _right) CONCAT(CONCAT(OR_, _left), _right)

#define INCLUDE_OR_DEFAULT_1(_x, _default) _x
#define INCLUDE_OR_DEFAULT_0(_x, _default) _default

#define INCLUDE_1(_x) _x
#define INCLUDE_0(_x)

#endif
