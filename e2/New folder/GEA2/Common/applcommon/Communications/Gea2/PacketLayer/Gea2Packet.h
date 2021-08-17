/*!
 * @file
 * @brief GEA2 packet definition.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2PACKET_H
#define GEA2PACKET_H

#include <stdint.h>

/*!
 * GEA2 bus packet.
 */
typedef struct
{
   /*!
    * Destination address.
    */
   uint8_t destination;

   /*!
    * Payload length.
    */
   uint8_t payloadLength;

   /*!
    * Source address.
    */
   uint8_t source;

   /*!
    * Packet payload.
    */
   uint8_t payload[1];
} Gea2Packet_t;

// I would love to use offsetof here, but the R8c compiler is shite so I have to use a magic number
// Payload begins after (1) destination, (2) payload length, (3) source
#define GEA2PACKET_OVERHEAD (3)

// STX, ETX, CRC_MSB, CRC_LSB, SOURCE, DESTINATION, DATA_LENGTH => 7
#define GEA2PACKET_TRANSMISSION_OVERHEAD (7)
#define GEA2PACKET_MAXPAYLOAD (UINT8_MAX - GEA2PACKET_TRANSMISSION_OVERHEAD)

/*!
 * Macro for allocating a GEA2 packet with a given payload size on the stack.  Payload size is set automatically.
 *
 * @note There are no issues with alignment since all members have single-byte alignment.
 */
#define STACK_ALLOC_GEA2PACKET(_name, _payloadLength) \
   uint8_t _name##Storage[_payloadLength + GEA2PACKET_OVERHEAD] = {0, _payloadLength}; \
   Gea2Packet_t * const _name = (Gea2Packet_t *)_name##Storage

/*!
 * Macro for allocating a GEA2 packet with with a provided payload type.  This sets the payload length
 * automatically and overlays the payload type on the packet payload.
 *
 * @note The payload types should have no alignment requirements (all fields should have single-byte
 * alignment, ie: should be u8s).
 */
#define STACK_ALLOC_GEA2PACKET_TYPE(_packetName, _payloadName, _payloadType) \
   STACK_ALLOC_GEA2PACKET(_packetName, sizeof(_payloadType)); \
   _payloadType *_payloadName; \
   _payloadName = (_payloadType *)_packetName->payload;

/*!
 * Macro for statically allocating a GEA2 packet with a given payload size.  Payload size is set automatically.
 *
 * @note There are no issues with alignment since all members have single-byte alignment.
 */
#define STATIC_ALLOC_GEA2PACKET(_name, _payloadLength) \
   static uint8_t _name##Storage[_payloadLength + GEA2PACKET_OVERHEAD] = {0, _payloadLength}; \
   static Gea2Packet_t * const _name = (Gea2Packet_t *)_name##Storage

#endif
