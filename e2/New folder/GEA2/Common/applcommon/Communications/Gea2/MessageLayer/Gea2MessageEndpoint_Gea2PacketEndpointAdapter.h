/*!
 * @file
 * @brief Adapter that takes a Gea2PacketEndpoint and turns it into a Gea2MessageEndpoint for
 * increased convenience when dealing with Gea2Messages instead of Gea2Packets.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2MESSAGEENDPOINT_GEA2PACKETENDPOINTADAPTER_H
#define GEA2MESSAGEENDPOINT_GEA2PACKETENDPOINTADAPTER_H

#include "I_Gea2MessageEndpoint.h"
#include "I_Gea2PacketEndpoint.h"
#include "Event_Synchronous.h"

/*!
 * packet endpoint to message endpoint adapter.  Struct members should be considered private.
 */
typedef struct
{
   I_Gea2MessageEndpoint_t interface;

   struct
   {
      I_Gea2PacketEndpoint_t *applicationEndpoint;
      Event_Synchronous_t messageEndpointOnReceiveEvent;
      EventSubscription_t applicationEndpointOnReceiveSubscription;
   } _private;
} Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t;

/*!
 * Initialize an packet endpoint to message endpoint adapter.  Will adapt using the provided
 * packet endpoint.
 * @pre instance != NULL
 * @pre applicationEndpoint != NULL
 * @param instance The adapter to initialize.
 * @param applicationEndpoint The packet endpoint to adapt.
 */
void Gea2MessageEndpoint_Gea2PacketEndpointAdapter_Init(Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t *instance,
   I_Gea2PacketEndpoint_t *applicationEndpoint);

#endif
