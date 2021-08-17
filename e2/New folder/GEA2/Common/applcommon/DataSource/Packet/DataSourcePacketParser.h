/*!
 * @file
 * @brief An object that can parse data source packets.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef DATASOURCEPACKETPARSER_H
#define DATASOURCEPACKETPARSER_H

#include <stdint.h>
#include <stdbool.h>
#include "Erd.h"

/*!
 * Data source packet parser.  Struct members should be considered private.
 */
typedef struct
{
   struct
   {
      const uint8_t *dataPointer;
      uint8_t erdCount;
   } _private;
} DataSourcePacketParser_t;

/*!
 * Initialize a parser object.
 * @pre instance != NULL
 * @pre packet != NULL
 * @param instance The parser.
 * @param packet The packet to parse.
 */
void DataSourcePacketParser_Init(DataSourcePacketParser_t *instance, const uint8_t *packet);

/*!
 * Process a buffer with an ERD.
 * @pre instance != NULL
 * @pre erd != NULL
 * @param instance The parser.
 * @param erd Pointer to where the ERD will be copied.
 * @return True if ERD extracted, false otherwise.
 */
bool DataSourcePacketParser_ExtractErd(DataSourcePacketParser_t *instance, Erd_t *erd);

/*!
 * Process a buffer with an ERD.
 * @pre instance != NULL
 * @pre erd != NULL
 * @pre erdSize != NULL
 * @pre erdData != NULL
 * @param instance The parser.
 * @param erd Pointer to where the extracted ERD will be copied.
 * @param erdSize Pointer to where the size of the ERD will be copied.
 * @param erdData Pointer to where the ERD data will be copied.
 * @return True if ERD and data extracted, false otherwise.
 */
bool DataSourcePacketParser_ExtractErdWithData(DataSourcePacketParser_t *instance, Erd_t *erd, uint8_t *erdSize, const uint8_t **erdData);

/*!
 * Extract a subscription item (ERD and subscription time) from the packet.
 * @pre instance != NULL
 * @param instance The packet parser.
 * @param erd The ERD.
 * @param subscriptionTime The subscription time.
 * @return True if subscription item extracted, false otherwise.
 */
bool DataSourcePacketParser_ExtractSubscriptionItem(DataSourcePacketParser_t *instance, Erd_t *erd, uint8_t *subscriptionTime);

#endif
