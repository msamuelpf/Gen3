/*!
 * @file
 * @brief Verifies correctness of data source packets.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETVERIFIER_H
#define DATASOURCEPACKETVERIFIER_H

#include <stdint.h>
#include <stdbool.h>

enum
{
   DataSourcePacketType_ReadRequest,
   DataSourcePacketType_ReadResponse,
   DataSourcePacketType_WriteRequest,
   DataSourcePacketType_WriteResponse,
   DataSourcePacketType_SubscribeRequest,
   DataSourcePacketType_SubscribeResponse,
   DataSourcePacketType_Publish,
   DataSourcePacketType_PublishAcknowledgement,
   DataSourcePacketType_UnsubscribeRequest,
   DataSourcePacketType_UnsubscribeResponse,
   DataSourcePacketType_SubscriptionListRequest,
   DataSourcePacketType_SubscriptionListResponse,
   DataSourcePacketType_Max
};
typedef uint8_t DataSourcePacketType_t;

/*!
 * Verifies that a packet is a valid instance of the specified packet type.
 * @pre packet != NULL
 * @param packet The packet.
 * @param packetSize The size of the packet.
 * @param packetType The expected packet type.
 * @return True if the packet is valid, false otherwise.
 * @note If packetType is greater than or equal to PacketType_Max this will always return false.
 */
bool DataSourcePacketVerifier_Verify(const void *packet, const uint8_t packetSize, const DataSourcePacketType_t packetType);

#endif
