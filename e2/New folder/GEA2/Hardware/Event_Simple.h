/*!
 * @file
 * @brief This has been deprecated in favor of Event_Synchronous.  For now it will remain in stub
 * form (and delegate to Event_Synchronous).  New code should target Event_Synchronous instead.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef EVENT_SIMPLE_H
#define EVENT_SIMPLE_H

#include "Event_Synchronous.h"

typedef Event_Synchronous_t Event_Simple_t;

#define Event_Simple_Init Event_Synchronous_Init
#define Event_Simple_Publish Event_Synchronous_Publish

#endif
