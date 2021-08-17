/*!
 * @file
 * @brief Digital output for controlling the WiFi Status LED
 *
 * Copyright General Electric Corporation - GE Confidential - All rights reserved.
 */

#ifndef DIGITAL_OUTPUT_WIFI_STATUS_LED_H
#define DIGITAL_OUTPUT_WIFI_STATUS_LED_H

#include "I_DigitalOutput.h"

/*!
 * Initialize the WiFi Status LED.
 * @return The WiFi Status LED interface.
 */
I_DigitalOutput_t * DigitalOutput_WiFiStatusLed_Init(void);

#endif
