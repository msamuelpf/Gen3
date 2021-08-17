/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_TmrInterrupt03.c                                  */
/*  DATE        :26/03/2014                                            */
/*  DESCRIPTION :Configure timer to output buzzer frequency            */
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
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Drv_TmrInterrupt03.h"

/*****************************************************************************
 Name:          SR_ConfigTmrInterrupt03
 Parameters:    none
 Returns:       none
 Called by:     Drv_Tmr0.c -> SR_InitTmr0
 Calls:         none
 Description:   Configures the timer output 03
******************************************************************************/
void SR_ConfigTmrInterrupt03(void)
{
  /* Mask channel 3 interrupt */
  TMMK03 = 1U;    /* disable INTTM03 interrupt */
  TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
  /* Mask channel 3 higher 8 bits interrupt */
  TMMK03H = 1U;    /* disable INTTM03H interrupt */
  TMIF03H = 0U;    /* clear INTTM03H interrupt flag */  

  /* Channel 0 used as interval timer */
  TMR03 = 0b0000000000000000;
          /*||||||||||||||||_ MDmn0. 0 Timer interrupt is not generated when counting is started
            |||||||||||||||   (timer output does not change, either).
            |||||||||||||||__ MDmn1:3. Interval timer mode. Interval timer / Square wave output / Divider function / PWM output (master)
            ||||||||||||_____ N/A (00)
            ||||||||||_______ CISmn. 00 Falling edge
            ||||||||_________ STSmn. 000 Only software trigger start is valid (other trigger sources are unselected)
            |||||____________ SPLITmn. 0 Operates as 16-bit timer.
            ||||_____________ CCSmn. 0 Operation clock (fMCK) specified by the CKSmn0 and CKSmn1 bits 
            |||______________ N/A (0)
            ||_______________ CKSmn. 00 Operation clock CKm0 set by timer clock select register m (TPSm)
          */

    TDR03 = 0x0F9F;  /* Initialize the TDR03 register to 0xFFFF, it will be change to the buzzer frequency
                     */
    TOE0 = 0x0000U; // Disable TO
    
    // Set TO03 pin as output
    P3 = P3 & 0b11111101;
    PM3 = PM3 & 0b11111101;
    TOM0 = 0x0000U; // Master channel output mode (to produce toggle output by timer interrupt request signal (INTTMmn))
    TO0 = TO0 | 0x0008; // Enable TO03
    TOE0 = TOE0 | 0x0008; // Enable TO03
}

/*****************************************************************************
 Name:          SR_EnableTmrInterrupt03
 Parameters:    None
 Returns:       none
 Called by:     Drv_Tmr0.c -> SR_EnableTmr0Functions
                Buzzer.c -> Buzzer
 Calls:         None
 Description:   enables timer interrupt 03
******************************************************************************/
void SR_EnableTmrInterrupt03(void)
{
    TOE0 = TOE0 | 0x0008; // Enable TO03
    TS0 = TS0 | 0x0008; // Enables TS03
}

/*****************************************************************************
 Name:          SR_DisableTmrInterrupt03
 Parameters:    None
 Returns:       none
 Called by:     Buzzer.c -> Buzzer
 Calls:         None
 Description:   disables timer interrupt 03
******************************************************************************/
void SR_DisableTmrInterrupt03(void)
{
    TO0 = TO0 & 0xFFF7; // Disable TO03
    TOE0 = TOE0 & 0xFFF7; // Disable TO03
    TS0 = TS0 & 0xFFF7; // Disable TS00
}

/*****************************************************************************
 Name:          timer interrupt 03
 Parameters:    lu16Freq
 Returns:       none
 Called by:     Buzzer.c -> Buzzer
 Calls:         None
 Description:   Set the frequency defined by the buzzer tone
******************************************************************************/
void SRE_BuzzerDriverSetToneFrequency(U16 lu16Freq)
{
   TDR03 = lu16Freq;  // Set the frequency defined by the buzzer tone in the TDR03 register
}

