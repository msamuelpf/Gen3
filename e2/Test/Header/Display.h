/***********************************************************************/
/*                                                                     */
/*  FILE        :Display.c                                             */
/*  DATE        :21/05/2014                                            */
/*  DESCRIPTION :Functions to manage the user interface (LEDs & Buttons*/
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_RefreshDisplay(void);
extern U16 FN_u16DISPLAY_MUX_1(void);
extern U16 FN_u16DISPLAY_MUX_2(void);
extern U16 FN_u16DISPLAY_MUX_3(void);
extern U16 FN_u16DISPLAY_MUX_4(void);
extern void SR_ReadBtn(U8 lu8Mux);
extern void SR_DigitalBtnFilter(U8 lu8Input, struct stFilterBtnParameters *lpstFilterParam);
void SR_InitBtnFilter(struct stFilterBtnParameters *lpstFilterParam);
extern U16 FN_u16DISPLAY_MUX_1_Centauro(void);
extern U16 FN_u16DISPLAY_MUX_2_Centauro(void);
extern U16 FN_u16DISPLAY_MUX_3_Centauro(void);
extern U16 FN_u16DISPLAY_MUX_4_Centauro(void);
