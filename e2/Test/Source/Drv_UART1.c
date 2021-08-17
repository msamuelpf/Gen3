/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_UART1.c                                           */
/*  DATE        :05/05/2014                                            */
/*  DESCRIPTION :Set the initialization, functions & interrupt for UART*/
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

/*****************************************************************************
    Pragma directive
*****************************************************************************/
/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Drv_UART1.h"

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   Configures the UART for transmision and reception 
                9600, 8bit, No Parity, 1 Stop Bit.
************************************************************************/
void SR_InitUART1(void)
{
/*
Starting initial setting

Release the serial array unit from the reset status and start clock supply.
Setting the PER0 register

Set the operation clock.
Setting the SPSm register

Set an operation mode, etc.
Setting the SMRmn register

Set a communication format.
Setting the SCRmn register

Set a transfer baud rate (setting the transfer clock by dividing the operation clock (fMCK)).
Setting the SDRmn register

Set the initial output level of the serialclock (CKOmn) and serial data (SOmn).
Setting the SOm register

Set the SOEmn bit to 1 and enable data output of the target channel.
Changing setting of the SOEm register

Enable data output and clock output of the target channel by setting a port register and a port mode register.
Setting port

Set the SSmn bit of the target channel to 1 and set the SEmn bit to 1 (to enable operation).
Writing to the SSm register

Set transmit data to the SIOp register (bits 7 to 0 of the SDRmn register) and start communication.
Starting communication


Register setting
Figure 12-77. Example of Contents of Registers for UART Transmission of UART (UART0 to UART2) (1/2)
(a) Serial mode register mn (SMRmn)
(b) Serial communication operation setting register mn (SCRmn)
(c) Serial data register mn (SDRmn) (lower 8 bits: TXDq)
(d) Serial output level register m (SOLm) � Sets only the bits of the target channel.
(e) Serial output register m (SOm) � Sets only the bits of the target channel.
(f) Serial output enable register m (SOEm) � Sets only the bits of the target channel to 1.
(g) Serial channel start register m (SSm) � Sets only the bits of the target channel to 1.
*/

  SAU0EN = 1;                    // Enables the SAU0 Module. Supply clock   from the CPU clock
  NOP();                        // Idle time to hardware response (4 instructions).
  NOP();                         // Idle time to hardware response (4 instructions).
  NOP();                         // Idle time to hardware response (4 instructions).
  NOP();                         // Idle time to hardware response (4 instructions).

  SPS0 = 0b0000000000000001;     // Serial clock select register to select two types of operation clocks (CKm0, CKm1) that are
  /*       ||||||||||||||||      // commonly supplied to each channel. CKm1 is selected by bits 7 to 4 of the SPSm register , and CKm0 is selected
           ||||||||||||||||      // by bits 3 to 0.
           ||||||||||||||||_____________________ PRSm00   See description  below.--
           |||||||||||||||______________________ PRSm01   See description  below.  \  fCLK / 4 for Channel 0, TX
           ||||||||||||||_______________________ PRSm02   See description  below.  /
           |||||||||||||________________________ PRSm03   See description  below.--
           ||||||||||||_________________________ PRSm10   See description  below.--
           |||||||||||__________________________ PRSm11   See description  below.  \  fCLK / 4 for Channel 1, RX
           ||||||||||___________________________ PRSm12   See description  below.  /
           |||||||||____________________________ PRSm13   See description  below.--
           ||||||||_____________________________ Bits 15 - 8 Unused. ** When writing to SPS be sure to clear bits 15 to 8 to �0�. 
            PRS PRS PRS PRS
            mk3 mk2 mk1 mk0               fCLK = 2 MHz   fCLK = 5 MHz   fCLK = 10 MHz   fCLK = 20 MHz   fCLK = 32 MHz 
             0   0   0   0    fCLK           2 MHz           5 MHz           10 MHz          20 MHz           32 MHz
             0   0   0   1    fCLK/2         1 MHz           2.5 MHz         5 MHz           10 MHz           16 MHz
             0   0   1   0    fCLK/2^2       500 kHz         1.25 MHz        2.5 MHz         5 MHz            8 MHz
             0   0   1   1    fCLK/2^3       250 kHz         625 kHz         1.25 MHz        2.5 MHz          4 MHz
             0   1   0   0    fCLK/2^4       125 kHz         313 kHz         625 kHz         1.25 MHz         2 MHz
             0   1   0   1    fCLK/2^5       62.5 kHz        156 kHz         313 kHz         625 kHz          1 MHz
             0   1   1   0    fCLK/2^6       31.3 kHz        78.1 kHz        156 kHz         313 kHz          500 kHz
             0   1   1   1    fCLK/2^7       15.6 kHz        39.1 kHz        78.1 kHz        156 kHz          250 kHz
             1   0   0   0    fCLK/2^8       7.81 kHz        19.5 kHz        39.1 kHz        78.1 kHz         125 kHz
             1   0   0   1    fCLK/2^9       3.91 kHz        9.77 kHz        19.5 kHz        39.1 kHz         62.5 kHz
             1   0   1   0    fCLK/2^10      1.95 kHz        4.88 kHz        9.77 kHz        19.5 kHz         31.3 kHz
             1   0   1   1    fCLK/2^11      977 Hz          2.44 kHz        4.88 kHz        9.77 kHz         15.6 kHz
             1   1   0   0    fCLK/2^12      488 Hz          1.22 kHz        2.44 kHz        4.88 kHz         7.81 kHz
             1   1   0   1    fCLK/2^13      244 Hz          610 Hz          1.22 kHz        2.44 kHz         3.91 kHz
             1   1   1   0    fCLK/2^14      122 Hz          305 Hz          610 Hz          1.22 kHz         1.95 kHz
             1   1   1   1    fCLK/2^15      61 Hz           153 kHz         305 Hz          610 Hz           977 Hz	     
                
  */
  SR_ConfigUart1Tx();
  SR_ConfigUart1Rx();
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
************************************************************************/
void SR_ConfigUart1Tx(void)
{
  ST0 = ST0 | 0b0000000000000100;         // Serial channel stop register
  /*            ||||||||||||||||_______   ST00   Bit to disable UART 0 Ch 0 (TX)
                |||||||||||||||________   ST01   Bit to disable UART 0 Ch 1 (RX)
                ||||||||||||||_________   ST10   Bit to disable UART 1 Ch 2 (TX)
                |||||||||||||__________   ST11   Bit to disable UART 1 Ch 3 (RX)
                ||||||||||||___________   Bits 15-4 Set/Read as 0.
  */          
  STMK1  = 1;                          // Disable INTST1 (UART1 TX) 
  STIF1  = 0;                          // Clear INTST1 (UART1 TX) interrupt flag 
  STPR11 = 1;                          // Set INTST1(UART1 TX) low priority
  STPR01 = 1;                          // Set INTST1(UART1 TX) low priority 

  SMR02  = 0b0000000000100010;         // Serial mode register Tx
  /*         ||||||||||||||||_______   MDmn0 Selection of interrupt source of channel n
             |||||||||||||||           0 Transfer end interrupt  <----------
             |||||||||||||||           1 Buffer empty interrupt
             |||||||||||||||________   MDmn2 (Bit 2) MDmn1 (bit 1)  Setting of operation mode of channel n              
             |||||||||||||               0             0                 CSI mode
             |||||||||||||               0             1                 UART mode      <-----------------
             |||||||||||||               1             0                 Simplified I2C mode
             |||||||||||||               1             1                 Setting prohibited
             |||||||||||||__________   Bits 4 - 3 unused defined as 0
             |||||||||||____________   Bit 5 unused. Defined as 1
             ||||||||||_____________   SISmn0 Controls inversion of level of receive data of channel n in UART mode
             |||||||||                 0 Falling edge is detected as the start bit.The input communication data is captured as is.  <-----------------
             |||||||||                 1 Rising edge is detected as the start bit.The input communication data is inverted and captured.
             |||||||||______________   Bit 7 unused. Defined as 0
             ||||||||_______________   STSmn Selection of start trigger source
             |||||||                   0 Only software trigger is valid (selected for CSI, UART transmission, and simplified I2C).<------------------
             |||||||                   1 Valid edge of the RXDq pin (selected for UART reception)
             |||||||________________   Bit 13-9 unused defined as 0
             ||_____________________   CCSmn Selection of transfer clock (fTCLK) of channel n
             |                         0 Divided operation clock fMCK specified by the CKSmn bit    <------------------
             |                         1 Clock input fSCK from the SCKp pin (slave transfer in CSI mode)
             |______________________   CKSmn Selection of operation clock (fMCK) of channel n
                                       0 Operation clock CKm0 set by the SPSm register  <-------------------------
                                       1 Operation clock CKm1 set by the SPSm register
  */              

  SCR02  = 0b1000000010010111;         // Serial control register
  /*         ||||||||||||||||_______   DLSmn1(Bit 1) DLSmn0 (bit 0)  Setting of data length in CSI and UART modes
             ||||||||||||||              0             0                 Unused
             ||||||||||||||              0             1                 9-bit data length (stored in bits 0 to 8 of the SDRmn register) (settable in UART mode only)
             ||||||||||||||              1             0                 7-bit data length (stored in bits 0 to 6 of the SDRmn register)
             ||||||||||||||              1             1                 8-bit data length (stored in bits 0 to 7 of the SDRmn register)<----------------------
             ||||||||||||||_________   Bit 2 unused. Defined as 1
             |||||||||||||__________   Bit 3 unused. Defined as 0
             ||||||||||||___________   SLCmn1(Bit 5) SLCmn0 (bit 4)  Setting of stop bit in UART mode
             ||||||||||                  0             0                 No stop bit
             ||||||||||                  0             1                 Stop bit length = 1 bit <--------------------------------
             ||||||||||                  1             0                 Stop bit length = 2 bits (mn = 00, 02, 10, 12 only)
             ||||||||||                  1             1                 Setting prohibited
             ||||||||||_____________   Bit 6 unused. Defined as 0
             |||||||||______________   DIRmn0 Selection of data transfer sequence in CSI and UART modes
             ||||||||                  0 Inputs/outputs data with MSB first.
             ||||||||                  1 Inputs/outputs data with LSB first. <------------------------
             ||||||||_______________   PTCmn1(Bit 9) PTCmn0 (bit 8)  Setting of parity bit in UART mode
             ||||||                      0             0                 Does not output the parity bit. /  Receives without parity   <----------------
             ||||||                      0             1                 Outputs 0 parity                /  No parity judgment
             ||||||                      1             0                 Outputs even parity.            / Judged as even parity.
             ||||||                      1             1                 Outputs odd parity.             / Judges as odd parity.
             ||||||_________________   EOCmn0 Selection of masking of error interrupt signal (INTSREx (x = 0 to 3))
             |||||                     0 Masks error interrupt INTSREx (INTSRx is not masked). <-------------------------
             |||||                     1 Enables generation of error interrupt INTSREx (INTSRx is masked if an error occurs).
             |||||__________________   Bit 11 unused. Defined as 0
             ||||___________________   DAPmn (Bit 13) CKPmn0 (bit 12)  Selection of data and clock phase in CSI mode
             ||                          0             0                 Type 1. See User Manual Pag. 549 
             ||                          0             1                 Type 2. See User Manual Pag. 549 
             ||                          1             0                 Type 3. See User Manual Pag. 549 
             ||                          1             1                 Type 4. See User Manual Pag. 549 
             ||_____________________   TXEmn (Bit 15) RXEmn0 (bit 14)  Setting of operation mode of channel n
                                         0             0                 Disable communication.
                                         0             1                 Reception only 
                                         1             0                 Transmission only   <-------------------
                                         1             1                 Transmission/reception    
  */              

  SDR02  = 0b0110011000000000;         // Serial data register
  /*         ||||||||||||||||_______   Bits 8-0 (9 bits) transmit/receive data register
             |||||||________________   Higher 7 bits of the serial data register are the division ratio of the operation clock
                                       SDRmn[15:9] Transfer clock setting by dividing the operating clock (fMCK) fMCK = fCLK / 2^4
                                       0 0 0 0 0 0 0 fMCK/2, fSCK/(2 * (0 + 1) (in CSI slave)
                                       0 0 0 0 0 0 1 fMCK/4, fSCK/(2 * (1 + 1)
                                       0 0 0 0 0 1 0 fMCK/6, fSCK/(2 * (2 + 1)
                                       0 0 0 0 0 1 1 fMCK/8, fSCK/(2 * (3 + 1)
                                       ------------  -----   Continue the sequence
                                       0 1 1 0 0 1 1 fMCK/104, fSCK/(2 * (51 + 1)  <------------------- 2MHz/19200 = 104 => SDR = (104 / 2) - 1 = 51
                                       1 1 0 0 1 1 1 fMCK/208, fSCK/(2 * (103 + 1)
                                       1 1 1 1 1 1 0 fMCK/254, fSCK/(2 * (126 + 1)
                                       1 1 1 1 1 1 1 fMCK/256, fSCK/(2 * (127 + 1)
  */   

  SO0 = SO0 | 0b0000000000000100;
  //                         |___ 1 Sets the SE02 bit to 1 and enters the communication wait status
  
  
  SOL0 = SOL0 | 0b0000000000000000;         // Serial output level register
  /*              ||||||||||||||||_______  SOL00 Bit 0 Selects inversion of the level of the transmit data of channel n in UART mode
                  |||||||||||||||          0 Communication data is output as is.<--------------
                  |||||||||||||||          1 Communication data is inverted and output.
                  |||||||||||||||________  Bit 1 not used. By default 0.
                  ||||||||||||||_________  SOL02 Bit 2 Selects inversion of the level of the transmit data of channel n in UART mode
                  ||||                     0 Communication data is output as is.<--------------
                  ||||                     1 Communication data is inverted and output.                    
                  ||||___________________  Bits 15-3 Not used. Read as 0
  */
  
  SOE0 = SOE0 | 0b0000000000000100;
  //                           |___ 1 Enables channel 2 output by serial communication operation.
  
  // Set TxD1 pin       // TX en pin P02 SOLO PARA TARJETA DE DESARROLLO!!!
  //PMC0 = PMC0 & 0b11111110; // P02 as digital input
  P0 = P0 | 0b00000001; // Initialize the P0.3 bit TXD1
  //PM0  = PM0 & 0b11111110;  // P02 as Output
  
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
************************************************************************/
void SR_ConfigUart1Rx(void)
{
  ST0 = ST0 | 0b0000000000001000;         // Serial channel stop register
  /*            ||||||||||||||||_______   ST00   Bit to disable UART 0 Ch 0 (TX)
                |||||||||||||||________   ST01   Bit to disable UART 0 Ch 1 (RX)
                ||||||||||||||_________   ST10   Bit to disable UART 1 Ch 2 (TX)
                |||||||||||||__________   ST11   Bit to disable UART 1 Ch 3 (RX)
                ||||||||||||___________   Bits 15-4 Set/Read as 0.
  */          
  SRMK1  = 1;                          // Disable INTSR1 (UART1 RX) 
  SRIF1  = 0;                          // Clear INTSR1 (UART1 RX) interrupt flag 
  SRPR01 = 1;                          // Set INTSR1(UART1 RX) low priority 
  SRPR11 = 1;                          // Set INTST1(UART1 RX) low priority

  SIR03  = 0b0000000000000111;                // Serial flag clear trigger register
  /*         ||||||||||||||||_______  OVCTmn Bit 0 Clear trigger of overrun error flag of channel n
             |||||||||||||||          0 Not cleared
             |||||||||||||||          1 Clears the OVFmn bit of the SSRmn register to 0.   <---------------
             |||||||||||||||________  PECT mn Bit 1 Clear trigger of parity error flag of channel n
             ||||||||||||||           0 Not cleared
             ||||||||||||||           1 Clears the OVFmn bit of the SSRmn register to 0.  <-----------------
             ||||||||||||||_________  FECT mn Bit 2 Clear trigger of framing error of channel n
             |||||||||||||            0 Not cleared
             |||||||||||||            1 Clears the OVFmn bit of the SSRmn register to 0.   <---------------
             ||||||||||||___________  Bits 15 - 3 Not used. Defined as 0.
   */
  NFEN0 = NFEN0 | 0b00000100;                // Noise filter enable register 0
  /*                ||||||||_______________  Bit 0 SNFEN00
                    |||||||                  0 Noise filter C_OFF
                    |||||||                  1 Noise filter C_ON
                    |||||||________________  Bit 1 not used                  
                    ||||||_________________  Bit 2 SNFEN10
                    |||||                    0 Noise filter C_OFF
                    |||||                    1 Noise filter C_ON      <-----------------
                    |||||__________________  Bit 3 not used               
                    ||||___________________  Bit 4 SNFEN20
                    |||                      0 Noise filter C_OFF
                    |||                      1 Noise filter C_ON
                    |||____________________  Bit 5 not used               
                    ||_____________________  Bit 6 SNFEN30
                    |                        0 Noise filter C_OFF
                    |                        1 Noise filter C_ON
                    |______________________  Bit 7 not used                              
  */
  SMR03  = 0b0000000100100010;         // Serial mode register
  /*         ||||||||||||||||_______   MDmn0 Selection of interrupt source of channel n
             |||||||||||||||           0 Transfer end interrupt  <----------
             |||||||||||||||           1 Buffer empty interrupt
             |||||||||||||||________   MDmn2 (Bit 2) MDmn1 (bit 1)  Setting of operation mode of channel n              
             |||||||||||||               0             0                 CSI mode
             |||||||||||||               0             1                 UART mode      <-----------------
             |||||||||||||               1             0                 Simplified I2C mode
             |||||||||||||               1             1                 Setting prohibited
             |||||||||||||__________   Bits 4 - 3 unused defined as 0
             |||||||||||____________   Bit 5 unused. Defined as 1
             ||||||||||_____________   SISmn0 Controls inversion of level of receive data of channel n in UART mode
             |||||||||                 0 Falling edge is detected as the start bit.The input communication data is captured as is.  <-----------------
             |||||||||                 1 Rising edge is detected as the start bit.The input communication data is inverted and captured.
             |||||||||______________   Bit 7 unused. Defined as 0
             ||||||||_______________   STSmn Selection of start trigger source
             |||||||                   0 Only software trigger is valid (selected for CSI, UART transmission, and simplified I2C).
             |||||||                   1 Valid edge of the RXDq pin (selected for UART reception)<------------------
             |||||||________________   Bit 13-9 unused defined as 0
             ||_____________________   CCSmn Selection of transfer clock (fTCLK) of channel n
             |                         0 Divided operation clock fMCK specified by the CKSmn bit    <------------------
             |                         1 Clock input fSCK from the SCKp pin (slave transfer in CSI mode)
             |______________________   CKSmn Selection of operation clock (fMCK) of channel n
                                       0 Operation clock CKm0 set by the SPSm register  <-------------------------
                                       1 Operation clock CKm1 set by the SPSm register
  */         
  SCR03  = 0b0100000010010111;         // Serial control register
  /*         ||||||||||||||||_______   DLSmn1(Bit 1) DLSmn0 (bit 0)  Setting of data length in CSI and UART modes
             ||||||||||||||              0             0                 Unused
             ||||||||||||||              0             1                 9-bit data length (stored in bits 0 to 8 of the SDRmn register) (settable in UART mode only)
             ||||||||||||||              1             0                 7-bit data length (stored in bits 0 to 6 of the SDRmn register)
             ||||||||||||||              1             1                 8-bit data length (stored in bits 0 to 7 of the SDRmn register)<----------------------
             ||||||||||||||_________   Bit 2 unused. Defined as 1
             |||||||||||||__________   Bit 3 unused. Defined as 0
             ||||||||||||___________   SLCmn1(Bit 5) SLCmn0 (bit 4)  Setting of stop bit in UART mode
             ||||||||||                  0             0                 No stop bit
             ||||||||||                  0             1                 Stop bit length = 1 bit <--------------------------------
             ||||||||||                  1             0                 Stop bit length = 2 bits (mn = 00, 02, 10, 12 only)
             ||||||||||                  1             1                 Setting prohibited
             ||||||||||_____________   Bit 6 unused. Defined as 0
             |||||||||______________   DIRmn0 Selection of data transfer sequence in CSI and UART modes
             ||||||||                  0 Inputs/outputs data with MSB first.
             ||||||||                  1 Inputs/outputs data with LSB first. <------------------------
             ||||||||_______________   PTCmn1(Bit 9) PTCmn0 (bit 8)  Setting of parity bit in UART mode
             ||||||                      0             0                 Does not output the parity bit. /  Receives without parity   <----------------
             ||||||                      0             1                 Outputs 0 parity                /  No parity judgment
             ||||||                      1             0                 Outputs even parity.            / Judged as even parity.
             ||||||                      1             1                 Outputs odd parity.             / Judges as odd parity.
             ||||||_________________   EOCmn0 Selection of masking of error interrupt signal (INTSREx (x = 0 to 3))
             |||||                     0 Masks error interrupt INTSREx (INTSRx is not masked). <-------------------------
             |||||                     1 Enables generation of error interrupt INTSREx (INTSRx is masked if an error occurs).
             |||||__________________   Bit 11 unused. Defined as 0
             ||||___________________   DAPmn (Bit 13) CKPmn0 (bit 12)  Selection of data and clock phase in CSI mode
             ||                          0             0                 Type 1. See User Manual Pag. 549 
             ||                          0             1                 Type 2. See User Manual Pag. 549 
             ||                          1             0                 Type 3. See User Manual Pag. 549 
             ||                          1             1                 Type 4. See User Manual Pag. 549 
             ||_____________________   TXEmn (Bit 15) RXEmn0 (bit 14)  Setting of operation mode of channel n
                                         0             0                 Disable communication.
                                         0             1                 Reception only <-------------------
                                         1             0                 Transmission only   
                                         1             1                 Transmission/reception    
  */              
  SDR03  = 0b0110011000000000;         // Serial data register
  /*         ||||||||||||||||_______   Bits 8-0 (9 bits) transmit/receive data register
             |||||||________________   Higher 7 bits of the serial data register are the division ratio of the operation clock
                                       SDRmn[15:9] Transfer clock setting by dividing the operating clock (fMCK)
                                       0 0 0 0 0 0 0 fMCK/2, fSCK/(2 * (0 + 1) (in CSI slave)
                                       0 0 0 0 0 0 1 fMCK/4, fSCK/(2 * (1 + 1)
                                       0 0 0 0 0 1 0 fMCK/6, fSCK/(2 * (2 + 1)
                                       0 0 0 0 0 1 1 fMCK/8, fSCK/(2 * (3 + 1)
                                       ------------  -----   Continue the sequence
                                       0 1 1 0 0 1 1 fMCK/104, fSCK/(2 * (51 + 1)  <------------------- 2MHz/19200 = 104 => SDR = (104 / 2) - 1 = 51
                                       1 1 0 0 1 1 1 fMCK/208, fSCK/(2 * (103 + 1)
                                       1 1 1 1 1 1 0 fMCK/254, fSCK/(2 * (126 + 1)
                                       1 1 1 1 1 1 1 fMCK/256, fSCK/(2 * (127 + 1)
  */   

  SOE0 = SOE0 & 0xFFF7;  /* disable UART1 output */

  // Set RxD1 pin       //RX en pin P03 SOLO PARA TARJETA DE DESARROLLO!!!
  //PMC0 = PMC0 & 0b1111101; // P03 as digital input
  PM0  = PM0 | 0b00000010;  // P03 as Input
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   Enable the Tx/Rx bus
************************************************************************/
void SR_EnableUart1Tx(void)
{
  STIF1 = 0U;	          // clear INTST0 interrupt flag
	STMK1 = 0U;	          // enable INTST0 interrupt
  SO0 = SO0 | 0x0004;   // output level normal
  SOE0 = SOE0 | 0x0004; // enable UART2 output
  SS0 = SS0 | 0x0004;         // enable UART2 output
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   Enable the Tx/Rx bus
************************************************************************/
void SR_EnableUart1Rx(void)
{
  SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
  SRMK1 = 0U;    /* enable INTSR1 interrupt */
  SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
  SREMK1 = 0U;   /* enable INTSRE1 interrupt */
  SS0 = SS0 | 0x0008;    /* enable UART1 receive */
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   Enable the Tx/Rx bus
************************************************************************/
void SR_DisableUart1Tx(void)
{
  ST0 = ST0 | 0x0004;   // disable UART1 transmit
  SOE0 = SOE0 & 0xFFFB; // disable UART1 output
  STMK1 = 1;            // disable INTST1 interrupt
  STIF1 = 0;            // clear INTST1 interrupt flag
}

/************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   Enable the Tx/Rx bus
************************************************************************/
void SR_DisableUart1Rx(void)
{
  ST0 = ST0 | 0x0008;    /* disable UART1 receive */
  SRMK1 = 1U;    /* disable INTSR1 interrupt */
  SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
  SREMK1 = 1U;   /* disable INTSRE1 interrupt */
  SREIF1 = 0U;   /* clear INTSRE1 interrupt flag */
}

/*****************************************************************************
 Name:          INTER_UART_Tx
 Parameters:    None
 Returns:       None
 Called by:     None
 Calls:         None
 Description:   Communication Reception interrupt
 
******************************************************************************/
#pragma interrupt INTER_UART1_Tx(vect=INTST1)
void INTER_UART1_Tx(void)
{
  u8TxByteCnt++;
  if(u8TxByteCnt < C_COMM_FRAME_SIZE)
    {
      TXD1 = au8BufferTx[u8TxByteCnt];
    }
  else
    {
      u8RxByteCnt = 0;
      u8RxFrameReceived = C_FALSE;
      SR_DisableUart1Tx();
      SR_EnableUart1Rx();
    }
}

/*****************************************************************************
 Name:          INTER_UART_Rx
 Parameters:    None
 Returns:       None
 Called by:     None
 Calls:         None
 Description:   Communication Reception interrupt
                Calculates the Checksum C_ON the fly
******************************************************************************/
#pragma interrupt INTER_UART1_Rx(vect=INTSR1)
void INTER_UART1_Rx(void)
{
  u8CommTimeout = (U8)C_20_ms;
  au8BufferRx[u8RxByteCnt] = (U8)RXD1;                               // Unload Reception Buffer into Reception Array
  u8RxByteCnt++;                                                              // Increments Reception pointer 
  
  if (u8RxByteCnt >= C_COMM_FRAME_SIZE)                                         // Has 6 Bytes of Reception been reached?
    {
      u8RxByteCnt = 0;
      u8RxFrameReceived = C_TRUE;
      u8EnableSlaveTx = C_TRUE;
    }
}