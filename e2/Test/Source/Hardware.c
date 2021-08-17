/***********************************************************************/
/*                                                                     */
/*  FILE        :Hardware.c                                            */
/*  DATE        :04/02/2014                                            */
/*  DESCRIPTION :Set the I/O direction and refresh the outputs         */
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
#include "Hardware.h"
#include "Display.h"
#include "CycleSelector.h"

/*****************************************************************************
 Name:          SR_PortConfig
 Parameters:    None
 Returns:       None
 Called by:     InitMCU.c -> SR_Init_mcu
 Calls:         None
 Description:   Set the I/O direction
******************************************************************************/
void SR_PortConfig(void)
{
  SR_InitPorts();
  
//  PMC0 = 0b11111100;
  PM0 = 0b11111110;
      /*        ||_ P_UART_TX
                |__ P_UART_RX
      */
  PM1 = 0b00000000;
      /*  ||||||||_ P_S2: Output
          |||||||__ P_S5: Output
          ||||||___ P_S4: Output
          |||||____ P_S3: Output
          ||||_____ P_S6: Output
          |||______ P_S1: Output
          ||_______ P_S7: Output
          |________ P_TEST_POINT1: Output
      */
  ADPC = 0b00000001;
  PM2 = 0b11110011;
      /*  ||||||||_ 
          |||||||__ 
          ||||||___ 
          |||||____ 
      */
  PM3 = 0b11111100;
      /*        ||_ P_S10: Output
                |__ : Output
      */
  PM5 = 0b11111100;
      /*        ||_ P_S9: Output
                |__ P_S8: Output
      */
  #ifdef C_EFX1870P001
  PM6 = 0b11110001;
      /*  ||||||||_ P_ROW_2: Input
          |||||||__ P_MUX_4: Output
          ||||||___ P_MUX_3: Output
          |||||____ P_MUX_1: Output
      */
  #endif
  
  #ifdef C_EFX2009P001
  PM6 = 0b11110000;
      /*  ||||||||_ P_ROW_2: Output
          |||||||__ P_MUX_4: Output
          ||||||___ P_MUX_3: Output
          |||||____ P_MUX_1: Output
      */
  #endif
  PM7 = 0b00111110;
      /*  ||||||||_ P_S11: Otuput
          |________ 
      */
  PMC12 = 0b11111110;
  PU12 = 0b11111111;
  PM12 = 0b11111110;
       /*  ||||||||_ : Output
           ||||||___ P_ROW_3: Input
           |||||____ P_ROW_4: Input
           ||||_____ P_ROW_1: Input
       */
//PM13 = 0b11111111;
      /*   |________ : Input
      */

  PMC14 = 0b01111111; // Disable P14.7 Analog input, enable P14.7 as Digital I/O
  PM14 = 0b01111111;
      /*   |________ P_MUX_2: Output
      */
}

/*****************************************************************************
 Name:          SR_InitPorts
 Parameters:    None
 Returns:       None
 Called by:     Hardware.c -> SR_PortConfig
 Calls:         None
 Description:   Initializes the ports
******************************************************************************/
void SR_InitPorts(void)
{
  P_UART_RX = C_OFF;
  P_UART_TX = C_ON;
  P_ROW_1 = C_OFF;
  P_ROW_2 = C_OFF;
  P_ROW_3 = C_OFF;
  P_ROW_4 = C_OFF;
  P_BUZZER = C_OFF;
  P_MUX_1 = C_OFF;
  P_MUX_2 = C_OFF;
  P_MUX_3 = C_OFF;
  P_MUX_4 = C_OFF;
  P_S1 = C_ON;
  P_S2 = C_ON;
  P_S3 = C_ON;
  P_S4 = C_ON;
  P_S5 = C_ON;
  P_S6 = C_ON;
  P_S7 = C_ON;
  P_S8 = C_ON;
  P_S9 = C_ON;
  P_S10 = C_ON;
  P_S11 = C_ON;
  P_TEST_POINT_1 = C_OFF;
}

/*****************************************************************************
 Name:          SR_HardwareRefresh
 Parameters:    None
 Returns:       None
 Called by:     main.c -> main
 Calls:         None
 Description:   Refresh output port
******************************************************************************/
void SR_HardwareRefresh(void)
{
  SR_GetCycle();
  SR_RefreshDisplay();
}
