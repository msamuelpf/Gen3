/*!
 * @file
 * @brief WiFiServiceState_t definition.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFISERVICESTATE_H
#define WIFISERVICESTATE_H

#include <stdint.h>

enum
{
   WiFiServiceState_Unknown,
   WiFiServiceState_Connecting,
   WiFiServiceState_Connected,
   WiFiServiceState_Disconnected
};
typedef uint8_t WiFiServiceState_t;

#endif
