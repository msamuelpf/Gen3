/*!
 * @file
 * @brief Initializes GEA2 support system and connects the data source to the GEA2 bus
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "Gea2Stack.h"
#include "Crc16Calculator_Formula.h"

I_Gea2PacketEndpoint_t *Gea2Stack_GetGea2PacketEndpoint(Gea2Stack_t *instance)
{
   return &instance->_private.gea2PacketEndpoint.interface;
}

I_Gea2MessageEndpoint_t *Gea2Stack_GetGea2MessageEndpoint(Gea2Stack_t *instance)
{
   return &instance->_private.messageEndpointAdapter.interface;
}

void Gea2Stack_Init(
   Gea2Stack_t *instance,
   I_DataSource_t *internalDataSource,
   I_DataSource_t *externalDataSource,
   TimerModule_t *timerModule,
   I_Uart_t *uart)
{
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_InitWithDefaultConfiguration(
      &instance->_private.gea2PacketEndpoint,
      &instance->_private.gea2PacketEndpointResources,
      uart,
      timerModule->timeSource,
      Crc16Calculator_Formula,
      Gea2Address);

   Gea2MessageEndpoint_Gea2PacketEndpointAdapter_Init(
      &instance->_private.messageEndpointAdapter,
      &instance->_private.gea2PacketEndpoint.interface);

   SimpleDataSourceMessageEndpointConnector_Init(
      &instance->_private.dataSourceMessageEndpointConnector,
      externalDataSource,
      &instance->_private.messageEndpointAdapter.interface,
      timerModule,
      instance->_private.storage,
      NUM_ELEMENTS(instance->_private.storage),
      GEA2MESSAGE_MAXPAYLOAD);
}

void Gea2Stack_RunGea(Gea2Stack_t *instance)
{
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_Run(&instance->_private.gea2PacketEndpoint);
}
