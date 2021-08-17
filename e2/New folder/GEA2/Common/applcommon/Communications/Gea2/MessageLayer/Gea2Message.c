/*!
 * @file
 * @brief Implementation of GEA2 message getters and setters.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Gea2Message.h"
#include "uassert.h"

uint8_t Gea2Message_GetSource(const Gea2Message_t *instance)
{
   return instance->_private.packet.source;
}

uint8_t Gea2Message_GetDestination(const Gea2Message_t *instance)
{
   return instance->_private.packet.destination;
}

uint8_t Gea2Message_GetCommand(const Gea2Message_t *instance)
{
   return instance->_private.packet.payload[0];
}

uint8_t Gea2Message_GetPayloadLength(const Gea2Message_t *instance)
{
   return instance->_private.packet.payloadLength - 1;
}

uint8_t * Gea2Message_GetPayload(Gea2Message_t *instance)
{
   return instance->_private.packet.payload + 1;
}

const uint8_t * Gea2Message_GetConstPayload(const Gea2Message_t *instance)
{
   return instance->_private.packet.payload + 1;
}

void Gea2Message_SetDestination(Gea2Message_t *instance, uint8_t destination)
{
   instance->_private.packet.destination = destination;
}

void Gea2Message_SetSource(Gea2Message_t *instance, uint8_t source)
{
   instance->_private.packet.source = source;
}

void Gea2Message_SetCommand(Gea2Message_t *instance, uint8_t command)
{
   instance->_private.packet.payload[0] = command;
}

void Gea2Message_SetPayloadLength(Gea2Message_t *instance, uint8_t payloadLength)
{
   instance->_private.packet.payloadLength = payloadLength + 1;
}
