/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_TmrInterrupt03.h                                  */
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

extern void SR_ConfigTmrInterrupt03(void);
extern void SR_EnableTmrInterrupt03(void);
extern void SR_DisableTmrInterrupt03(void);
extern void SRE_BuzzerDriverSetToneFrequency(U16 lu16Freq);