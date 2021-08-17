/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_TmrInterrupt00.h                                  */
/*  DATE        :05/02/2014                                            */
/*  DESCRIPTION :Configure timers and define functions & interrupts    */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_ConfigTmrInterrupt00(void);
extern void SR_EnableTmrInterrupt00(void);
extern void INTER_TickTmr(void);
