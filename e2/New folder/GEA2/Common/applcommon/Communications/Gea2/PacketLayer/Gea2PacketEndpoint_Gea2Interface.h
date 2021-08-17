/*!
 * @file
 * @brief Adapter to convert a GEA2 interface into a GEA2 packet endpoint.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2PACKETENDPOINT_GEA2INTERFACE_H
#define GEA2PACKETENDPOINT_GEA2INTERFACE_H

#include "I_Gea2PacketEndpoint.h"
#include "I_Gea2Interface.h"
#include "Event_Synchronous.h"

typedef struct
{
   I_Gea2PacketEndpoint_t interface;

   struct
   {
      I_Gea2Interface_t *gea2Interface;
      Event_Synchronous_t onReceive;
      EventSubscription_t interfaceReceiveSubscription;
   } _private;
} Gea2PacketEndpoint_Gea2Interface_t;

/*!
 * Initialize an I_Gea2Interface to I_Gea2PacketEndpoint adapter.
 * @param instance The adapter.
 * @param gea2Interface The GEA2 interface to adapt.
 */
void Gea2PacketEndpoint_Gea2Interface_Init(
   Gea2PacketEndpoint_Gea2Interface_t *instance,
   I_Gea2Interface_t *gea2Interface);

#endif
