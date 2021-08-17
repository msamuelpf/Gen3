/*!
 * @file
 * @brief Interrupt-safe UART wrapper -- takes an ISR-driven UART and queues incoming bytes and errors
 * to be consumed in the background.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef UART_ISRSAFE_H
#define UART_ISRSAFE_H

#include <stdbool.h>
#include <stddef.h>
#include "I_Uart.h"
#include "RingBuffer.h"
#include "Event_Synchronous.h"

/*!
 * ISR-safe UART wrapper.  Struct members should be considered private.
 */
typedef struct
{
   I_Uart_t interface;

   struct
   {
      I_Uart_t *inner;
      RingBuffer_t ringBuffer;
      Event_Synchronous_t OnReceive;
      Event_Synchronous_t OnTransmit;
      Event_Synchronous_t OnError;
      EventSubscription_t onReceiveSubscription;
      EventSubscription_t onTransmitSubscription;
      EventSubscription_t onErrorSubscription;
      bool errorOccurred :1;
      bool transmitOccurred :1;
   } _private;
} Uart_IsrSafe_t;

/*!
 * Initialize an ISR-safe UART wrapper.
 * @pre instance != NULL
 * @pre inner != NULL
 * @pre queueBuffer != NULL
 * @pre queueBufferSize > 0
 * @param instance The UART wrapper.
 * @param inner The wrapped UART.
 * @param queueBuffer Storage allocated for the receive queue.
 * @param queueBufferSize Size of storage allocated for the receive queue.
 */
void Uart_IsrSafe_Init(Uart_IsrSafe_t *instance, I_Uart_t *inner, void *queueBuffer, size_t queueBufferSize);

/*!
 * Process received UART events from the background.
 * @pre instance != NULL
 * @param instance The UART wrapper.
 */
void Uart_IsrSafe_Run(Uart_IsrSafe_t *instance);

#endif
