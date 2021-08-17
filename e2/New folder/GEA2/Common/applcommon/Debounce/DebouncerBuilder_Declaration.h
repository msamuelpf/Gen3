/*!
 * @file
 * @brief Can be used to generate declarations for an implementation of a debouncer.
 *
 * #define DEBOUNCED_TYPE int
 * #define DEBOUNCER_NAME Debouncer_int
 * #define ACCESS_SPECIFIER static
 * #include "DebouncerBuilder_Declaration.h"
 *
 * This will generate a static declaration of an integer debouncer (Debouncer_int_t).
 *
 * #define DEBOUNCED_TYPE bool
 * #define DEBOUNCER_NAME Debouncer_Boolean
 * #define ACCESS_SPECIFIER extern
 * #include "DebouncerBuilder_Declaration.h"
 *
 * And this will generate an extern declaration of a bool debouncer (Debouncer_Boolean_t).  Notice
 * that the debouncer can be named independently of the debounced type.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdint.h>
#include "utils.h"

#define DEBOUNCER_TYPE MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _t)

typedef struct
{
   struct
   {
      DEBOUNCED_TYPE raw;
      DEBOUNCED_TYPE debounced;
      uint8_t currentCount;
      uint8_t maxCount;
   } _private;
} DEBOUNCER_TYPE;

/*!
 * Initialize a debouncer.
 * @pre instance != NULL
 * @param instance The debouncer.
 * @param initial The initial debounced value.
 * @param maxCount The number of times that a value must be processed before being debounced.
 */
ACCESS_SPECIFIER void MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Init)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE initial, uint8_t maxCount);

/*!
 * Reset a debouncer by specifying an initial state.
 * @pre instance != NULL
 * @param instance The debouncer.
 * @param initial The initial debounced value.  This will be set as the debounced value and the count reset.
 */
ACCESS_SPECIFIER void MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Reset)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE initial);

/*!
 * Process the current input.
 * @pre instance != NULL
 * @param instance The debouncer.
 * @param value The current value.  If the value has been stable long enough, it will become the new value.
 */
ACCESS_SPECIFIER bool MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Process)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE value);

/*!
 * Get the current debounced value.
 * @pre instance != NULL
 * @param instance The debouncer.
 * @return The current debounced value.
 */
ACCESS_SPECIFIER DEBOUNCED_TYPE MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _GetDebounced)(DEBOUNCER_TYPE *instance);

#undef ACCESS_SPECIFIER
#undef DEBOUNCED_TYPE
#undef DEBOUNCER_NAME
#undef DEBOUNCER_TYPE
