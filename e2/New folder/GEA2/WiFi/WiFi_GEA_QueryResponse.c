/*!
 * @file
 * @brief Module supports GEA2 messages queries from WIFI module or broadcast addresses.
 *       It exists because the WiFi module will perform a broadcast query to establish which boards are
 *       in the eco-system.  After receiving a response to the version command (0x001) it will also ask
 *       for some parametric data including:
 *          Max parametric Fields and size (0xDD 0x03 0x00) - response is 0xDD 0x03 0x04 size (TBD - Usually 0x20)
 *          Model Number/SKU (0xDD 0x03 0x03) -- response
 *          Serial Number of Appliance (0xDD 0x03 0x04)
 *          For any other parametric query it is OK to issue an invalid response as follows:
 *            Response data is 0xDD 0x03, ##, 0x00, 0xFF - where:
 *             0xDD,0x03 is the parametric read request
 *             ## is the parametric field requested
 *             0xFF is the error code - indicating it is invalid
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include <string.h>
#include <stdbool.h>
#include "WiFi_GEA_QueryResponse.h"
#include "uassert.h"
#include "utils.h"
#include "Gea2Message.h"
#include "StackAllocator.h"
#include <Tables.h>

enum
{
   BytesInVersion = 4,
   SingleByteCommandSize = 1,
   VersionRequestSize = SingleByteCommandSize,
   VersionResponseSize = SingleByteCommandSize + BytesInVersion,

   BootHeaderParametricItemCount = 4,
   BootLoaderParametricItemMaxSize = 32,

   BootLoaderParametricItem_RequestCountAndSize = 0,
   BootLoaderParametricItem_ModelNumber = 3,
   BootLoaderParametricItem_SerialNumber = 4,

   Gea2CommonCommand_Version = 0x0001,
   Gea2CommonCommand_BootLoaderParametricData = -8957,  //0xDD03

};

static void SendVersionResponse(WiFi_GEA_QueryResponse_t *instance, const Gea2Packet_t *packet)
{
   STACK_ALLOC_GEA2PACKET(response, VersionResponseSize);
   uint8_t *payloadInsertionPoint = response->payload;

   const char fakeSoftwareVersion[] =
      { VersionCriticalMajor, VersionCriticalMinor, VersionNonCriticalMajor, VersionNonCriticalMinor };

   response->destination = packet->source;
   response->payloadLength = VersionResponseSize;

   *payloadInsertionPoint++ = Gea2CommonCommand_Version;
   memcpy(payloadInsertionPoint, fakeSoftwareVersion, BytesInVersion);
   Gea2PacketEndpoint_Send(instance->_private.applicationNode, response, PacketResponseRetries);
}

static void HandleBootLoaderParametricItemRequest(WiFi_GEA_QueryResponse_t *instance, const Gea2Packet_t *packet)
{
   STACK_ALLOC_GEA2PACKET(response, GEA2PACKET_MAXPAYLOAD);
   uint8_t *payloadInsertionPoint = response->payload;
   uint8_t item = packet->payload[2];
   const int8_t *bootLoaderParametricItemData;
   uint8_t dataSize;

   response->destination = packet->source;
   *payloadInsertionPoint++ = (uint8_t)(Gea2CommonCommand_BootLoaderParametricData >> 8);
   *payloadInsertionPoint++ = (uint8_t)(Gea2CommonCommand_BootLoaderParametricData & 0x00FF);
   *payloadInsertionPoint++ = item;

   if(BootLoaderParametricItem_RequestCountAndSize == item)
   {
      *payloadInsertionPoint++ = BootHeaderParametricItemCount;
      *payloadInsertionPoint++ = BootLoaderParametricItemMaxSize;
   }
   else if((BootLoaderParametricItem_ModelNumber == item) || (BootLoaderParametricItem_SerialNumber == item))
   {
      if(BootLoaderParametricItem_ModelNumber == item)
      {
         dataSize = 14;//BOOTLOADER_PARAMETRIC_MODEL_DATA_LENGTH;
         bootLoaderParametricItemData = pS_SkuParamROM->u8SKU;//BOOTLOADER_PARAMETRIC_MODEL_DATA;

      }
      else  // BootLoaderParametricItem_SerialNumber
      {
         dataSize = 11;//BOOTLOADER_PARAMETRIC_SERIAL_NUMBER_DATA_LENGTH;
         bootLoaderParametricItemData = pS_SkuParamROM->u8SerialNumber;//T_S_SKU_PARAM->u8SerialNumber;//BOOTLOADER_PARAMETRIC_SERIAL_NUMBER_DATA;
      }
      *payloadInsertionPoint++ = dataSize;
      memcpy(payloadInsertionPoint, bootLoaderParametricItemData, dataSize);
      payloadInsertionPoint += dataSize;
   }
   else  // invalid item requested
   {
      *payloadInsertionPoint++ = 0;
      *payloadInsertionPoint++ = 0xFF;
   }
   response->payloadLength = (uint8_t)(payloadInsertionPoint - response->payload);
   Gea2PacketEndpoint_Send(instance->_private.applicationNode, response, PacketResponseRetries);
}

static void HandlePacket(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFi_GEA_QueryResponse_t *);
   REINTERPRET(args, _args, const Gea2PacketEndpointOnReceiveArgs_t *);
   const Gea2Packet_t *packet = args->packet;
   int16_t command = packet->payload[0];

   if(0xDD == command)
   {
      command = (command << 8) + packet->payload[1];
   }

   switch(command)
   {
      case Gea2CommonCommand_Version:
         SendVersionResponse(instance, packet);
         break;

      case Gea2CommonCommand_BootLoaderParametricData:
         HandleBootLoaderParametricItemRequest(instance, packet);
         break;

      default:
         break;
   }
}

void WiFi_GEA_QueryResponse_Init(
   WiFi_GEA_QueryResponse_t *instance,
   I_Gea2PacketEndpoint_t *applicationNode,
   I_Crc16Calculator_t *crcCalculator,
   Crc16_t seed)
{
   instance->_private.applicationNode = applicationNode;
   instance->_private.crcCalculator = crcCalculator;
   instance->_private.seed = seed;

   EventSubscription_Init(&instance->_private.gea2PacketSubscription, instance, HandlePacket);
   Event_Subscribe(Gea2PacketEndpoint_GetOnReceiveEvent(applicationNode), &instance->_private.gea2PacketSubscription);
}
