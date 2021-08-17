/***********************************************************************/
/*                                                                     */
/*  FILE        :buzzer.h                                              */
/*  DATE        :24/03/2014                                            */
/*  DESCRIPTION :Set the buzzer structures and functions               */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern const U16 T_U16PWM_REG [];
extern void SR_Buzzer(void);
extern void SR_PlayMusic(U8 lu8Music);
extern void SR_BuzzerTest(void);
extern void SR_ConvertToneRecivedToTable(U8 *lpu8ToneReceived);