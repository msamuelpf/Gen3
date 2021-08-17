/***********************************************************************/
/*                                                                     */
/*  FILE        :CycleSelector.h                                       */
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

extern void SR_GetCycle(void);
extern U8 FN_u8GetKnobPosition(U8 lu8ADC, U8 *T_ReferenceTable);