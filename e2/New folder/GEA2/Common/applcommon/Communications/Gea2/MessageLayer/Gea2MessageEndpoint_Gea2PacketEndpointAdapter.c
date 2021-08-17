/*!
 * @file
 * @brief Implementation of packet endpoint to message endpoint adapter.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include <limits.h>
#include "Gea2MessageEndpoint_Gea2PacketEndpointAdapter.h"
#include "uassert.h"
#include "utils.h"

static void Send(I_Gea2MessageEndpoint_t *_instance, Gea2Message_t *message, const uint8_t retries)
{
   REINTERPRET(instance, _instance, Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t *);
   REINTERPRET(packet, message, Gea2Packet_t *);

   Gea2PacketEndpoint_Send(instance->_private.applicationEndpoint, packet, retries);
}

static I_Event_t * GetOnReceiveEvent(I_Gea2MessageEndpoint_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t *);
   return &instance->_private.messageEndpointOnReceiveEvent.interface;
}

static const I_Gea2MessageEndpoint_Api_t api =
   { Send, GetOnReceiveEvent };

static void PacketReceivedFromApplicationEndpoint(void *context, const void *_args)
{
   REINTERPRET(receivedArgs, _args, const Gea2PacketEndpointOnReceiveArgs_t *);

   if(receivedArgs->packet->payloadLength > 0)
   {
      REINTERPRET(instance, context, Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t *);
      Gea2MessageEndpointOnReceiveArgs_t publishArgs =
         { (const Gea2Message_t *)receivedArgs->packet };

      Event_Synchronous_Publish(&instance->_private.messageEndpointOnReceiveEvent, &publishArgs);
   }
}

void Gea2MessageEndpoint_Gea2PacketEndpointAdapter_Init(Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t *instance,
   I_Gea2PacketEndpoint_t *applicationEndpoint)
{
   instance->interface.api = &api;
   instance->_private.applicationEndpoint = applicationEndpoint;

   EventSubscription_Init(&instance->_private.applicationEndpointOnReceiveSubscription, instance,
      PacketReceivedFromApplicationEndpoint);
   Event_Subscribe(Gea2PacketEndpoint_GetOnReceiveEvent(applicationEndpoint), &instance->_private.applicationEndpointOnReceiveSubscription);

   Event_Synchronous_Init(&instance->_private.messageEndpointOnReceiveEvent);
}
