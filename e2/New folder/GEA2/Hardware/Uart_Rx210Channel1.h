/*!
 * @file
 * @brief Header file for the Channel 1 RX210 uart driver for GEA2
 *
 * Copyright General Electric Appliances - Confidential - All rights reserved.
 */

#ifndef UART_RX210CHANNEL1_H
#define UART_RX210CHANNEL1_H

#include "I_Uart.h"

/*!
 * This function initializes the channel 1 UART for GEA2
 * @return Returns the interface to the Uart.
 */
I_Uart_t * Uart_Rx210Channel1_Init(void);

#endif
