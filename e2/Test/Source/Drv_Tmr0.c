/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_Tmr0.c                                            */
/*  DATE        :24/02/2014                                            */
/*  DESCRIPTION :Configure timer modes, functions & interrupts         */
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
#include "Drv_Tmr0.h"
#include "Drv_TmrInterrupt00.h"
#include "Drv_TmrInterrupt03.h"
#include "Drv_TmrPwm07.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_InitTmr0(void)
{
  TAU0EN = 1U;    /* supplies input clock */
  
  // Configure Timer0 Clock
  TPS0 = 0b0000000001100000;
         /*||||||||||||||||__PRS00: 000 - fclk     --> 32MHz
           ||||||||||||______PRS01: 000 - fclk     --> 32MHz
           ||||||||__________PRS02: 00 - fclk/2   --> 16MHz
           ||||||____________N/A (00)
           ||||______________PRS03: 00 - fclk/256 --> 125kHz
           ||________________N/A (00)
         */
    /* Stop all channels */
  
  /* Stop all channels */
    TT0 = 0b0000101011111111;
          /*||||||||||||||||__0 No trigger operation
            ||||||||          1 TEmn bit is cleared to 0 and the count operation is stopped.
            ||||||||          This bit is the trigger to stop operation of the lower 8-bit timer for TTm1 and TTm3 when channel 1 
            ||||||||          or 3 is in the 8-bit timer mode.
            ||||||||__________N/A (0)
            |||||||___________0 No trigger operation
            ||||||            1 TEHm1 bit is cleared to 0 and the count operation is stopped.
            ||||||____________N/A (0)
            |||||_____________0 No trigger operation
            ||||              1 TEHm1 bit is cleared to 0 and the count operation is stopped.
            ||||______________N/A (0000)
          */

  SR_ConfigTmrInterrupt00();
  SR_ConfigTmrInterrupt03();
  SR_ConfigTmrPwm07();
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_EnableTmr0Functions(void)
{
  SR_EnableTmrInterrupt00();
  SR_EnableTmrInterrupt03(); //Se deshabilita para evitar Beep al energizar
  SR_EnableTmrInterrupt07();
}