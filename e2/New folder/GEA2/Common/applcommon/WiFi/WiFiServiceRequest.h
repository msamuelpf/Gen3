/*!
 * @file
 * @brief WiFiServiceRequest_t definition.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFISERVICEREQUEST_H
#define WIFISERVICEREQUEST_H

#include <stdint.h>

enum
{
   WiFiServiceRequest_RemainInCurrentState,
   WiFiServiceRequest_Connect,
   WiFiServiceRequest_Disconnect
};
typedef uint8_t WiFiServiceRequest_t;

#endif
