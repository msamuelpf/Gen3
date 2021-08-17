/*!
 * @file
 * @brief Source file to the GEA DataSource interface
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "DataSourcePacketReadWriteManager_Simple.h"
#include "DataSourcePacketParser.h"
#include "DataSourcePacketBuilder.h"
#include "uassert.h"
#include "utils.h"

static void Read(I_DataSourcePacketReadWriteManager_t *_instance, const void *requestBuffer, void *responseBuffer,
   const uint8_t responseBufferSize, uint8_t *responseSize)
{
   REINTERPRET(instance, _instance, DataSourcePacketReadWriteManager_Simple_t *);

   Erd_t erd;
   void *dataToFill;
   DataSourcePacketParser_t parser;
   DataSourcePacketBuilder_t builder;

   DataSourcePacketParser_Init(&parser, requestBuffer);
   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);

   while(DataSourcePacketParser_ExtractErd(&parser, &erd))
   {
      if(DataSource_Has(instance->_private.dataSource, erd))
      {
         uint8_t erdSize = DataSource_SizeOf(instance->_private.dataSource, erd);

         if(DataSourcePacketBuilder_AddErdAndReserveStorageForData(&builder, erd, erdSize, &dataToFill))
         {
            DataSource_Read(instance->_private.dataSource, erd, dataToFill);
         }
      }
   }

   *responseSize = DataSourcePacketBuilder_GetSize(&builder);
}

static void Write(I_DataSourcePacketReadWriteManager_t *_instance, const void *requestBuffer, void *responseBuffer,
   const uint8_t responseBufferSize, uint8_t *responseSize)
{
   REINTERPRET(instance, _instance, DataSourcePacketReadWriteManager_Simple_t *);

   Erd_t erd;
   const uint8_t *dataToProcess;
   uint8_t erdSize;
   DataSourcePacketParser_t parser;
   DataSourcePacketBuilder_t builder;

   DataSourcePacketParser_Init(&parser, requestBuffer);
   DataSourcePacketBuilder_Init(&builder, responseBuffer, responseBufferSize);

   while(DataSourcePacketParser_ExtractErdWithData(&parser, &erd, &erdSize, &dataToProcess))
   {
      if(DataSource_Has(instance->_private.dataSource, erd)
         && (erdSize == DataSource_SizeOf(instance->_private.dataSource, erd)))
      {
         DataSource_Write(instance->_private.dataSource, erd, dataToProcess);
         (void)DataSourcePacketBuilder_AddErd(&builder, erd);
      }
   }

   *responseSize = DataSourcePacketBuilder_GetSize(&builder);
}

static const I_DataSourcePacketReadWriteManager_Api_t api =
   { Read, Write };

void DataSourcePacketReadWriteManager_Init(DataSourcePacketReadWriteManager_Simple_t *instance, I_DataSource_t *dataSource)
{
   instance->interface.api = &api;
   instance->_private.dataSource = dataSource;
}
