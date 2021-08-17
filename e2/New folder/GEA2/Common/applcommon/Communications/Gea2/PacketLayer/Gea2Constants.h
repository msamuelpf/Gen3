/*!
 * @file
 * @brief GEA2 constants.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2CONSTANTS_H
#define GEA2CONSTANTS_H

#include "CrcSeed.h"

#define GEA2_ESC (0xE0)
#define GEA2_ACK (0xE1)
#define GEA2_STX (0xE2)
#define GEA2_ETX (0xE3)

#define GEA2_BCAST (0xFF)
#define GEA2_BCAST_MASK (0xF0)

#define GEA2_CRC_SEED (CrcSeed)

#define GEA2_INTERBYTE_TIMEOUT_MSEC (6)
#define GEA2_REFLECTION_TIMEOUT_MSEC (GEA2_INTERBYTE_TIMEOUT_MSEC)
#define GEA2_ACK_TIMEOUT_MSEC (8)

enum
{
   Gea2Esc = GEA2_ESC,
   Gea2Ack = GEA2_ACK,
   Gea2Stx = GEA2_STX,
   Gea2Etx = GEA2_ETX,

   Gea2Broadcast = GEA2_BCAST,
   Gea2BroadcastMask = GEA2_BCAST_MASK,

   Gea2CrcSeed_B = GEA2_CRC_SEED
};

#endif
