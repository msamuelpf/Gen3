/***********************************************************************/
/*                                                                     */
/*  FILE        :MainProcess.c                                         */
/*  DATE        :09/06/2015                                            */
/*  DESCRIPTION :Set opeartion states to manage the user interface     */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

#include "RAM.h"
#include "MainProcess.h"
#include "Test.h"
#include "Buzzer.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_InitState(void)
{
  if(u8DeviceRqstID == C_MASTER_TO_DISPLAY)
    {
      EMainProcessSt = E_ST_OPERATION_MODE;
    }
  else if((u8TECmdRx == C_CMD_TEST_LOADS) && (u8FCTData1 == 0x00))
    {
      SR_PlayMusic(14);
      EMainProcessSt = E_ST_SUPPLIER_FCT;
    }
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_OperationMode(void)
{
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_MProcess(void)
{
  switch(EMainProcessSt)
    {
      case E_ST_INIT:
        SR_InitState();
        break;
      case E_ST_OPERATION_MODE:
        SR_OperationMode();
        break;
      case E_ST_SUPPLIER_FCT:
        SR_FCT_Test();
        break;
      case E_ST_UI_TEST_MODE:
        SR_UserInterfaceTest();
        break;
      case E_ST_ALT_TEST_MODE:
        SR_ALT_Test();
        break;
      default:
        EMainProcessSt = E_ST_INIT;
        break;
    }
}
