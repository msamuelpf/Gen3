/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_Adc.c                                             */
/*  DATE        :01/05/2014                                            */
/*  DESCRIPTION :Set the configuration and functions to operate ADC    */
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
#include "Drv_Adc.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_InitADC(void)
{
	ADCEN = 1U;   // supply AD clock
	ADM0 = 0x00;  // Clear ADM0 register
  ADMK = 1U;	  // disable INTAD interrupt
	ADIF = 0U;	  // clear INTAD interrupt flag
	PM2 = PM2 | 0x01U; // Set ANI0 pin as analog input
	ADM0 = 0b00101000;
      /*   ||||||||_ ADCE(voltage comparator operation control): 0 Stops A/D voltage comparator operation
           |||||||__ LV: 00 Normal mode 1
           |||||____ FR: 101  ADC clock clk/5
           ||_______ ADMD(channel selection mode): 0 Select mode
           |________ ADCS (A/D conversion operation control): 0 Stops conversion operation
      */
	ADM1 = 0b00000000;
      /*   ||||||||_ ADTRS (Selection of the hardware trigger signal): 00 End of timer channel 01 count
           ||||||___ 000
           |||______ ADSCM(conversion mode): 0 Sequential conversion mode
           ||_______ ADTMD: 00 Software trigger mode
      */
	ADM2 = 0b00000001;  //_00_AD_POSITIVE_VDD | _00_AD_NEGATIVE_VSS | _00_AD_AREA_MODE_1 | _00_AD_RESOLUTION_10BIT;
      /*   ||||||||_ ADTYP: 1 8-bit resolution
           |||||||__ 0
           ||||||___ AWC: 0 Do not use the SNOOZE mode function.
           |||||____ ADRCK (Checking the upper limit and lower limit conversion result values): The interrupt signal (INTAD) is 
           ||||            output when the ADLL register <= the ADCR register <= the ADUL register (AREA 1).
           ||||_____ 0
           |||______ ADREFM: 0 Supplied from VSS
           ||_______ ADREFP: 00 Supplied from VDD
      */
	ADUL = 0xFF;
	ADLL = 0x00;
	ADS = 0x00; // Set the Analog Input Channel ANI0
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_EnableADC(void)
{
  U8 lu8Cnt;
  lu8Cnt = 0;
  
  ADCE = 1U;	// Enable AD comparator
  while (lu8Cnt < 32) // stabilization wait time(about 1us)
    {
      lu8Cnt++;
    }
	ADCS = 1U;	// enable AD conversion
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_DisableADC(void)
{
	ADCS = 0U;	/* disable AD conversion */
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
U8 FN_u8GetADC(void)
{
  return (U8)ADCRH;  // Set the ADCRH register value to the pointer variable
}
