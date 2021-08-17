/*!
 * @file
 * @brief Input for WIFI button on the board.
 *
 * Copyright General Electric Corporation - GE Confidential - All rights reserved.
 */

#include <stdint.h>
#include <stdbool.h>
#include "Input_WiFiButton.h"
#include "iodefineRX210.h"
#include "utils.h"
#include "uassert.h"

// Just to get it to compile I am pretending that the WIFI button input is Port 1.3


static void Read(I_Input_t *instance, void *value)
{
   REINTERPRET(returnData, value, bool *);

   IGNORE_ARG(instance);
   *returnData = !PORT1.PIDR.BIT.B3;     // active low
}

static I_Event_t * GetOnChangeEvent(I_Input_t *_instance)
{
   IGNORE_ARG(_instance);
   uassert(!"OnChange event is not supported for Buttons right now");
   return NULL;
}

static const I_Input_Api_t api =
   { NULL, Read, GetOnChangeEvent };

static I_Input_t instance;

I_Input_t * Input_WiFiButton_Init(void)
{
	PORT1.PMR.BIT.B3 = 0;
	PORT1.PDR.BIT.B3 = 0;

   instance.api = &api;
   return &instance;
}
