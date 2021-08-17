/*!
 * @file
 * @brief The API to build a response to a DataSourceMessage
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <string.h>
#include "DataSourcePacketBuilder.h"
#include "uassert.h"

#define U16_LSB_MASK (0x00FF)
#define SUBSCRIPTION_TIME_SIZE (sizeof(uint8_t))

uint8_t DataSourcePacketBuilder_GetSize(DataSourcePacketBuilder_t *instance)
{
   return (uint8_t)((uint8_t *)instance->_private.current - (uint8_t *)instance->_private.packet);
}

bool DataSourcePacketBuilder_AddErd(DataSourcePacketBuilder_t *instance, const Erd_t erd)
{
   if(instance->_private.bytesRemaining >= sizeof(Erd_t))
   {
      *instance->_private.current++ = (uint8_t)((erd >> 8) & U16_LSB_MASK);
      *instance->_private.current++ = (uint8_t)(erd & U16_LSB_MASK);

      instance->_private.bytesRemaining -= sizeof(Erd_t);

      instance->_private.packet->erdCount += 1;

      return true;
   }

   return false;
}

bool DataSourcePacketBuilder_AddErdWithData(
   DataSourcePacketBuilder_t *instance,
   const Erd_t erd,
   const uint8_t erdSize,
   const void *erdData)
{
   void *reservedStorage;

   if(DataSourcePacketBuilder_AddErdAndReserveStorageForData(instance, erd, erdSize, &reservedStorage))
   {
      memcpy(reservedStorage, erdData, (size_t)erdSize);
      return true;
   }

   return false;
}

bool DataSourcePacketBuilder_AddErdAndReserveStorageForData(
   DataSourcePacketBuilder_t *instance,
   const Erd_t erd,
   const uint8_t erdSize,
   void **reservedStorage)
{
   uint16_t bytesToAdd = sizeof(erd) + sizeof(erdSize) + erdSize;
   if(instance->_private.bytesRemaining >= bytesToAdd)
   {
      *instance->_private.current++ = (uint8_t)((erd >> 8) & U16_LSB_MASK);
      *instance->_private.current++ = (uint8_t)(erd & U16_LSB_MASK);

      *(uint8_t *)instance->_private.current++ = erdSize;

      *reservedStorage = instance->_private.current;

      instance->_private.current += erdSize;

      instance->_private.bytesRemaining -= (uint8_t)bytesToAdd;

      instance->_private.packet->erdCount += 1;

      return true;
   }

   return false;
}

bool DataSourcePacketBuilder_AddSubscriptionItem(
   DataSourcePacketBuilder_t *instance,
   const Erd_t erd,
   const uint8_t subscriptionTime)
{
   if(instance->_private.bytesRemaining >= sizeof(Erd_t) + SUBSCRIPTION_TIME_SIZE)
   {
      *instance->_private.current++ = (uint8_t)((erd >> 8) & U16_LSB_MASK);
      *instance->_private.current++ = (uint8_t)(erd & U16_LSB_MASK);

      *instance->_private.current++ = subscriptionTime;

      instance->_private.bytesRemaining -= sizeof(Erd_t) + SUBSCRIPTION_TIME_SIZE;

      instance->_private.packet->erdCount += 1;

      return true;
   }

   return false;
}

void DataSourcePacketBuilder_Init(DataSourcePacketBuilder_t *instance, void *packet, const uint8_t maxBytes)
{
   instance->_private.packet = (DataSourcePacketBuilderPacketRepresentation_t *)packet;
   instance->_private.packet->erdCount = 0;
   instance->_private.current = instance->_private.packet->data;

   instance->_private.bytesRemaining = (uint8_t)(maxBytes - sizeof(instance->_private.packet->erdCount));
}
