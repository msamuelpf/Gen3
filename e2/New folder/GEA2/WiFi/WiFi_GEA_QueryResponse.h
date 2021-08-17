/*!
 * @file
 * @brief Prototypes supporting GEA2 Query/Response from/to the WiFi Module or Broadcast Adr.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFI_GEA_QUERY_RESPONSE_H
#define WIFI_GEA_QUERY_RESPONSE_H

#include "I_Gea2PacketEndpoint.h"
#include "EventSubscription.h"
#include "I_Crc16Calculator.h"


enum
{
   // modify this to change the Fake software version shared with the 0x01 GEA command
   VersionCriticalMajor = 0xDE,
   VersionCriticalMinor = 0xAD,
   VersionNonCriticalMajor = 0xBE,
   VersionNonCriticalMinor = 0xFF,

   PacketResponseRetries = 2,
};

// below fills in the model and serial number for bootloader parametric field 3 and 4 respectively
#define  BOOTLOADER_PARAMETRIC_MODEL_DATA_LENGTH (12)
#define  BOOTLOADER_PARAMETRIC_MODEL_DATA  "WMH74201WDAB"

#define  BOOTLOADER_PARAMETRIC_SERIAL_NUMBER_DATA_LENGTH (9)
#define  BOOTLOADER_PARAMETRIC_SERIAL_NUMBER_DATA  "SN = 0001"

typedef struct
{
   struct
   {
      I_Gea2PacketEndpoint_t *applicationNode;
      EventSubscription_t gea2PacketSubscription;
      I_Crc16Calculator_t *crcCalculator;
      Crc16_t seed;
   } _private;
} WiFi_GEA_QueryResponse_t;

void WiFi_GEA_QueryResponse_Init(
   WiFi_GEA_QueryResponse_t *instance,
   I_Gea2PacketEndpoint_t *applicationNode,
   I_Crc16Calculator_t *crcCalculator,
   Crc16_t seed);

#endif
