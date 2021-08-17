/*!
 * @file
 * @brief Defines the structure of a GEA2 message layer message.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2MESSAGE_H
#define GEA2MESSAGE_H

#include <stdint.h>
#include "Gea2Packet.h"
#include "utils.h"

/*!
 * GEA2 bus message.  Struct members should be accessed only via functions defined below.
 */
typedef struct
{
   struct
   {
      Gea2Packet_t packet;
   } _private;
} Gea2Message_t;

// Command byte resides in the packet payload so the effective payload size is one smaller
#define GEA2MESSAGE_MAXPAYLOAD (GEA2PACKET_MAXPAYLOAD - 1)

// The message format has one more byte of overhead than a packet (the command)
#define GEA2MESSAGE_OVERHEAD (GEA2PACKET_OVERHEAD + 1)

/*!
 * Macro for allocating a GEA2 message with a given payload size on the stack.  Payload size is set
 * automatically.
 *
 * @note There are no issues with alignment since all members have single-byte alignment.
 */
#define STACK_ALLOC_GEA2MESSAGE(_name, _payloadLength) \
   uint8_t MACRO_SAFE_CONCATENATE(_name, Storage)[_payloadLength + GEA2MESSAGE_OVERHEAD] = {0, _payloadLength + 1}; \
   Gea2Message_t * const _name = (Gea2Message_t *)MACRO_SAFE_CONCATENATE(_name, Storage)

/*!
 * Macro for allocating a GEA2 message with with a provided payload type and setting the command.
 * This sets the payload length automatically, sets the command automatically, and overlays the payload
 * type on the message payload.
 *
 * @note The payload types should have no alignment requirements (all fields should have single-byte
 * alignment, ie: should be u8s).
 */
#define STACK_ALLOC_GEA2MESSAGE_TYPE(_messageName, _payloadName, _command, _payloadType) \
   STACK_ALLOC_GEA2MESSAGE(_messageName, sizeof(_payloadType)); \
   _payloadType *_payloadName; \
   Gea2Message_SetCommand(_messageName, _command); \
   _payloadName = (_payloadType *)Gea2Message_GetPayload(_messageName)

/*!
 * Macro for statically allocating a GEA2 message with a given payload size.  Payload size is set
 * automatically.
 *
 * @note There are no issues with alignment since all members have single-byte alignment.
 */
#define STATIC_ALLOC_GEA2MESSAGE(_name, _payloadLength) \
   static uint8_t _name##Storage[_payloadLength + GEA2MESSAGE_OVERHEAD] = {0, _payloadLength + 1}; \
   static Gea2Message_t * const _name = (Gea2Message_t *)_name##Storage

/*!
 * Get the source address of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return The source address.
 */
uint8_t Gea2Message_GetSource(const Gea2Message_t *instance);

/*!
 * Get the destination address of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return The destination address.
 */
uint8_t Gea2Message_GetDestination(const Gea2Message_t *instance);

/*!
 * Get the command of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return The command.
 */
uint8_t Gea2Message_GetCommand(const Gea2Message_t *instance);

/*!
 * Get the payload length of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return The payload length.
 */
uint8_t Gea2Message_GetPayloadLength(const Gea2Message_t *instance);

/*!
 * Get a pointer to the payload of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return A pointer to the payload.
 */
uint8_t * Gea2Message_GetPayload(Gea2Message_t *instance);

/*!
 * Get a pointer to the payload of a const GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @return A pointer to the payload.
 */
const uint8_t * Gea2Message_GetConstPayload(const Gea2Message_t *instance);

/*!
 * Set the destination address of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @param destination The new destination address.
 */
void Gea2Message_SetDestination(Gea2Message_t *instance, uint8_t destination);

/*!
 * Set the source address of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @param destination The new source address.
 */
void Gea2Message_SetSource(Gea2Message_t *instance, uint8_t source);

/*!
 * Set the command of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @param command The new command.
 */
void Gea2Message_SetCommand(Gea2Message_t *instance, uint8_t command);

/*!
 * Set the payload length of a GEA2 message.
 * @pre instance != NULL
 * @param instance The GEA2 message.
 * @param payloadLength The new payload length.
 */
void Gea2Message_SetPayloadLength(Gea2Message_t *instance, uint8_t payloadLength);

#endif
