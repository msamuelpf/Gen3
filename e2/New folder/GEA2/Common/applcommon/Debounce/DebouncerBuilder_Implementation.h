/*!
 * @file
 * @brief Can be used to generate an implementation of a debouncer.  Declarations must have been
 * previously generated.
 *
 * #define DEBOUNCED_TYPE int
 * #define DEBOUNCER_NAME Debouncer_int
 * #define ACCESS_SPECIFIER static
 * #include "DebouncerBuilder_Implementation.h"
 *
 * This will generate a static implementation of an integer debouncer (Debouncer_int_t).
 *
 * #define DEBOUNCED_TYPE bool
 * #define DEBOUNCER_NAME Debouncer_Boolean
 * #define ACCESS_SPECIFIER extern
 * #include "DebouncerBuilder_Implementation.h"
 *
 * And this will generate an extern implementation of a bool debouncer (Debouncer_Boolean_t).  Notice
 * that the debouncer can be named independently of the debounced type.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "uassert.h"

#define DEBOUNCER_TYPE MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _t)

ACCESS_SPECIFIER void MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Init)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE initial, uint8_t maxCount)
{
   uassert(instance);
   uassert(maxCount);

   instance->_private.debounced = initial;
   instance->_private.maxCount = maxCount;
   instance->_private.raw = initial;
}

ACCESS_SPECIFIER void MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Reset)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE initial)
{
   uassert(instance);

   instance->_private.debounced = initial;
   instance->_private.currentCount = 0;
}

ACCESS_SPECIFIER bool MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _Process)(DEBOUNCER_TYPE *instance, DEBOUNCED_TYPE value)
{
   bool changed = false;

   uassert(instance);

   if((instance->_private.raw == value) && (value != instance->_private.debounced))
   {
      instance->_private.currentCount++;
   }
   else
   {
      instance->_private.currentCount = 1;
   }

   if(instance->_private.currentCount >= instance->_private.maxCount)
   {
      if(instance->_private.debounced != value)
      {
         instance->_private.debounced = value;
         changed = true;
      }
   }

   instance->_private.raw = value;

   return changed;
}

ACCESS_SPECIFIER DEBOUNCED_TYPE MACRO_SAFE_CONCATENATE(DEBOUNCER_NAME, _GetDebounced)(DEBOUNCER_TYPE *instance)
{
   uassert(instance);

   return instance->_private.debounced;
}

#undef ACCESS_SPECIFIER
#undef DEBOUNCED_TYPE
#undef DEBOUNCER_NAME
#undef DEBOUNCER_TYPE
