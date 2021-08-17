/***********************************************************************/
/*                                                                     */
/*  FILE        :CycleSelector.c                                       */
/*  DATE        :01/05/2014                                            */
/*  DESCRIPTION :Set fucntions to define the cycle set by the selector */
/*               knonb                                                 */
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
#include "CycleSelector.h"
#include "Drv_Adc.h"

#ifdef C_EFX1870P001
const U8 T_CycleKnobADC[] = { 12, 40, 69, 99, 128, 157, 186, 215, 242, 255 };
#endif

#ifdef C_EFX2009P001
const U8 T_CycleKnobADC[] = {  9, 30, 50, 69,  89, 108, 128, 147, 166, 186, 206, 226, 246, 255 };
#endif

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_GetCycle(void)
{
  U8 lu8CycleADC;
  U8 lu8Cycle;
  U8 lu8KnobPosAux;
  
  lu8CycleADC = FN_u8GetADC();  // Read the ADC signal from cycle knob
  u8CycleSelectorADC = lu8CycleADC;
  u8CycleTemp = FN_u8GetKnobPosition(lu8CycleADC, T_CycleKnobADC);  // Detects the cycle knob resistor interval
  
  if(u8CycleTemp != u8LastCycleTemp)
    {
      u8KnobFilterCnt = C_30_ms;
    }
  else
    {
      if(u8KnobFilterCnt > 0)
        {
          u8KnobFilterCnt--;
        }
      else
        {
          u8Cycle = u8CycleTemp;
          /*if(u8Cycle > 8)
            {
              u8Cycle = 0;
            }*/
        }
    }
  u8LastCycleTemp = u8CycleTemp;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
U8 FN_u8GetKnobPosition(U8 lu8ADC, U8 *T_ReferenceTable)
{
   U8 lu8Cnt;
   U8 lu8Setpoint;
  
  for(lu8Cnt = 0; lu8Cnt < 0xFF; lu8Cnt++)
    {
      lu8Setpoint = *(T_ReferenceTable + lu8Cnt);
      if( lu8ADC < lu8Setpoint)
        {
          break;
        }
    }
  return lu8Cnt;
}
