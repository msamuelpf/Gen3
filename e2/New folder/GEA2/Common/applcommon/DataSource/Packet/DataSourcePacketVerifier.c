/*!
 * @file
 * @brief Implementation of data source packet verifier.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "DataSourcePacketVerifier.h"
#include "Erd.h"
#include "uassert.h"

static bool ValidErdList(const void *packet, const uint8_t packetSize)
{
   uint8_t erdCount;

   if(packetSize == 0)
   {
      return false;
   }

   erdCount = *(uint8_t *)packet;
   return (bool)(packetSize == sizeof(uint8_t) + erdCount * sizeof(Erd_t));
}

static bool ValidErdListWithData(const uint8_t *packet, const uint8_t packetSize)
{
   uint8_t erdCount;
   uint8_t erdIndex;
   uint8_t dataIndex = 0;

   if(packetSize == 0)
   {
      return false;
   }

   erdCount = packet[dataIndex++];

   for(erdIndex = 0; erdIndex < erdCount; erdIndex++)
   {
      uint8_t dataSize;

      // Need to be able to get ERD (2 bytes) and data length (1 byte)
      if(dataIndex + 3 > packetSize)
         return false;

      // Ignore ERD MSB/LSB
      dataIndex++;
      dataIndex++;

      dataSize = packet[dataIndex++];
      dataIndex += dataSize;
   }

   return (bool)(dataIndex == packetSize);
}

static bool ValidSubscriptionList(const uint8_t *packet, const uint8_t packetSize)
{
   uint8_t erdCount;

   if(packetSize == 0)
   {
      return false;
   }

   erdCount = *(uint8_t *)packet;
   return (bool)(packetSize == sizeof(uint8_t) + erdCount * (sizeof(Erd_t) + sizeof(uint8_t)));
}

static bool ValidEmptyList(const uint8_t packetSize)
{
   return (bool)(packetSize == 0);
}

bool DataSourcePacketVerifier_Verify(const void *packet, const uint8_t packetSize, const DataSourcePacketType_t packetType)
{
   switch(packetType)
   {
      case DataSourcePacketType_SubscribeRequest:
         return (packetSize > 1) && ValidSubscriptionList(packet, packetSize);

      case DataSourcePacketType_SubscriptionListResponse:
         return ValidSubscriptionList(packet, packetSize);

      case DataSourcePacketType_ReadRequest:
         case DataSourcePacketType_UnsubscribeRequest:
         return (packetSize > 1) && ValidErdList(packet, packetSize);

      case DataSourcePacketType_SubscribeResponse:
         case DataSourcePacketType_WriteResponse:
         return (packetSize == 1) || ValidErdList(packet, packetSize);

      case DataSourcePacketType_UnsubscribeResponse:
         case DataSourcePacketType_PublishAcknowledgement:
         case DataSourcePacketType_SubscriptionListRequest:
         return ValidEmptyList(packetSize);

      case DataSourcePacketType_Publish:
         case DataSourcePacketType_ReadResponse:
         return ValidErdListWithData(packet, packetSize);

      case DataSourcePacketType_WriteRequest:
         return (packetSize > 1) && ValidErdListWithData(packet, packetSize);

      default:
         return false;
   }
}
