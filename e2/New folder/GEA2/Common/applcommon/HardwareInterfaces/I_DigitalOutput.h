/*!
 * @file
 * @brief Generic Digital Output Interface for a single GPIO object.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_DIGITALOUTPUT_H
#define I_DIGITALOUTPUT_H

#include <stdbool.h>

struct I_DigitalOutput_Api_t;

typedef struct
{
   /*!
    * API for interacting with Digital Output
    */
   const struct I_DigitalOutput_Api_t *api;
} I_DigitalOutput_t;

typedef struct I_DigitalOutput_Api_t
{
   /*!
    * Function to set the state of the Digital Output
    * @pre instance != NULL
    * @param instance - Instance of the Digital Output
    * @param state - Digital Output state
    */
   void (*Write)(I_DigitalOutput_t *instance, const bool state);
} I_DigitalOutput_Api_t;

#define DigitalOutput_Write(instance, state) \
   (instance)->api->Write((instance), (state))

#endif
