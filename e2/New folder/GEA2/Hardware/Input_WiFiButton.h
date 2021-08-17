/*!
 * @file
 * @brief Input for WiFi button on the board.
 *
 * Copyright General Electric Corporation - GE Confidential - All rights reserved.
 */

#ifndef INPUT_WIFI_BUTTON_H
#define INPUT_WIFI_BUTTON_H

#include "I_Input.h"

/*!
 * Initialize the WiFi button input
 * @return The WiFi Button Input interface.
 */
I_Input_t * Input_WiFiButton_Init(void);

#endif
