/*!
 * @file
 * @brief Implementation of the wiring object that goes from a GEA2 message endpoint to a data source
 * via a subscription front-end and a read/write manager.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdbool.h>
#include "DataSourcePacketGea2MessageEndpointConnector.h"
#include "DataSourcePacketVerifier.h"
#include "StackAllocator.h"
#include "ErdCommands.h"
#include "uassert.h"
#include "utils.h"

typedef struct
{
   DataSourcePacketGea2MessageEndpointConnector_t *instance;
   const Gea2Message_t *message;
} MessageReceivedCallbackContext_t;

static bool ValidMessageOfType(const Gea2Message_t *message, DataSourcePacketType_t packetType)
{
   return DataSourcePacketVerifier_Verify(Gea2Message_GetConstPayload(message),
      Gea2Message_GetPayloadLength(message), packetType);
}

static void MessageReceivedCallback(void *_context, void *allocatedBlock)
{
   REINTERPRET(context, _context, MessageReceivedCallbackContext_t *);
   REINTERPRET(instance, context->instance, DataSourcePacketGea2MessageEndpointConnector_t *);
   REINTERPRET(message, context->message, const Gea2Message_t *);
   REINTERPRET(response, allocatedBlock, Gea2Message_t *);

   uint8_t responseSize = 0;
   bool needToSendResponse = false;

   switch(Gea2Message_GetCommand(message))
   {
      case ErdCommand_ReadRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_ReadRequest))
         {
            DataSourcePacketReadWriteManager_Read(
               instance->_private.readWriteManager,
               Gea2Message_GetConstPayload(message),
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize);
            needToSendResponse = true;
         }
         break;

      case ErdCommand_WriteRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_WriteRequest))
         {
            DataSourcePacketReadWriteManager_Write(
               instance->_private.readWriteManager,
               Gea2Message_GetConstPayload(message),
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize);
            needToSendResponse = true;
         }
         break;

      case ErdCommand_SubscribeRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_SubscribeRequest))
         {
            DataSourcePacketSubscriptionFrontEnd_SubscribeRequest(
               instance->_private.subscriptionFrontEnd,
               Gea2Message_GetConstPayload(message),
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize,
               Gea2Message_GetSource(message));
            needToSendResponse = true;
         }
         break;

      case ErdCommand_UnsubscribeRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_UnsubscribeRequest))
         {
            DataSourcePacketSubscriptionFrontEnd_UnsubscribeRequest(
               instance->_private.subscriptionFrontEnd,
               Gea2Message_GetConstPayload(message),
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize,
               Gea2Message_GetSource(message));
            needToSendResponse = true;
         }
         break;

      case ErdCommand_SubscriptionListRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_SubscriptionListRequest))
         {
            DataSourcePacketSubscriptionFrontEnd_ListRequest(
               instance->_private.subscriptionFrontEnd,
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize,
               Gea2Message_GetSource(message));
            needToSendResponse = true;
         }
         break;

      case ErdCommand_PublishAcknowledgement:
         if(ValidMessageOfType(message, DataSourcePacketType_PublishAcknowledgement))
         {
            DataSourcePacketSubscriptionFrontEnd_PublishAcknowledge(
               instance->_private.subscriptionFrontEnd,
               Gea2Message_GetSource(message));
         }
         break;

      case ErdCommand_OpenLoopWriteRequest:
         if(ValidMessageOfType(message, DataSourcePacketType_WriteRequest))
         {
            DataSourcePacketReadWriteManager_Write(
               instance->_private.readWriteManager,
               Gea2Message_GetConstPayload(message),
               Gea2Message_GetPayload(response),
               instance->_private.maxMessagePayloadSize,
               &responseSize);
         }
         break;

      default:
         break;
   }

   if(needToSendResponse)
   {
      Gea2Message_SetDestination(response, Gea2Message_GetSource(message));
      Gea2Message_SetCommand(response, Gea2Message_GetCommand(message));
      Gea2Message_SetPayloadLength(response, responseSize);

      Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, response, instance->_private.responseRetries);
   }
}

static void MessageReceived(void *context, const void *_args)
{
   REINTERPRET(instance, context, DataSourcePacketGea2MessageEndpointConnector_t *);
   REINTERPRET(args, _args, const Gea2MessageEndpointOnReceiveArgs_t *);
   MessageReceivedCallbackContext_t callbackContext;
   
   callbackContext.instance = instance;
   callbackContext.message = args->message;

   StackAllocator_Allocate((size_t)(GEA2MESSAGE_OVERHEAD + instance->_private.maxMessagePayloadSize), MessageReceivedCallback, &callbackContext);
}

void DataSourcePacketGea2MessageEndpointConnector_Init(
   DataSourcePacketGea2MessageEndpointConnector_t *instance,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   I_DataSourcePacketReadWriteManager_t *readWriteManager,
   I_DataSourcePacketSubscriptionFrontEnd_t *subscriptionFrontEnd,
   const uint8_t maxMessagePayloadSize,
   const uint8_t responseRetries,
   const uint8_t publishRetries)
{
   instance->_private.messageEndpoint = messageEndpoint;
   instance->_private.readWriteManager = readWriteManager;
   instance->_private.responseRetries = responseRetries;
   instance->_private.publishRetries = publishRetries;
   instance->_private.maxMessagePayloadSize = maxMessagePayloadSize;
   instance->_private.subscriptionFrontEnd = subscriptionFrontEnd;

   EventSubscription_Init(&instance->_private.messageReceivedSubscription, instance, MessageReceived);
   Event_Subscribe(Gea2MessageEndpoint_GetOnReceiveEvent(messageEndpoint), &instance->_private.messageReceivedSubscription);
}

static void RunCallback(void *context, void *allocatedBlock)
{
   REINTERPRET(instance, context, DataSourcePacketGea2MessageEndpointConnector_t *);
   REINTERPRET(publish, allocatedBlock, Gea2Message_t *);
   uint8_t publishSize;
   uint8_t subscriberId;

   if(DataSourcePacketSubscriptionFrontEnd_ServiceSubscriptions(instance->_private.subscriptionFrontEnd,
      Gea2Message_GetPayload(publish), instance->_private.maxMessagePayloadSize, &publishSize, &subscriberId))
   {
      Gea2Message_SetDestination(publish, subscriberId);
      Gea2Message_SetCommand(publish, ErdCommand_Publish);
      Gea2Message_SetPayloadLength(publish, publishSize);

      Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, publish, instance->_private.publishRetries);
   }
}

void DataSourcePacketGea2MessageEndpointConnector_Run(DataSourcePacketGea2MessageEndpointConnector_t * instance)
{
   StackAllocator_Allocate((size_t)(GEA2MESSAGE_OVERHEAD + instance->_private.maxMessagePayloadSize),
      RunCallback, instance);
}
