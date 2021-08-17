/***********************************************************************/
/*                                                                     */
/*  FILE        :Communications.h                                      */
/*  DATE        :13/05/2014                                            */
/*  DESCRIPTION :Set the functions to manage the comm protocol         */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

extern void SR_SerialComm(void);
extern void SR_SetFrame(void);
extern void SR_SetDisplayFrame(U8 lu8Command);
extern void SR_SetTestEquipmentFrame(U8 lu8Command);
extern void SR_CommandManager(void);
extern void SR_TestEquipmentCommandManager(void);
extern void SR_DisplayCommandManager(void);
extern void SR_SlaveDeviceManager(void);
extern void SR_CommLevelManager(void);
extern U8 FN_u8CalculateChecksum(U8 *lpu8ChecksumArray);
extern U8 FN_u8FrameReceivedStatus(U8 *lpuArrayReceived);
extern void SR_GetFrame(void);
extern void SR_GetDisplayFrame(U8 lu8CommandRx);
extern void SR_GetTestEquipmentFrame(U8 lu8CommandRx);