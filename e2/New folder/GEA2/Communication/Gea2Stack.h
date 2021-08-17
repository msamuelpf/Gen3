/*!
 * @file
 * @brief Initializes GEA2 support system and connects the data source to the GEA2 bus
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef GEA2STACK_H
#define GEA2STACK_H

#include "Gea2PacketEndpoint_BackgroundSingleWireUartInterface.h"
#include "Gea2MessageEndpoint_Gea2PacketEndpointAdapter.h"
#include "SimpleDataSourceMessageEndpointConnector.h"
#include "DataSourcePacketSubscriptionManager_Simple.h"
#include "I_Uart.h"
#include "I_DataSource.h"

enum
{
   Gea2Address = 0x23,
   Gea2CrcSeed = 0x1021,
};

typedef struct
{
   struct
   {
      Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t gea2PacketEndpoint;
      Gea2PacketEndpoint_BackgroundSingleWireUartInterfaceDefaultConfigurationResources_t gea2PacketEndpointResources;
      Gea2MessageEndpoint_Gea2PacketEndpointAdapter_t messageEndpointAdapter;
      SimpleDataSourceMessageEndpointConnector_t dataSourceMessageEndpointConnector;
      DataSourcePacketSubscriptionManager_Simple_SubscriptionListItem_t storage[SIMPLEDATASOURCEMESSAGEENDPOINTCONNECTOR_SUBSCRIPTIONLISTLENGTH];
   } _private;
} Gea2Stack_t;


/*!
 * Get handle to the packet end point interface.
 * @param instance ptr of type Gea2Stack_t
 * @return packetEndpointAdapter interface.
 */
I_Gea2PacketEndpoint_t *Gea2Stack_GetGea2PacketEndpoint(Gea2Stack_t *instance);


/*!
 * Get a handle to transmit/Receive GEA messages.
 * @param instance ptr of type Gea2Stack_t
 * @return messageEndpointAdapter interface - so you can send and pay attention to received a GEA messages
 */
I_Gea2MessageEndpoint_t *Gea2Stack_GetGea2MessageEndpoint(Gea2Stack_t *instance);


/*!
 * Initialize the Gea2 stack
 * @param instance ptr of type Gea2Stack_t
 * @param internalDataSource
 * @param externalDataSource
 * @param timerModule
 * @param uart
 */
void Gea2Stack_Init(
   Gea2Stack_t *instance,
   I_DataSource_t *internalDataSource,
   I_DataSource_t *externalDataSource,
   TimerModule_t *timerModule,
   I_Uart_t *uart);

/*!
 * Run Gea2
 * @param instance ptr of type Gea2Stack_t
 */
void Gea2Stack_RunGea(Gea2Stack_t *instance);

#endif
