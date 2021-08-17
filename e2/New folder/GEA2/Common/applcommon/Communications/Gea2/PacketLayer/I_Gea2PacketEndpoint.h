/*!
 * @file
 * @brief Interface that an application will use to send/receive GEA2 messages.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_GEA2PACKETENDPOINT_H
#define I_GEA2PACKETENDPOINT_H

#include "I_Event.h"
#include "Gea2Packet.h"

struct I_Gea2PacketEndpoint_Api_t;

typedef struct
{
   const struct I_Gea2PacketEndpoint_Api_t *api;
} I_Gea2PacketEndpoint_t;

typedef struct
{
   const Gea2Packet_t *packet;
} Gea2PacketEndpointOnReceiveArgs_t;

typedef struct I_Gea2PacketEndpoint_Api_t
{
   /*!
    * Get the address associated with the endpoint.
    * @param instance The endpoint.
    * @return The endpoint address.
    */
   uint8_t (*Address)(I_Gea2PacketEndpoint_t *instance);

   /*!
    * Send a packet via the endpoint. The packet pointer is released when the call exits (it is okay
    * to allocate a packet on the stack). The source address is automatically set to the address of the
    * endpoint.
    * @param instance The endpoint.
    * @param packet The packet to send.
    * @param retries Retries for the packet.
    */
   void (*Send)(I_Gea2PacketEndpoint_t *instance, Gea2Packet_t *packet, const uint8_t retries);

   /*!
    * Forwards a packet via the endpoint. The packet pointer is released when the call exits (it is okay
    * to allocate a packet on the stack). The source address is _not_ automatically set to the address of
    * the endpoint and can be set by the caller.
    * @param instance The endpoint.
    * @param packet The packet to send.
    * @param retries Retries for the packet.
    */
   void (*Forward)(I_Gea2PacketEndpoint_t *instance, Gea2Packet_t *packet, const uint8_t retries);

   /*!
    * Get event raised when a packet is received.
    * @param instance The instance
    * @note Event args are of type Gea2PacketEndpointOnReceiveArgs_t
    * @return The event
    */
   I_Event_t * (*GetOnReceiveEvent)(I_Gea2PacketEndpoint_t *instance);
} I_Gea2PacketEndpoint_Api_t;

#define Gea2PacketEndpoint_Address(instance) \
   (instance)->api->Address((instance))

#define Gea2PacketEndpoint_Send(instance, packet, retries) \
   (instance)->api->Send((instance), (packet), (retries))

#define Gea2PacketEndpoint_Forward(instance, packet, retries) \
   (instance)->api->Forward((instance), (packet), (retries))

#define Gea2PacketEndpoint_GetOnReceiveEvent(instance) \
   (instance)->api->GetOnReceiveEvent((instance))

#endif
