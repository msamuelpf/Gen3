/*!
 * @file
 * @brief Interface for a packet-based read write manager for a data source.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_DATASOURCEPACKETREADWRITEMANAGER_H
#define I_DATASOURCEPACKETREADWRITEMANAGER_H

#include <stdint.h>

struct I_DataSourcePacketReadWriteManager_Api_t;

/*!
 * Interface for a packet-based read write manager.
 */
typedef struct
{
   const struct I_DataSourcePacketReadWriteManager_Api_t *api;
} I_DataSourcePacketReadWriteManager_t;

/*!
 * Methods for interacting with a packet-based read write manager.  Methods should be invoked with
 * convenience functions declared below.
 */
typedef struct I_DataSourcePacketReadWriteManager_Api_t
{
   /*!
    * Process a read message.  This will parse a read request, execute the read, and then populate
    * the read response that should be sent to the requester.
    * @pre instance != NULL
    * @pre request != NULL
    * @pre responseBuffer != NULL
    * @pre responseSize != NULL
    * @param instance The read write manager.
    * @param request The read request buffer.
    * @param responseBuffer The buffer that will be filled with the response.
    * @param responseBufferSize The maximum size of the response.
    * @param responseSize The actual size of the response.  This is an output parameter.
    * @note requestBuffer is assumed to be a valid Read packet.
    */
   void (*Read)(I_DataSourcePacketReadWriteManager_t *instance, const void *requestBuffer,
      void *responseBuffer, const uint8_t responseBufferSize, uint8_t *responseSize);

   /*!
    * Process a write message.  This will parse a write request, execute the write, and then populate
    * the write response that should be sent to the requester.
    * @pre instance != NULL
    * @pre request != NULL
    * @pre responseBuffer != NULL
    * @pre responseSize != NULL
    * @param instance The read write manager.
    * @param request The write request buffer.
    * @param responseBuffer The buffer that will be filled with the response.
    * @param responseBufferSize The maximum size of the response.
    * @param responseSize The actual size of the response.  This is an output parameter.
    * @note payloadToProcess is assumed to be a valid Write packet.
    */
   void (*Write)(I_DataSourcePacketReadWriteManager_t *instance, const void *requestBuffer,
      void *responseBuffer, const uint8_t responseBufferSize, uint8_t *responseSize);
} I_DataSourcePacketReadWriteManager_Api_t;

#define DataSourcePacketReadWriteManager_Read(instance, requestBuffer, responseBuffer, responseBufferSize, responseSize) \
   (instance)->api->Read((instance), (requestBuffer), (responseBuffer), (responseBufferSize), (responseSize))

#define DataSourcePacketReadWriteManager_Write(instance, requestBuffer, responseBuffer, responseBufferSize, responseSize) \
   (instance)->api->Write((instance), (requestBuffer), (responseBuffer), (responseBufferSize), (responseSize))

#endif
