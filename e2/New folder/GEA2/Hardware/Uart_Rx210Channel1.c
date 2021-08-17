/*!
 * @file
 * @brief Implementation of the Channel 1 RX210 uart driver for GEA2
 *
 * Copyright General Electric Appliances - Confidential - All rights reserved.
 */

#include "Uart_Rx210Channel1.h"
#include "Event_Synchronous.h"
#include "I_Interrupt.h"
#include "I_Uart.h"
#include "utils.h"
#include "uassert.h"
//#include "ClockConfig.h"   // Get PCLK definition
#include "iodefineRX210.h"
#include "Event_Null.h"
#include "interrupt_timing.h"

#define	SYSTEM_CLOCK				50000000
#define U32_TARGET_BAUD_RATE (19200)

typedef struct
{
   I_Uart_t interface;
   Event_Synchronous_t onReceiveEvent;
   Event_Synchronous_t onErrorEvent;
} Uart_t;

static Uart_t uart;

/*!
 * Transmit a single byte out the UART1 port
 * @param instance
 * @param byte
 */
static void Send(I_Uart_t *instance, const uint8_t byte)
{
   (void)instance;

   SCI1.TDR = byte;
   while(SCI1.SSR.BIT.TEND != 1)
   {

   }
}

static I_Event_t * GetOnReceiveEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return &uart.onReceiveEvent.interface;
}

static I_Event_t * GetOnTransmitEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return Event_Null_GetInstance();
}

static I_Event_t * GetOnErrorEvent(I_Uart_t *_instance)
{
   IGNORE_ARG(_instance);
   return &uart.onErrorEvent.interface;
}

static const I_Uart_Api_t api =
   { Send, GetOnReceiveEvent, GetOnTransmitEvent, GetOnErrorEvent };

/*!
 * Interrupt service routine for UART1 rx data
 */
 #pragma interrupt SCI1_RXI1(vect=VECT_SCI1_RXI1)
 //void SCI1_RXI1(void) __attribute__ ((interrupt));
void SCI1_RXI1(void)
{
   uint8_t receivedData;

   ENTER_ISR;

   receivedData = SCI1 .RDR;

   {
      UartOnReceiveArgs_t args =
         { receivedData };
      Event_Synchronous_Publish(&uart.onReceiveEvent, &args);
   }

   EXIT_ISR;
}

/*!
 * Interrupt service routine for UART1 rx error
 */
 #pragma interrupt SCI1_ERI1(vect=VECT_SCI1_ERI1)
//void SCI1_ERI1(void) __attribute__ ((interrupt));
void SCI1_ERI1(void)
{
   uint8_t received_data;

   ENTER_ISR;
   received_data = SCI1.RDR;
   // Remove warning
   (void)received_data;
   // Disable the module and then re-init
   SCI1.SSR.BIT.PER = 0;
   SCI1.SSR.BIT.FER = 0;
   SCI1.SSR.BIT.ORER = 0;
   MSTP_SCI1 = 1;
   MSTP_SCI1 = 0;

   Event_Synchronous_Publish(&uart.onErrorEvent, NULL);
   EXIT_ISR;
}

/*!
 * Interrupt service routine for UART1 tx error
 */
#pragma interrupt SCI1_TEI1(vect=VECT_SCI1_TEI1)
//void SCI1_TEI1(void) __attribute__ ((interrupt));
void SCI1_TEI1(void)
{
   uint8_t received_data;

   ENTER_ISR;
   received_data = SCI1.RDR;
   // Remove warning
   (void)received_data;
   // Disable the module and then re-init
   SCI1.SSR.BIT.PER = 0;
   SCI1.SSR.BIT.FER = 0;
   SCI1.SSR.BIT.ORER = 0;
   MSTP_SCI1 = 1;
   MSTP_SCI1 = 0;

   Event_Synchronous_Publish(&uart.onErrorEvent, NULL);
   EXIT_ISR;
}

I_Uart_t * Uart_Rx210Channel1_Init(void)
{
   // Initialize the events first to account for the possibility of the interrupt firing right after
   // interrupts are enabled
   Event_Synchronous_Init(&uart.onReceiveEvent);
   Event_Synchronous_Init(&uart.onErrorEvent);

   // Configure SCI1/UART1 on board
   // First, allow writes to Module-Stop-Control-Register
   SYSTEM.PRCR.WORD = 0xA502;
   // Now turn on SCI1
   MSTP_SCI1 = 0;
   // Disable UART in/out while we fiddle with it, set the clock to internal (CKE=0)
   SCI1.SCR.BYTE = 0;
   // Setup port P30 (rx) and P26 (tx) for use by UART
   PORT3.PMR.BIT.B0 = 1;
   PORT2.PMR.BIT.B6 = 1;
   PORT2.PDR.BIT.B6 = 1;
   PORT2.PODR.BIT.B6 = 1;
   // Setup the data format
   // Bit - Setting : Comment
   // 0:1 -     00  : Clock Select PCLK
   //   2 -      0  : No multi-processor mode
   //   3 -      0  : 1 Stop bit
   //   4 -      0  : Even Parity
   //   5 -      0  : No Parity
   //   6 -      0  : 8 Bytes
   //   7 -      0  : Async
   SCI1.SMR.BYTE = 0x00;
   // Setup BRR and the clock multiplier
   SCI1.SEMR.BIT.ABCS = 1;// 8 base clock cycles per 1 bit
   SCI1.BRR = (uint8_t)((SYSTEM_CLOCK/(32L*U32_TARGET_BAUD_RATE)) - 1);
   //SCI1.BRR = (uint8_t)((SYSTEM_CLOCK / (32L * U32_TARGET_BAUD_RATE / 2L)) - 1);
   // Set up interrupts in the Interrupt-Control-Unit
   // There is only one priority register per SCI port
   ICU.IPR[IPR_SCI1_RXI1].BIT.IPR = 10;
   // But there are 4 separate interrupt enable bits
   ICU.IER[IER_SCI1_RXI1].BIT.IEN_SCI1_RXI1 = 1;
   ICU.IER[IER_SCI1_TXI1].BIT.IEN_SCI1_TXI1 = 0;
   ICU.IER[IER_SCI1_ERI1].BIT.IEN_SCI1_ERI1 = 1;
   ICU.IER[IER_SCI1_TEI1].BIT.IEN_SCI1_TEI1 = 1;

   // Enable writing to the PFSWE bit
   MPC.PWPR.BIT.B0WI = 0;
   // Enable writing to the PFS register
   MPC.PWPR.BIT.PFSWE = 1;

   // Assign P30 and P26 to function as RXD1 and TXD1...
   MPC.P30PFS.BYTE = 0x0A;
   MPC.P26PFS.BYTE = 0x0A;

   // Disable writing to the PFS register
   MPC.PWPR.BIT.PFSWE = 0;
   // Disable writing to the PFSWE bit
   MPC.PWPR.BIT.B0WI = 1;

   ICU.IR[IR_SCI1_TXI1].BIT.IR = 0;
   // Finally, enable UART rx and interrupts
   SCI1.SCR.BIT.TIE = 0;// Transmit Interrupt Disabled, not using.
   SCI1.SCR.BIT.RIE = 1;// Receive Interrupt Enabled
   SCI1.SCR.BIT.TE = 1;// Transmit is disabled, not using it yet.
   SCI1.SCR.BIT.RE = 1;// Receive Enabled

   uart.interface.api = &api;

   return &uart.interface;
}
