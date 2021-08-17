/*!
 * @file
 * @brief Definitions for WiFiNetworkState Erd
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef WIFINETWORKSTATE_H
#define WIFINETWORKSTATE_H

#include <stdint.h>

enum
{
   WiFiNetworkState_Off,
   WiFiNetworkState_ApMode,
   WiFiNetworkState_Connecting,
   WiFiNetworkState_Connected,
   WiFiNetworkState_Connected_Off,
   WiFiNetworkState_Scanning,
   WiFiNetworkState_Reconnecting,
   WiFiNetworkState_Invalid = 0xFF
};
typedef uint8_t WiFiNetworkState_t;

#endif
