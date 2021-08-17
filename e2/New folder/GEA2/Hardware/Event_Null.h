/*!
 * @file
 * @brief Event that never publishes and doesn't keep a subscription list.  Useful when you need to
 * provide an event but have no event to provide.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef EVENT_NULL_H
#define EVENT_NULL_H

#include "I_Event.h"

/*!
 * Get the null event singleton instance.
 * @return The null event singleton instance.
 */
I_Event_t * Event_Null_GetInstance(void);

#endif
