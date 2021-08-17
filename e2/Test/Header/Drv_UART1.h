/***********************************************************************/
/*                                                                     */
/*  FILE        :Drv_UART1.h                                           */
/*  DATE        :05/05/2014                                            */
/*  DESCRIPTION :Set the initialization, functions & interrupt for UART*/
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_InitUART1(void);
extern void SR_ConfigUart1Tx(void);
extern void SR_ConfigUart1Rx(void);
extern void SR_EnableUart1Tx(void);
extern void SR_EnableUart1Rx(void);
extern void SR_DisableUart1Tx(void);
extern void SR_DisableUart1Rx(void);
extern void INTER_UART1_Tx(void);
extern void INTER_UART1_Rx(void);
