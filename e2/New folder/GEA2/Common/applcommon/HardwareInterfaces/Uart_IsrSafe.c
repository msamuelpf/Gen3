/*!
 * @file
 * @brief Implementation of an ISR-safe UART wrapper.  Uses a ring buffer queue received bytes and
 * then consumes from the queue in the background.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Uart_IsrSafe.h"
#include "uassert.h"
#include "utils.h"

static void ReceiveCallback(void *context, const void *args)
{
   REINTERPRET(instance, context, Uart_IsrSafe_t *);
   REINTERPRET(onReceiveArgs, args, const UartOnReceiveArgs_t *);

   // Cannot allow the ring buffer to get full or ISR safety cannot be guaranteed
   if(RingBuffer_Count(&instance->_private.ringBuffer) < (RingBuffer_Capacity(&instance->_private.ringBuffer) - 1))
   {
      RingBuffer_Add(&instance->_private.ringBuffer, (const void *)&onReceiveArgs->byte);
   }
}

static void TransmitCallback(void *context, const void *args)
{
   REINTERPRET(instance, context, Uart_IsrSafe_t *);
   instance->_private.transmitOccurred = true;
   IGNORE_ARG(args);
}

static void ErrorCallback(void *context, const void *args)
{
   REINTERPRET(instance, context, Uart_IsrSafe_t *);
   instance->_private.errorOccurred = true;
   IGNORE_ARG(args);
}

static void Send(I_Uart_t *_instance, const uint8_t byte)
{
   REINTERPRET(instance, _instance, Uart_IsrSafe_t *);
   Uart_Send(instance->_private.inner, byte);
}

static I_Event_t * GetOnReceiveEvent(I_Uart_t *_instance)
{
   REINTERPRET(instance, _instance, Uart_IsrSafe_t *);
   return &instance->_private.OnReceive.interface;
}

static I_Event_t * GetOnTransmitEvent(I_Uart_t *_instance)
{
   REINTERPRET(instance, _instance, Uart_IsrSafe_t *);
   return &instance->_private.OnTransmit.interface;
}

static I_Event_t * GetOnErrorEvent(I_Uart_t *_instance)
{
   REINTERPRET(instance, _instance, Uart_IsrSafe_t *);
   return &instance->_private.OnError.interface;
}

static const I_Uart_Api_t api =
   { Send, GetOnReceiveEvent, GetOnTransmitEvent, GetOnErrorEvent };

void Uart_IsrSafe_Init(Uart_IsrSafe_t *instance, I_Uart_t *inner, void *queueBuffer, size_t queueBufferSize)
{
   uassert(queueBuffer);

   instance->interface.api = &api;
   instance->_private.inner = inner;

   Event_Synchronous_Init(&instance->_private.OnReceive);
   Event_Synchronous_Init(&instance->_private.OnError);
   Event_Synchronous_Init(&instance->_private.OnTransmit);

   // Needs to happen first in case we get a byte while we're in init
   RingBuffer_Init(&instance->_private.ringBuffer, queueBuffer, (unsigned)queueBufferSize, (unsigned)sizeof(uint8_t));

   EventSubscription_Init(&instance->_private.onReceiveSubscription, instance, ReceiveCallback);
   EventSubscription_Init(&instance->_private.onTransmitSubscription, instance, TransmitCallback);
   EventSubscription_Init(&instance->_private.onErrorSubscription, instance, ErrorCallback);

   Event_Subscribe(Uart_GetOnReceiveEvent(inner), &instance->_private.onReceiveSubscription);
   Event_Subscribe(Uart_GetOnTransmitEvent(inner), &instance->_private.onTransmitSubscription);
   Event_Subscribe(Uart_GetOnErrorEvent(inner), &instance->_private.onErrorSubscription);
}

void Uart_IsrSafe_Run(Uart_IsrSafe_t *instance)
{
   size_t queueCount;
   queueCount = RingBuffer_Count(&instance->_private.ringBuffer);

   if(instance->_private.errorOccurred)
   {
      instance->_private.errorOccurred = false;
      Event_Synchronous_Publish(&instance->_private.OnError, NULL);
   }

   if(instance->_private.transmitOccurred)
   {
      instance->_private.transmitOccurred = false;
      Event_Synchronous_Publish(&instance->_private.OnTransmit, NULL);
   }

   while(queueCount)
   {
      uint8_t byte;

      RingBuffer_Remove(&instance->_private.ringBuffer, (void *)&byte);

      {
         Event_Synchronous_Publish(&instance->_private.OnReceive, &byte);
      }

      queueCount--;
   }
}

