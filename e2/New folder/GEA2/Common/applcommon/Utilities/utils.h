/*!
 * @file
 * @brief Miscellaneous utilities and macros.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// Contortions like these are necessary to get the arguments of concatenate to be macro expanded
// before the concatenation occurs
#define _MACRO_SAFE_CONCATENATE(a, b) a ## b
#define MACRO_SAFE_CONCATENATE(a, b) _MACRO_SAFE_CONCATENATE(a, b)
#define CONCAT MACRO_SAFE_CONCATENATE

// Used to perform a compile-time check that can't be done with the pre-processor (ie: sizeof checks)
#define STATIC_ASSERT(cond) typedef int MACRO_SAFE_CONCATENATE(assert, __LINE__)[(cond) ? 1 : -1]

#define unless(cond) if(!(cond))

#define NUM_ELEMENTS(array) (sizeof(array)/sizeof(array[0]))
#define ELEMENT_COUNT NUM_ELEMENTS
#define ELEMENT_SIZE(array) (sizeof(array[0]))

#ifndef OFFSET_OF
#define OFFSET_OF offsetof
#endif

#define MEMBER_SIZE(container_type, field_name) \
   sizeof(((container_type *)0)->field_name)

#define IS_SIGNED(integer_type) \
   (((integer_type)-1) < 0)

// void * cast is necessary to avoid spurious alignment warnings
#define CONTAINER_OF(container_type, field_name, pointer_to_field) \
   (container_type *)((void *)((char *)pointer_to_field - OFFSET_OF(container_type, field_name)))

#define IGNORE_ARG(arg) (void)(arg)
#define IGNORE(arg) IGNORE_ARG(arg)

#define REINTERPRET(new_name, cast_me, new_type) \
   new_type new_name = (new_type)cast_me

#define REINTERPRET_CAST(new_name, cast_me, new_type) \
   REINTERPRET(new_name, cast_me, new_type)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define CLAMP(value, min, max) MAX(MIN((value), (max)), (min))

#define DIVIDE_AND_ROUND(n, d) (((n) + (((n) >= 0) ^ ((d) >= 0) ? -1 : 1) * ((d) >> 1))/(d))
#define UNSIGNED_DIVIDE_AND_ROUND(n, d) (((n) + ((d) >> 1))/(d))

#define DIVIDE_WITH_CEILING(n, d) ((n) / (d) + (((n) % (d) != 0) ? !(((n) > 0)^((d) > 0)) : 0))
#define UNSIGNED_DIVIDE_WITH_CEILING(n, d) (((n) + ((d) - 1))/(d))

#define TRUNCATE_UNSIGNED_ADDITION(a, b, max) ((((a)/(max))||((b)/(max))) ? (max) : (((max - a) > (b)) ? (a + b) : (max)))
#define TRUNCATE_UNSIGNED_SUBTRACTION(a, b) (((a) > (b)) ? (a - b) : (0))

#define INSTANCE_DATA (instance->_private)

#define IN_RANGE(low, value, high) (((low) <= (value)) && ((value) <= (high)))
#define BETWEEN(low, value, high) (((low) < (value)) && ((value) < (high)))

#define BIT_SET(word, bit_index) \
   (word) |= 1 << (bit_index)

#define BIT_CLEAR(word, bit_index) \
   (word) &= ~(1 << (bit_index))

#define BIT_STATE(word, bit_index) \
   !!((word) & (1 << (bit_index)))

#define BIT_WRITE(word, bit_index, state) \
   if(state) BIT_SET(word, bit_index); \
   else BIT_CLEAR(word, bit_index)

#define NUMBER_OF_BYTES(bits) \
   ((bits / 8) + !!(bits % 8))

#define BIT_MASK(bit_index) \
   (1 << (bit_index))

#endif
