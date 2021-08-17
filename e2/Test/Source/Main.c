/***********************************************************************/
/*                                                                     */
/*  FILE        :main.c                                                */
/*  DATE        :31/01/2014                                            */
/*  DESCRIPTION :Main Process for Washer machine                       */
/*  CPU TYPE    :RL78G13 32K Flash, 4K Data Flash, 2K RAM  (R5F100AC)  */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "InitMCU.h"
#include "Hardware.h"
#include "Buzzer.h"
#include "Communications.h"
#include "Tablas.h"
#include "Drv_TmrPwm07.h"
#include "MainProcess.h"

void main(void)
{
  DI();
  SR_Init_mcu();
  EI();

  SR_InitRam();
  SR_EnableHardware();
  
  while(1)
  {
    //WDTE = 0xACU;     // restart watchdog timer
    // ******  Main Loop ***************
    if(bf_MainTickCompleted == C_TRUE)
      {
        bf_MainTickCompleted = C_FALSE;
        SR_SerialComm();
        SR_MProcess();
        
        if(u8BuzzerTickCnt > 0)
          {
            u8BuzzerTickCnt--;
          }
        else
          {
            u8BuzzerTickCnt = C_BUZZER_TICK;
            SR_BuzzerTest();
            SR_Buzzer();
          }
        SR_HardwareRefresh();
      }
      if(bf_GEATickCompleted == C_TRUE)
      {
	 
	     bf_GEATickCompleted = C_FALSE;
	      //  P_S2 = 0; //prueba
	       // P_MUX_1 = 1; //prueba
	 
      }
  }
}
