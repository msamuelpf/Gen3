/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_TmrPwm07.c                                        */
/*  DATE        :22/10/2015                                            */
/*  DESCRIPTION :Configure timer to output a PWM signal to control the */
/*               volume of the buzzer                                  */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Kraken 24 User Interface                             */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Drv_TmrPwm07.h"

/*****************************************************************************
 Name:          SR_ConfigTmrPwm07
 Parameters:    none
 Returns:       none
 Called by:     Drv_Tmr0.c -> SR_InitTmr0
 Calls:         none
 Description:   Configures the timer pwm channel 4
******************************************************************************/
void SR_ConfigTmrPwm07(void)
{
  /* Mask channel 2 interrupt */
  TMMK02 = 1U;    /* disable INTTM02 interrupt */
  TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
  /* Mask channel 7 interrupt */
  TMMK07 = 1U;    /* disable INTTM07 interrupt */
  TMIF07 = 0U;    /* clear INTTM07 interrupt flag */

  /* Channel 0 used as interval timer */
  TMR02 = 0b0000100000000001;
          /*||||||||||||||||_ 
            |||||||||||||||   
            |||||||||||||||__ 
            ||||||||||||_____ 
            ||||||||||_______ 
            ||||||||_________ 
            |||||____________ 
            ||||_____________ 
            |||______________ 
            ||_______________ 
          */

    TDR02 = 0x063F;  // Initialize the TDR03 register to 0xFFFF, it will be change to the buzzer frequency
    TOM0 &= ~0x0004;
    TOL0 &= ~0x0004;
    TO0 &= ~0x0004;
    TOE0 &= ~0x0004;
    /* Channel 7 is used as slave channel for PWM output function */
    TMR07 = 0b0000010000001001;
          /*||||||||||||||||_ 
            |||||||||||||||   
            |||||||||||||||__ 
            ||||||||||||_____ 
            ||||||||||_______ 
            ||||||||_________ 
            |||||____________ 
            ||||_____________ 
            |||______________ 
            ||_______________ 
          */
    
    TDR07 = 0x04B0;
    TOM0 |= 0x0080;
    TOL0 &= ~0x0080;
    TO0 &= ~0x0080;
    TOE0 |= 0x0080;
    /* Set TO07 pin */
    P4 &= 0xFDU;
    PM4 &= 0xFDU;
}

/*****************************************************************************
 Name:          SR_EnableTmrInterrupt07
 Parameters:    None
 Returns:       none
 Called by:     Drv_Tmr0.c -> SR_EnableTmr0Functions
                Buzzer.c -> Buzzer
 Calls:         None
 Description:   enables timer interrupt 07
******************************************************************************/
void SR_EnableTmrInterrupt07(void)
{
    TOE0 = TOE0 | 0x0080; // Enable TO07
    TS0 = TS0 | 0x0004 | 0x0080; // Enables TS02 / TS07
}

/*****************************************************************************
 Name:          SR_DisableTmrInterrupt07
 Parameters:    None
 Returns:       none
 Called by:     Buzzer.c -> Buzzer
 Calls:         None
 Description:   disables timer interrupt 07
******************************************************************************/
void SR_DisableTmrInterrupt07(void)
{
    TT0 |= 0x0004 | 0x0080;
    TOE0 &= ~0x0080;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SRE_BuzzerDriverSetVolumeDutty(U16 lu16Percent)
{
  U32 lu32TmrCnt;
  
  if(lu16Percent > 100)
    {
      lu16Percent = 100;
    }
    
  lu32TmrCnt = ((U32)TDR02 * (U32)lu16Percent) / (U32)100;
  TDR07 = (U16)lu32TmrCnt;
}

