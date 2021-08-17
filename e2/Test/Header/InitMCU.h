/***********************************************************************/
/*                                                                     */
/*  FILE        :InitMCU.h                                             */
/*  DATE        :31/01/2014                                            */
/*  DESCRIPTION :Microcontroller Initialization                        */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyD                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_Init_mcu(void);
extern void SR_EnableHardware(void);

extern void SR_SetClk(void);
extern void SR_FlashChecksum(void);
extern void SR_EnableWDT(void);
