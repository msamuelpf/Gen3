/*!
 * @file
 * @brief Object that provides the ability to construct a data source packet.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETBUILDER_H
#define DATASOURCEPACKETBUILDER_H

#include <stdbool.h>
#include "Erd.h"

/*!
 * Used internally to keep track of data being written into the buffer.
 */
typedef struct
{
   uint8_t erdCount;
   uint8_t data[1];
} DataSourcePacketBuilderPacketRepresentation_t;

/*!
 * Data source packet builder.  Struct members should be considered private.
 */
typedef struct
{
   struct
   {
      uint8_t *current;
      DataSourcePacketBuilderPacketRepresentation_t *packet;
      uint8_t bytesRemaining;
   } _private;
} DataSourcePacketBuilder_t;

/*!
 * Initializer for an instance of the builder object.
 * @pre instance != NULL
 * @param instance The packet builder.
 * @param packetOutput Pointer to where the packet should be built.
 * @param maxBytes The max space allowed at the pointer
 */
void DataSourcePacketBuilder_Init(DataSourcePacketBuilder_t *instance, void *packetOutput, const uint8_t maxBytes);

/*!
 * Fill a buffer with an ERD if there is room.
 * @pre instance != NULL
 * @param instance The packet builder.
 * @param erd The ERD to add
 * @return True if something added to buffer, false otherwise.
 */
bool DataSourcePacketBuilder_AddErd(DataSourcePacketBuilder_t *instance, const Erd_t erd);

/*!
 * Fill a buffer with an ERD and its data if there is room.
 * @pre instance != NULL
 * @param instance The packet builder.
 * @param erd The ERD to add.
 * @param erdSize ERD data size.
 * @param erdData Pointer to ERD data that will be copied into the buffer.
 * @return True if something added to buffer, false otherwise.
 */
bool DataSourcePacketBuilder_AddErdWithData(DataSourcePacketBuilder_t *instance, const Erd_t erd,
   const uint8_t erdSize, const void *erdData);

/*!
 * Fill a buffer with an ERD and its data if there is room.
 * @pre instance != NULL
 * @param instance The packet builder.
 * @param erd The ERD to add.
 * @param erdSize ERD data size.
 * @param reservedStorage Output parameter that will hold the location of the reserved storage.  ERD data can be written here on success.
 * @return True if something added to buffer, false otherwise.
 */
bool DataSourcePacketBuilder_AddErdAndReserveStorageForData(DataSourcePacketBuilder_t *instance,
   const Erd_t erd, const uint8_t erdSize, void **reservedStorage);

/*!
 * Fill a buffer with a subscription (an ERD and the associated subscription time).
 * @pre instance != NULL
 * @param instance The packet builder.
 * @param erd The ERD.
 * @param subscriptionTime The subscription time (minutes).
 * @return True if subscription added to the buffer, false otherwise.
 */
bool DataSourcePacketBuilder_AddSubscriptionItem(DataSourcePacketBuilder_t *instance, const Erd_t erd,
   const uint8_t subscriptionTime);

/*!
 * Gets the size of the built packet (from last call of Add).
 * @pre instance != NULL
 * @param instance The packet builder.
 * @return The size.
 */
uint8_t DataSourcePacketBuilder_GetSize(DataSourcePacketBuilder_t *instance);

#endif
