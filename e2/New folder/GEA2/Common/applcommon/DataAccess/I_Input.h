/*!
 * @file
 * @brief Generic input interface.  The type that's read is not specified in the definition and should
 * be specified by contract when used.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_INPUT_H
#define I_INPUT_H

#include "I_Event.h"

struct I_Input_Api_t;

typedef struct
{
   const struct I_Input_Api_t *api;
} I_Input_t;

typedef struct I_Input_Api_t
{
   /*!
    * Defined only to allow the APIs for inputs and outputs to be compatible.
    */
   void (*OutputCompatibility)(I_Input_t *instance, const void *value);

   /*!
    * Read a value.
    * @pre instance != NULL
    * @pre value != NULL
    * @param instance The input.
    * @param value A pointer to where the read value will be placed.
    * @note value is an output parameter.
    */
   void (*Read)(I_Input_t *instance, void *value);

   /*!
    * Access the OnChange event which is raised when the input's data changes.
    * Event arguments are a pointer to the new value.
    * @pre instance != NULL
    * @param instance The input
    * @return OnChange I_Event_t pointer
    */
   I_Event_t * (*GetOnChangeEvent)(I_Input_t *instance);
} I_Input_Api_t;

#define Input_Read(instance, value) \
   (instance)->api->Read((instance), (value))

#define Input_GetOnChangeEvent(instance) \
   (instance)->api->GetOnChangeEvent((instance))

#endif
