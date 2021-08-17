/***********************************************************************/
/*                                                                     */
/*  FILE        :Hardware.h                                            */
/*  DATE        :04/02/2014                                            */
/*  DESCRIPTION :Set the I/O direction and refresh the outputs         */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_PortConfig(void);
extern void SR_InitPorts(void);
extern void SR_HardwareRefresh(void);
