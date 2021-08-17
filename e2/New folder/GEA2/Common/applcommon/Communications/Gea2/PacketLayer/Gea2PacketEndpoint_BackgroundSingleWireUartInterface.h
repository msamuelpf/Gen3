/*!
 * @file
 * @brief GEA2 packet endpoint that directly uses a single-wire UART interface that is run in the background.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2PACKETENDPOINT_BACKGROUNDSINGLEWIREUARTINTERFACE_H
#define GEA2PACKETENDPOINT_BACKGROUNDSINGLEWIREUARTINTERFACE_H

#include "I_Gea2PacketEndpoint.h"
#include "Gea2PacketQueue_EfficientStorage.h"
#include "Gea2Interface_SingleWire.h"
#include "Gea2PacketEndpoint_Gea2Interface.h"
#include "Uart_IsrSafe.h"
#include "I_Crc16Calculator.h"
#include "I_TimeSource.h"

typedef struct
{
   union
   {
      I_Gea2PacketEndpoint_t interface;

      struct
      {
         Gea2PacketEndpoint_Gea2Interface_t gea2PacketEndpoint;
         Uart_IsrSafe_t isrSafeUart;
         Gea2PacketQueue_EfficientStorage_t packetQueue;
         Gea2Interface_SingleWire_t gea2Interface;
      } _private;
   };
} Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t;

typedef struct
{
   uint8_t interfaceSendReceiveBuffer[Gea2Interface_SingleWireMaxSendReceiveBufferSize];
   uint8_t isrSafeUartBuffer[20];
   uint8_t packetQueueStorage[300];
} Gea2PacketEndpoint_BackgroundSingleWireUartInterfaceDefaultConfigurationResources_t;

/*!
 * Initialize the packet endpoint with a reasonable default configuration.
 * @param instance The endpoint.
 * @param resources All RAM resources required to configure the endpoint with the default configuration.
 * @param uart The UART to use.
 * @param timeSource The time source that will be used by the GEA2 interface.
 * @param crc16Calculator The CRC16 calculator to use in the GEA2 interface.
 * @param address The address of the endpoint.
 */
void Gea2PacketEndpoint_BackgroundSingleWireUartInterface_InitWithDefaultConfiguration(
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t *instance,
   Gea2PacketEndpoint_BackgroundSingleWireUartInterfaceDefaultConfigurationResources_t *resources,
   I_Uart_t *uart,
   I_TimeSource_t *timeSource,
   I_Crc16Calculator_t *crc16Calculator,
   uint8_t address);

/*!
 * Initialize the packet endpoint with a custom configuration.
 * @param instance The endpoint.
 * @param uart The UART to use.
 * @param timeSource The time source that will be used by the GEA2 interface.
 * @param crc16Calculator The CRC16 calculator to use in the GEA2 interface.
 * @param address The address of the endpoint.
 * @param interfaceSendBuffer The GEA2 interface send/receive buffer.
 * @param interfaceSendBufferSize The size of the GEA2 interface send/receive buffer.
 * @param isrSafeUartBuffer The buffer for bytes received in the interrupt context.
 * @param isrSafeUartBufferSize The size of the buffer for bytes received in the interrupt context.
 * @param packetQueueStorage The buffer used for queueing sent packets.
 * @param packetQueueStorageSize The size of the buffer used for queueing sent packets.
 */
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
   size_t packetQueueStorageSize);

/*!
 * Run the packet endpoint. This allows the underlying interface to run.
 * @param instance The endpoint.
 */
void Gea2PacketEndpoint_BackgroundSingleWireUartInterface_Run(
   Gea2PacketEndpoint_BackgroundSingleWireUartInterface_t *instance);

#endif
