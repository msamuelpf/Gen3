/*!
 * @file
 * @brief GEA2 interface controller.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_GEA2INTERFACE_H
#define I_GEA2INTERFACE_H

#include <stdbool.h>
#include <stddef.h>
#include "Gea2InterfaceAcceptDelegate.h"
#include "Gea2Packet.h"
#include "I_Event.h"

typedef struct
{
   const Gea2Packet_t *packet;
} Gea2InterfaceOnReceiveArgs_t;

struct I_Gea2Interface_Api_t;

/*!
 * Generic GEA2 interface.
 */
typedef struct
{
   /*!
    * API for interacting with the GEA2 interface.
    */
   const struct I_Gea2Interface_Api_t *api;
} I_Gea2Interface_t;

/*!
 * Interface for interacting with a GEA2 interface.  API should be accessed using wrapper calls below.
 */
typedef struct I_Gea2Interface_Api_t
{
   /*!
    * Queue a packet to be sent. The packet pointer is released when the call exits (it is safe to
    * allocate the packet on the stack).
    * @pre PayloadLength(packet) < MaxPayloadLength(interface)
    * @param instance The GEA2 interface.
    * @param packet The packet to send.
    * @param retries The maximum number of retries to be made when sending.
    */
   void (*Send)(I_Gea2Interface_t *instance, const Gea2Packet_t *packet, const uint8_t retries);

   /*!
    * Set the accept delegate to be used when the interface is determining whether to ACK an incoming packet.
    * @param instance The GEA2 interface.
    * @param delegate The accept delegate.
    */
   void (*SetAcceptDelegate)(I_Gea2Interface_t *instance, const Gea2InterfaceAcceptDelegate_t *delegate);

   /*!
    * Get the primary address associated with a GEA2 interface.
    * @param instance The GEA2 interface.
    * @return The primary bus address of the GEA2 interface.
    */
   uint8_t (*Address)(I_Gea2Interface_t *instance);

   /*!
    * Get the max payload length for a sent message.
    * @param instance The GEA2 interface.
    * @return The max payload length of a message sent using the GEA2 interface.
    */
   uint8_t (*MaxPayloadLength)(I_Gea2Interface_t *instance);

   /*!
    * Get the number of packets queued for send.
    * @param instance The interface.
    * @return The number of pending packets to be sent.
    */
   size_t (*SendQueueCount)(I_Gea2Interface_t *instance);

   /*!
    * Get the event raised when a packet is received from the interface.
    * @param instance The instance
    * @note Event args are of type Gea2InterfaceOnReceiveArgs_t
    * @return The event
    */
   I_Event_t * (*GetOnReceiveEvent)(I_Gea2Interface_t *instance);
} I_Gea2Interface_Api_t;

#define Gea2Interface_Send(instance, packet, retries) \
   (instance)->api->Send((instance), (packet), (retries))

#define Gea2Interface_SetAcceptDelegate(instance, delegate) \
   (instance)->api->SetAcceptDelegate((instance), (delegate))

#define Gea2Interface_Address(instance) \
   (instance)->api->Address((instance))

#define Gea2Interface_MaxPayloadLength(instance) \
   (instance)->api->MaxPayloadLength((instance))

#define Gea2Interface_SendQueueCount(instance) \
   (instance)->api->SendQueueCount((instance))

#define Gea2Interface_GetOnReceiveEvent(instance) \
   (instance)->api->GetOnReceiveEvent((instance))

#endif
