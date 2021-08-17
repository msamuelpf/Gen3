/*!
 * @file
 * @brief Adapter to convert a GEA2 interface into a GEA2 packet endpoint.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Gea2PacketEndpoint_Gea2Interface.h"
#include "Gea2Constants.h"
#include "utils.h"
#include "uassert.h"

static bool IsBroadcast(uint8_t address)
{
   return ((address & GEA2_BCAST_MASK) == GEA2_BCAST_MASK);
}

static void PacketReceivedViaTheInterface(void *context, const void *_args)
{
   REINTERPRET(instance, context, Gea2PacketEndpoint_Gea2Interface_t *);
   REINTERPRET(args, _args, const Gea2InterfaceOnReceiveArgs_t *);

   if(IsBroadcast(args->packet->destination) || (args->packet->destination == Gea2Interface_Address(instance->_private.gea2Interface)))
   {
      Event_Synchronous_Publish(&instance->_private.onReceive, args);
   }
}

static uint8_t Address(I_Gea2PacketEndpoint_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2PacketEndpoint_Gea2Interface_t *);
   return Gea2Interface_Address(instance->_private.gea2Interface);
}

static void Send(I_Gea2PacketEndpoint_t *_instance, Gea2Packet_t *packet, const uint8_t retries)
{
   REINTERPRET(instance, _instance, Gea2PacketEndpoint_Gea2Interface_t *);
   packet->source = Gea2Interface_Address(instance->_private.gea2Interface);
   Gea2Interface_Send(instance->_private.gea2Interface, packet, retries);
}

static void Forward(I_Gea2PacketEndpoint_t *_instance, Gea2Packet_t *packet, const uint8_t retries)
{
   REINTERPRET(instance, _instance, Gea2PacketEndpoint_Gea2Interface_t *);
   Gea2Interface_Send(instance->_private.gea2Interface, packet, retries);
}

static I_Event_t * GetOnReceiveEvent(I_Gea2PacketEndpoint_t *_instance)
{
   REINTERPRET(instance, _instance, Gea2PacketEndpoint_Gea2Interface_t *);
   return &instance->_private.onReceive.interface;
}

static const I_Gea2PacketEndpoint_Api_t api =
   { Address, Send, Forward, GetOnReceiveEvent };

void Gea2PacketEndpoint_Gea2Interface_Init(
   Gea2PacketEndpoint_Gea2Interface_t *instance,
   I_Gea2Interface_t *gea2Interface)
{
   instance->interface.api = &api;
   instance->_private.gea2Interface = gea2Interface;

   Event_Synchronous_Init(&instance->_private.onReceive);

   EventSubscription_Init(&instance->_private.interfaceReceiveSubscription, instance, PacketReceivedViaTheInterface);
   Event_Subscribe(Gea2Interface_GetOnReceiveEvent(gea2Interface), &instance->_private.interfaceReceiveSubscription);
}
