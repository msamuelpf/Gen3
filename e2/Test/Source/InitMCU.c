/***********************************************************************/
/*                                                                     */
/*  FILE        :InitMCU.c                                             */
/*  DATE        :31/01/2014                                            */
/*  DESCRIPTION :Microcontroller Initialization                        */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyD                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "InitMCU.h"
#include "Drv_Tmr0.h"
#include "Hardware.h"
#include "Drv_Adc.h"
#include "Drv_UART1.h"


/*****************************************************************************
 Name:          SR_Init_mcu       
 Parameters:    None
 Returns:       None
 Called by:     main.c -> main
 Calls:         InitMCU.c -> SR_SetClk
                InitMCU.c -> SR_FlashChecksum
                InitMCU.c -> SR_EnableWDT
 Description:   Initializes MCU Hardware
                Selects Clock Speed
                Enables the Watch Dog Timer
******************************************************************************/
void SR_Init_mcu(void)
{
  DI();
  SR_PortConfig();
  SR_SetClk();
  SR_InitTmr0();
  SR_InitADC();
  SR_InitUART1();
  SR_FlashChecksum();
}

/*****************************************************************************
 Name:          SR_Init_mcu       
 Parameters:    None
 Returns:       None
 Called by:     main.c -> main
 Calls:         InitMCU.c -> SR_SetClk
                InitMCU.c -> SR_FlashChecksum
                InitMCU.c -> SR_EnableWDT
 Description:   Initializes MCU Hardware
                Selects Clock Speed
                Enables the Watch Dog Timer
******************************************************************************/
void SR_EnableHardware(void)
{
  SR_EnableWDT();
  SR_EnableTmr0Functions();
  SR_EnableADC();
  SR_EnableUart1Rx();
}

/*****************************************************************************
 Name:          SR_FlashChecksum
 Parameters:    None
 Returns:       None
 Called by:     InitMCU.c -> SR_Init_mcu
 Calls:         None
 Description:   Determine the Program Flash Checksum
*****************************************************************************/
void SR_FlashChecksum(void)
{
/*    const U8 * lpu8FlashAdd;
    u16FlashChecksum = 0;
    lpu8FlashAdd = (const U8 *)0x0080;

    do
      {
        u16FlashChecksum = (U16) (u16FlashChecksum + *lpu8FlashAdd);
      }
    while ( ++lpu8FlashAdd <= (const U8 *)0xFFFE );
*/
}

/*****************************************************************************
 Name:          SR_FlashChecksum
 Parameters:    None
 Returns:       None
 Called by:     InitMCU.c -> SR_Init_mcu
 Calls:         None
 Description:   Select clock speed
*****************************************************************************/
void SR_SetClk(void)
{
    PIOR = 0x00U; // Peripheral I/O redirection register. Set as default configuration

    /*----------------------------------------------------------------------------*/
    /*                      Start Main Clock                                      */
    /*----------------------------------------------------------------------------*/
    CMC = 0b00000001; // Clock operation mode control register
        /*  ||||||||__ AMPH Control of X1 clock oscillation frequency
            |||||||     0: 1 MHz = fX = 10 MHz
            |||||||     1: 10 MHz < fX = 20 MHz
            |||||||___ AMPHS1 - AMPHS0 XT1 oscillator oscillation mode selection Note
            |||||       0 0: Low power consumption oscillation (default) Oscillation margin: Medium
            |||||       0 1: Normal oscillation Oscillation margin: high
            |||||       1 0: Ultra-low power consumption oscillation Oscillation margin: Low
            |||||       1 1: Setting prohibited
            |||||_____ NA
            ||||______ EXCLKS - OSCSELS Subsystem clock pin operation mode XT1/P123 pin XT2/EXCLKS/P124 pin
            ||          0 0: Input port mode Input port
            ||          0 1: XT1 oscillation mode Crystal/ceramic resonator connection
            ||          1 0: Input port mode Input port
            ||          1 1: External clock input mode Input port External clock input
            ||________ EXCLK - OSCSEL High-speed system clock pin operation mode X1/P121 pin X2/EXCLK/P122 pin
                        0 0: Input port mode Input port
                        0 1: X1 oscillation mode Crystal/ceramic resonator connection
                        1 0: Input port mode Input port
                        1 1: External clock input mode Input port External clock input
            Note As the XT oscillator becomes oscillation
            1. The CMC register can be written only once after reset release, by an 8-bit memory manipulation instruction. When the 
            CMC register is used at the default value (00H), be sure to set 00H to this register after reset release in order to 
            prevent malfunctioning during a program loop.
            2. After reset release, set the CMC register before X1 or XT1 oscillation is started as set by the clock operation 
            status control register (CSC).
            3. Be sure to set the AMPH bit to 1 if the X1 clock oscillation frequency exceeds 10 MHz.
            4. The XT1 oscillator is a circuit with low amplification in order to achieve low-power consumption.
        */
            
    OSTS = 0b00000000;  // Oscillation stabilization time select register
        /*   ||||||||__ oscillation stabilization time set as 12.8us
             |||||_____ N/A (0)
        */
            
    CSC = 0b11000000; // Clock operation status control register
        /*  ||||||||__ HIOSTOP High-speed C_ON-chip oscillator clock operation control
            ||          0 High-speed C_ON-chip oscillator operating
            ||          1 High-speed C_ON-chip oscillator stopped
            ||________ XTSTOP: Subsystem clock operation control
            |           0 XT1 oscillator operating / External clock from EXCLKS pin is valid / Input pin
            |           1 XT1 oscillator stopped / External clock from EXCLKS pin is invalid / Input pin
            |_________ MSTOP: High-speed system clock operation control
                        0 XT1 oscillator operating / External clock from EXCLKS pin is valid / Input pin
                        1 XT1 oscillator stopped / External clock from EXCLKS pin is invalid / Input pin
            1. After reset release, set the clock operation mode control register (CMC) before setting the CSC register.
            2. Set the oscillation stabilization time select register (OSTS) before setting the MSTOP bit to 0 after releasing 
            reset. Note that if the OSTS register is being used with its default settings, the OSTS register is not required to be 
            set here.
            3. To start X1 oscillation as set by the MSTOP bit, check the oscillation stabilization time of the X1 clock by using 
            the oscillation stabilization time counter status register (OSTC).
            4. When starting XT1 oscillation by setting the XSTOP bit, wait for oscillation of the subsystem clock to stabilize by 
            setting a wait time using software.
            5. Do not stop the clock selected for the CPU peripheral Hardware clock (fCLK) with the OSC register.
            6. The setting of the flags of the register to stop clock oscillation (invalidate the external clock input) and the 
            condition before clock oscillation is to be stopped are as Table 5-2.
    */
    
    CKC = 0b00000000; // System clock control register
        /*  ||||||||__ NA
            ||||______ MCM0: Main system clock (fMAIN) operation control
            |||         0 Selects the high-speed C_ON-chip oscillator clock (fIH) as the main system clock (fMAIN)
            |||         1 Selects the high-speed system clock (fMX) as the main system clock (fMAIN)
            |||_______ MCS: Status of Main system clock (fMAIN)
            ||          0 High-speed C_ON-chip oscillator clock (fIH)
            ||          1 High-speed system clock (fMX)
            ||________ CSS: Selection of CPU/peripheral Hardware clock (fCLK)
            ||          0 Main system clock (fMAIN)
            ||          1 Subsystem clock (fSUB)
            |_________ CLS: Status of CPU/peripheral Hardware clock (fCLK)
                        0 Main system clock (fMAIN)
                        1 Subsystem clock (fSUB)
        */
        
    OSMC = 0b00010000;  // Subsystem clock supply mode control register
          /* ||||||||__ NA
             ||||______ WUTMMCK0 Selection of operation clock for real-time clock, 12-bit interval timer, and timer RJ
             |||        0 The subsystem clock is selected as the operation clock for the real-time clock and the 12-bit interval 
             |||        timer.
             |||        The low-speed C_ON-chip oscillator cannot be selected as the count source for timer RJ.
             |||        1 The low-speed C_ON-chip oscillator clock is selected as the operation clock for the real-time clock and the 
             |||        12-bit interval timer.
             |||          Either the low-speed C_ON-chip oscillator or the subsystem clock can be selected as the count source for 
             |||        timer RJ.
             |||_______ NA
             |_________ RTCLPC Setting in STOP mode or HALT mode while subsystem clock is selected as CPU clock
                        0 Enables supply of subsystem clock to peripheral functions
                        1 Stops supply of subsystem clock to peripheral functions other than real-time clock and 12-bit interval 
                        timer.
          */
    OSTC = 0b00000000;  // Oscillation stabilization time counter status register
          // ||||||||__ Status of the time counter register, set as 12.8us

    PER0 = 0b00101111; // Peripheral enable register 0
          /* ||||||||__ TAU0EN Control of timer array unit 0 input clock supply
             |||||||     0 Stops input clock supply. SFR used by timer array unit 0 cannot be written. Timer array unit 0 is in the 
             |||||||     reset status.
             |||||||     1 Enables input clock supply. SFR used by timer array unit 0 can be read and written.
             |||||||___ TAU1EN Note Control of timer array unit 1 input clock supply
             ||||||      0 Stops input clock supply.SFR used by timer array unit 1 cannot be written. Timer array unit 1 is in the 
             ||||||     reset status.
             ||||||      1 Enables input clock supply. SFR used by timer array unit 1 can be read and written.
             ||||||____ SAU0EN Control of serial array unit 0 input clock supply
             |||||       0 Stops input clock supply. SFR used by the serial array unit 0 cannot be written. The serial array unit 0   
             |||||      is in the reset status.
             |||||       1 Enables input clock supply. SFR used by the serial array unit 0 can be read and written.
             |||||_____ SAU1EN Control of serial array unit 1 input clock supply
             ||||        0 Stops input clock supply. SFR used by the serial array unit 1 cannot be written. The serial array unit 1 
             ||||       is in the reset status.
             ||||        1 Enables input clock supply. SFR used by the serial array unit 1 can be read and written.
             ||||______ IICA0EN Control of serial interface IICA0 input clock supply
             |||         0 Stops input clock supply. SFR used by the serial interface IICA0 cannot be written. The serial interface 
             |||         IICA0 is in the reset status.
             |||         1 Enables input clock supply. SFR used by the serial interface IICA0 can be read and written.
             |||_______ ADCEN Control of A/D converter input clock supply
             ||          0 Stops input clock supply. SFR used by the A/D converter cannot be written. The A/D converter is in the 
             ||          reset status.
             ||          1 Enables input clock supply. SFR used by the A/D converter can be read and written.
             ||________ IICA1EN Note Control of serial interface IICA1 input clock supply
             |           0 Stops input clock supply. SFR used by the serial interface IICA1 cannot be written. The serial interface 
             |          IICA1 is in the reset status.
             |           1 Enables input clock supply. SFR used by the serial interface IICA1 can be read and written.
             |_________ RTCEN Control of supplying input clock Note 2 for real-time clock (RTC) and 12-bit interval timer
                         0 Stops input clock supply.SFR used by the real-time clock (RTC) and 12-bit interval timer cannot be 
                            written. The real-time clock (RTC) and 12-bit interval timer are in the reset status.
                         1 Enables input clock supply. SFR used by the real-time clock (RTC) and 12-bit interval timer can be read 
                         and written.
          */

    HOCODIV = 0b00000011; // High-speed C_ON-chip oscillator frequency select register
             // ||||||||___ Set at 32MHz
}
/*****************************************************************************
 Name:          SR_FlashChecksum
 Parameters:    None
 Returns:       None
 Called by:     InitMCU.c -> SR_Init_mcu
 Calls:         None
 Description:   Enables the WDT
*****************************************************************************/
void SR_EnableWDT(void)
{
    WDTIMK = 1U;    // disable INTWDTI interrupt 
    WDTIIF = 0U;    // clear INTWDTI interrupt flag 

    WDTIPR1 = 1U;   // Set INTWDTI low priority
    WDTIPR0 = 1U;

    WDTIMK = 0U;    // enable INTWDTI interrupt
}
