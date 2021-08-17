/*!
 * @file
 * @brief WiFi Status LED driver implementation.
 *
 * Copyright General Electric Corporation - GE Confidential - All rights reserved.
 */

#include "DigitalOutput_WiFiStatusLed.h"
#include "iodefineRX210.h"
#include "utils.h"


// just to get it to build I am pretending that the indicator for the WIFI LED is port 2.3
static void Write(I_DigitalOutput_t *instance, bool state)
{
   IGNORE_ARG(instance);

   PORT2.PODR.BIT.B3 = !state;   // active low
}

static const I_DigitalOutput_Api_t api =
   { Write };

static I_DigitalOutput_t instance;

I_DigitalOutput_t * DigitalOutput_WiFiStatusLed_Init(void)
{
	PORT2.PMR.BIT.B3 = 0;
	PORT2.PDR.BIT.B3 = 1;

   instance.api = &api;
   return &instance;
}
