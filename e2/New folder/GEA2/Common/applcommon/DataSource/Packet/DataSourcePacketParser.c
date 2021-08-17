/*!
 * @file
 * @brief The API that processes a DataSource Packet
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "DataSourcePacketParser.h"
#include "uassert.h"

void DataSourcePacketParser_Init(DataSourcePacketParser_t *instance, const uint8_t *packet)
{
   instance->_private.erdCount = packet[0];
   instance->_private.dataPointer = packet + 1;
}

bool DataSourcePacketParser_ExtractErd(DataSourcePacketParser_t *instance, Erd_t *erd)
{
   if(instance->_private.erdCount)
   {
      *erd = *(uint8_t *)instance->_private.dataPointer++;
      *erd = (uint16_t)(0xff00 & (*erd << 8)) + *instance->_private.dataPointer++;
      instance->_private.erdCount -= 1;

      return true;
   }

   return false;
}

bool DataSourcePacketParser_ExtractErdWithData(DataSourcePacketParser_t *instance, Erd_t *erd, uint8_t *erdSize, const uint8_t **erdData)
{
   if(DataSourcePacketParser_ExtractErd(instance, erd))
   {
      *erdSize = *instance->_private.dataPointer++;
      *erdData = instance->_private.dataPointer;
      instance->_private.dataPointer += *erdSize;
      return true;
   }

   return false;
}

bool DataSourcePacketParser_ExtractSubscriptionItem(DataSourcePacketParser_t *instance, Erd_t *erd, uint8_t *subscriptionTime)
{
   if(instance->_private.erdCount)
   {
      *erd = *instance->_private.dataPointer++;
      *erd = (uint16_t)(0xff00 & (*erd << 8)) + *instance->_private.dataPointer++;
      *subscriptionTime = *instance->_private.dataPointer++;

      instance->_private.erdCount -= 1;

      return true;
   }

   return false;
}
