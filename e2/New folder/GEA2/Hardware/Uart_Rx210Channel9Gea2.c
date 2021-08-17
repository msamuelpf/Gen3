/*!
 * @file
 * @brief Main external UART driver
 *
 * Copyright General Electric Corporation - GE Confidential - All rights reserved.
 */

#include <stdint.h>
#include <string.h>
#include "iodefineRX210.h"
#include "I_Interrupt.h"
#include "I_Uart.h"
#include "uassert.h"
#include "Uart_Rx210Channel9Gea2.h"
//***#include "ClockConfig.h"   // Get PCLK definition
#include "Event_Simple.h"
#include "Event_SafeSynchronous.h"
#include "utils.h"
//#include <EFX1854P001.h>
#include <Drv_Uart.h>

#define	SYSTEM_CLOCK				50000000
#define U32_TARGET_BAUD_RATE        ((uint32_t)19200)

// There is no Tx interrupt since we're doing GEA2 data here
typedef struct
{
   Event_Simple_t OnReceiveEvent;
   Event_Simple_t OnTransmitEvent;
   Event_Simple_t OnErrorEvent;
   I_Uart_t Uart;
} Uart_Rx210Channel9Gea2_t;

static Uart_Rx210Channel9Gea2_t uart;

/*!
 * Transmit a single byte out the UART9 port
 * @param instance
 * @param byte
 */
static void Send(I_Uart_t *instance, const uint8_t byte)
{
   (void)instance;
   SCI9.TDR = byte;
}

static I_Event_t * GetOnReceiveEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return &uart.OnReceiveEvent.interface;
}

static I_Event_t * GetOnTransmitEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return &uart.OnTransmitEvent.interface;
}

static I_Event_t * GetOnErrorEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return &uart.OnErrorEvent.interface;
}

static const I_Uart_Api_t api =
   { Send, GetOnReceiveEvent, GetOnTransmitEvent, GetOnErrorEvent };

/*!
 * Interrupt service routine for UART9 rx data
 */
#pragma interrupt SCI9_RXI9(vect=VECT_SCI9_RXI9)
//***void SCI9_RXI9(void) __attribute ((interrupt));
void SCI9_RXI9(void)
{
   uint8_t receivedData;
   uint8_t lu8CommProtocol;

   lu8CommProtocol = FNE_GetCommProtocol();
   
   if(lu8CommProtocol == C_GE_COMM)
     {
       receivedData = SCI9 .RDR;
       {
          UartOnReceiveArgs_t args =
             { receivedData };
          Event_Simple_Publish(&uart.OnReceiveEvent, &args);
       }
     }
   else
     {
       ISR_RxInterrupt(SCI9.RDR);
     }
}

/*!
 * Interrupt service routine for GEA2_UART rx error
 */
#pragma interrupt SCI9_ERI9(vect=VECT_SCI9_ERI9)
//***void SCI9_ERI9(void) __attribute__ ((interrupt));
void SCI9_ERI9(void)
{
   uint8_t received_data;
   uint8_t lu8CommProtocol;

   lu8CommProtocol = FNE_GetCommProtocol();
   
   if(lu8CommProtocol == C_GE_COMM)
     {
       received_data = SCI9.RDR;
       // Remove warning
       (void)received_data;
       // Disable the module and then re-init
       SCI9.SSR.BIT.PER = 0;
       SCI9.SSR.BIT.FER = 0;
       SCI9.SSR.BIT.ORER = 0;
       MSTP_SCI9 = 1;
       MSTP_SCI9 = 0;

       Event_Simple_Publish(&uart.OnErrorEvent, NULL);
     }
   else
     {
       ISR_ErrorReceiveInterrupt(SCI9.RDR);
     }
}

/*!
 * Interrupt service routine for GEA2_UART tx error
 */
#pragma interrupt SCI9_TEI9(vect=VECT_SCI9_TEI9)
//***void SCI9_TEI9(void) __attribute__ ((interrupt));
void SCI9_TEI9(void)
{
   uint8_t received_data;
   uint8_t lu8CommProtocol;

   lu8CommProtocol = FNE_GetCommProtocol();
   
   if(lu8CommProtocol == C_GE_COMM)
     {
       received_data = SCI9.RDR;
       // Remove warning
       (void)received_data;
       // Disable the module and then re-init
       SCI9.SSR.BIT.PER = 0;
       SCI9.SSR.BIT.FER = 0;
       SCI9.SSR.BIT.ORER = 0;
       MSTP_SCI9 = 1;
       MSTP_SCI9 = 0;

       Event_Simple_Publish(&uart.OnErrorEvent, NULL);    
     }
   else
     {
       ISR_TxEndInterrupt();
     }
}

/*!
 * Initialize GEA2_UART as GEA2 port - 19200, 8,n,1 with no Tx interrupts
 * @return
 */
I_Uart_t *Uart_Rx210Channel9Gea2_Init(void)
{
	// Initialize the events first to account for the possibility of the interrupt firing right after
	// interrupts are enabled
	Event_Simple_Init(&uart.OnReceiveEvent);
	Event_Simple_Init(&uart.OnTransmitEvent);
	Event_Simple_Init(&uart.OnErrorEvent);

   // Configure SCI9/UART9 on board
   // First, allow writes to Module-Stop-Control-Register
   SYSTEM.PRCR.WORD = 0xA502;
   // Now turn on SCI9
   MSTP_SCI9 = 0;
   // Disable UART in/out while we fiddle with it, set the clock to internal (CKE=0)
   SCI9.SCR.BYTE  = 0;
   // Setup port PB6 (rx) and PB7 (tx) for use by UART
   PORTB.PMR.BIT.B6 = 1;
   PORTB.PMR.BIT.B7 = 1;
   PORTB.PDR.BIT.B7 = 1;
   PORTB.PODR.BIT.B7 = 1;
   // Setup the data format
   // Bit - Setting : Comment
   // 0:1 -     00  : Clock Select PCLK
   //   2 -      0  : No multi-processor mode
   //   3 -      0  : 1 Stop bit
   //   4 -      0  : Even Parity
   //   5 -      0  : No Parity
   //   6 -      0  : 8 Bytes
   //   7 -      0  : Async
   SCI9.SMR.BYTE =  0x00;
   // Setup BRR and the clock multiplier
   SCI9.SEMR.BIT.ABCS = 1; // 8 base clock cycles per 1 bit
   //***SCI9.BRR = (uint8_t)((U32_PCLK/(32L*U32_TARGET_BAUD_RATE/2L)) - 1);
   SCI9.BRR = (uint8_t)((SYSTEM_CLOCK/(32L*U32_TARGET_BAUD_RATE)) - 1);
   //***uart.uartPort->BRR = (SYSTEM_CLOCK/(64*uart.baudRate)) - 1;
   // Set up interrupts in the Interrupt-Control-Unit
   // There is only one priority register per SCI port
   ICU.IPR[IPR_SCI9_RXI9].BIT.IPR = 11;
   // But there are 4 separate interrupt enable bits
   ICU.IER[IER_SCI9_RXI9].BIT.IEN_SCI9_RXI9 = 1;
   ICU.IER[IER_SCI9_TXI9].BIT.IEN_SCI9_TXI9 = 0;
   ICU.IER[IER_SCI9_ERI9].BIT.IEN_SCI9_ERI9 = 1;
   ICU.IER[IER_SCI9_TEI9].BIT.IEN_SCI9_TEI9 = 1;
   // Enable the Interrupt should be deferred until the structure is enabled

   // Enable writing to the PFSWE bit
   MPC.PWPR.BIT.B0WI = 0;
   // Enable writing to the PFS register
   MPC.PWPR.BIT.PFSWE = 1;

   // Assign PB6 and PB7 to function as RXD9 and TXD9...
   MPC.PB6PFS.BYTE = 0x0A;
   MPC.PB7PFS.BYTE = 0x0A;

   // Disable writing to the PFS register
   MPC.PWPR.BIT.PFSWE = 0;
   // Disable writing to the PFSWE bit
   MPC.PWPR.BIT.B0WI = 1;

   ICU.IR[IR_SCI9_TXI9].BIT.IR = 0;
   // Finally, enable UART rx and interrupts
   SCI9.SCR.BIT.TIE = 0;  // Transmit Interrupt Disabled
   SCI9.SCR.BIT.RIE = 1;  // Receive Interrupt Enabled
   SCI9.SCR.BIT.TE = 1;   // Transmit Enabled
   SCI9.SCR.BIT.RE = 1;   // Receive Enabled

   uart.Uart.api = &api;

   return &uart.Uart;
}
