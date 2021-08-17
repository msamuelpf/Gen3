/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_TmrPwm07.h                                        */
/*  DATE        :22/10/2015                                            */
/*  DESCRIPTION :Configure timer to output a PWM signal to control the */
/*               volume of the buzzer                                  */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Kraken 24 User Interface                             */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_ConfigTmrPwm07(void);
extern void SR_EnableTmrInterrupt07(void);
extern void SR_DisableTmrInterrupt07(void);
extern void SRE_BuzzerDriverSetVolumeDutty(U16 lu16Percent);
