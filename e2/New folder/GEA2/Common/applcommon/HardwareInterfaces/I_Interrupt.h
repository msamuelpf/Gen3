/*!
 * @file
 * @brief Generic interrupt interface.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_INTERRUPT_H
#define I_INTERRUPT_H

#include "Event_Synchronous.h"

/*!
 * Generic interrupt.  API is an I_Event_t only.  No functions.
 */
typedef struct
{
   /*!
    * This event is raised when an interrupt occurs.  There are no event args.
    */
   I_Event_t *OnInterrupt;
} I_Interrupt_t;

#endif

