/*!
 * @file
 * @brief Generic UART interface.  Baud rate is not defined as part of the interface and if a client
 * requires a particular baud rate, it must be part of the contract for initializing that module.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef I_UART_H
#define I_UART_H

#include <stdint.h>
#include "I_Event.h"

/*!
 * Event args for OnReceive event.
 */
typedef struct
{
   /*!
    * Received byte.
    */
   const uint8_t byte;
} UartOnReceiveArgs_t;

struct I_Uart_Api_t;

typedef struct
{
   const struct I_Uart_Api_t *api;
} I_Uart_t;

typedef struct I_Uart_Api_t
{
   /*!
    * Send a serial byte via a UART.
    * @param instance The UART.
    * @param byte The byte to send.
    */
   void (*Send)(I_Uart_t *instance, const uint8_t byte);

   /*!
    * Get the event raised when a byte is received.
    * @note event args are of type UartOnReceiveArgs_t
    * @param instance The instance
    * @return The event
    */
   I_Event_t * (*GetOnReceiveEvent)(I_Uart_t *instance);

   /*!
    * Get the event raised when a byte is transmitted.
    * @note no event args are provided.
    * @param instance The instance
    * @return The event
    */
   I_Event_t * (*GetOnTransmitEvent)(I_Uart_t *instance);

   /*!
    * Get the event raised when a UART error occurs.
    * @note no event args are provided.
    * @param instance The instance.
    * @return The event
    */
   I_Event_t * (*GetOnErrorEvent)(I_Uart_t *instance);
} I_Uart_Api_t;

#define Uart_Send(instance, byte) \
   (instance)->api->Send((instance), (byte))

#define Uart_GetOnReceiveEvent(instance) \
   (instance)->api->GetOnReceiveEvent((instance))

#define Uart_GetOnTransmitEvent(instance) \
   (instance)->api->GetOnTransmitEvent((instance))

#define Uart_GetOnErrorEvent(instance) \
   (instance)->api->GetOnErrorEvent((instance))

#endif
