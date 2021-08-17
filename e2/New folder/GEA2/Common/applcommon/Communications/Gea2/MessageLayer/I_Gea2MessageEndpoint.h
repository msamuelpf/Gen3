/*!
 * @file
 * @brief Object that allows GEA2 messages to be sent and received.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_GEA2MESSAGEENDPOINT_H
#define I_GEA2MESSAGEENDPOINT_H

#include "I_Event.h"
#include "Gea2Message.h"

struct I_Gea2MessageEndpoint_Api_t;

/*!
 * Message endpoint interface.  Includes methods (API) and events that can be used to interact
 * with an Message endpoint.
 */
typedef struct
{
   const struct I_Gea2MessageEndpoint_Api_t *api;
} I_Gea2MessageEndpoint_t;

/*!
 * Event args sent to subscribers when the OnReceive event is published.
 */
typedef struct
{
   const Gea2Message_t *message;
} Gea2MessageEndpointOnReceiveArgs_t;

/*!
 * Methods for interacting with a GEA2 Message endpoint.
 */
typedef struct I_Gea2MessageEndpoint_Api_t
{
   /*!
    * Send a message via the endpoint.  The message pointer is released when the call exits (it is okay
    * to allocate a message on the stack).  The source address is automatically set to the address of the
    * endpoint.
    * @pre instance != NULL
    * @pre message != NULL
    * @param instance The endpoint.
    * @param message The message to send.
    * @param retries Retries for the message.
    */
   void (*Send)(I_Gea2MessageEndpoint_t *instance, Gea2Message_t *message, const uint8_t retries);

   /*!
    * Get the event raised when a message is received
    * @note event args are of type Gea2MessageEndpointOnReceiveArgs_t
    * @param instance The instance
    * @return The event
    */
   I_Event_t * (*GetOnReceiveEvent)(I_Gea2MessageEndpoint_t *instance);
} I_Gea2MessageEndpoint_Api_t;

#define Gea2MessageEndpoint_Send(instance, message, retries) \
   (instance)->api->Send((instance), (message), (retries))

#define Gea2MessageEndpoint_GetOnReceiveEvent(instance) \
   (instance)->api->GetOnReceiveEvent((instance))

#endif
