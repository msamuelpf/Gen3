/*!
 * @file
 * @brief GEA2 packet endpoint that directly uses a single-wire UART interface that is run in the background.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Gea2PacketEndpoint_BackgroundSingleWireUartInterface.h"
#include "utils.h"
#include "uassert.h"

void Gea2PacketEndpoint_BackgroundSingleWireUartInterface_InitWithCustomConfiguration(
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t *instance,
   I_Uart_t *uart,
   I_TimeSource_t *timeSource,
   I_Crc16Calculator_t *crc16Calculator,
   uint8_t address,
   uint8_t *interfaceSendReceiveBuffer,
   size_t interfaceSendReceiveBufferSize,
   uint8_t *isrSafeUartBuffer,
   size_t isrSafeUartBufferSize,
   uint8_t *packetQueueStorage,
   size_t packetQueueStorageSize)
{
   Uart_IsrSafe_Init(
      &instance->_private.isrSafeUart,
      uart,
      isrSafeUartBuffer,
      isrSafeUartBufferSize);

   Gea2PacketQueue_EfficientStorage_Init(
      &instance->_private.packetQueue,
      packetQueueStorage,
      packetQueueStorageSize,
      interfaceSendReceiveBufferSize + Gea2Interface_SingleWireUnbufferedBytes - GEA2PACKET_TRANSMISSION_OVERHEAD);

   Gea2Interface_SingleWire_Init(
      &instance->_private.gea2Interface,
      &instance->_private.isrSafeUart.interface,
      address,
      interfaceSendReceiveBuffer,
      interfaceSendReceiveBufferSize,
      timeSource,
      &instance->_private.packetQueue.interface,
      crc16Calculator);

   Gea2PacketEndpoint_Gea2Interface_Init(
      &instance->_private.gea2PacketEndpoint,
      &instance->_private.gea2Interface.interface);
}

void Gea2PacketEndpoint_BackgroundSingleWireUartInterface_InitWithDefaultConfiguration(
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t *instance,
   Gea2PacketEndpoint_BackgroundSingleWireUartInterfaceDefaultConfigurationResources_t *resources,
   I_Uart_t *uart,
   I_TimeSource_t *timeSource,
   I_Crc16Calculator_t *crc16Calculator,
   uint8_t address)
{
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_InitWithCustomConfiguration(
      instance,
      uart,
      timeSource,
      crc16Calculator,
      address,
      resources->interfaceSendReceiveBuffer,
      sizeof(resources->interfaceSendReceiveBuffer),
      resources->isrSafeUartBuffer,
      sizeof(resources->isrSafeUartBuffer),
      resources->packetQueueStorage,
      sizeof(resources->packetQueueStorage));
}

void Gea2PacketEndpoint_BackgroundSingleWireUartInterface_Run(
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t *instance)
{
   Uart_IsrSafe_Run(&instance->_private.isrSafeUart);
   Gea2Interface_SingleWire_Run(&instance->_private.gea2Interface);
}
