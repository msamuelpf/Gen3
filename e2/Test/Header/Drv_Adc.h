/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_Adc.h                                             */
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

extern void SR_InitADC(void);
extern void SR_EnableADC(void);
extern void SR_DisableADC(void);
extern U8 FN_u8GetADC(void);
