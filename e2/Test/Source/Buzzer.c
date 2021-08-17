/***********************************************************************/
/*                                                                     */
/*  FILE        :buzzer.c                                              */
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

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Buzzer.h"
#include "Drv_TmrInterrupt03.h"
#include "Drv_TmrPwm07.h"

struct stBuzzerParam
{
  U16 u16Tone;
  U16 u16Duration;
};

//Tabla para tonos a 32Mhz          
/* const U16 T_U16PWM_REG [] = 
  {         
  //C_SILENCE C_BEEP  C_C4    C_B4    C_A_4
      0x0000, 0x0F9F, 0x0776, 0x07E7, 0x0860,
      //C_A4  C_G_3   C_G3    C_F_3   C_F3
      0x08DF, 0x0966, 0x09F6, 0x0A8D, 0x0B2E,
      //C_E3  C_D_3   C_D3    C_C_3   C_C3
      0x0BD8, 0x0C8D, 0x0D4C, 0x0E16, 0x0EED,
      //C_B3  C_A_3   C_A3    C_G_2   C_G2
      0x0FD0, 0x10C1, 0x11C0, 0x12CE, 0x13ED,
      //C_F_2 C_F2    C_E2    C_D_2   C_D2
      0x151C, 0x165D, 0x17B2, 0x191B, 0x1A99,
      //C_C_2 C_C2    C_B2    C_A_2   C_A2
      0x1C2E, 0x1DDB, 0x1FA2, 0x2183, 0x2381,
      //C_G_1 C_G1    C_F_1   C_F1    C_E1
      0x259E, 0x27DB, 0x2A39, 0x2CBC, 0x2F65,
      //C_D_1 C_D1    C_C_1   C_C1    C_B1
      0x3237, 0x3533, 0x385D, 0x3BB8, 0x3F45,
      //C_A_1 C_A1
      0x4308, 0x4704,
  }; */
//Tabla para tonos a 4Mhz
const U16 T_U16PWM_REG [] = {					
	//C_SILENCE	C_BEEP	C_C4	C_B4	C_A_4
	0,	0x01F3,	0x0ED,	0x0FC,	0x010B,
	//C_A4	C_G_3	C_G3	C_F_3	C_F3
	0x011B,	0x012B,	0x013D,	0x0150,	0x0164,
	//C_E3	C_D_3	C_D3	C_C_3	C_C3
	0x017A,	0x0190,	0x01A8,	0x01C1,	0x01DC,
	//C_B3	C_A_3	C_A3	C_G_2	C_G2
	0x01F9,	0x0217,	0x0237,	0x0258,	0x027C,
	//C_F_2	C_F2	C_E2	C_D_2	C_D2
	0x02A2,	0x02CA,	0x02F5,	0x0322,	0x0352,
	//C_C_2	C_C2	C_B2	C_A_2	C_A2
	0x0384,	0x03BA,	0x03F3,	0x042F,	0x046F,
	//C_G_1	C_G1	C_F_1	C_F1	C_E1
	0x04B2,	0x04FA,	0x0546,	0x0596,	0x05EB,
	//C_D_1	C_D1	C_C_1	C_C1	C_B1
	0x0646,	0x06A5,	0x070A,	0x0776,	0x07E7,
	//C_A_1	C_A1			
	0x0860,	0x08DF,			
	};				


    //--------------------------------------------------------------------
    //
    //                     BUZZER TABLES
    //
    //--------------------------------------------------------------------
    const struct SBuzzerParam T_S_SOUND_TUNE[] =
       {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_C1,      7,     0, C_BUZZER_070ms,      13,     100,     80 },
          {       C_E1,      7,     0, C_BUZZER_070ms,      13,     100,     80 },
          {       C_G1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_F1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_E1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_D1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_C1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_130ms,       0,     100,     80 },
          {       C_G1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_C2,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_130ms,       0,     100,     80 }
       };

    const struct SBuzzerParam T_S_INTRO_TUNE[] =
       {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_C1,      7,     0, C_BUZZER_070ms,      13,     100,     80 },
          {       C_E1,      7,     0, C_BUZZER_070ms,      13,     100,     80 },
          {       C_G1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_F1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_E1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_D1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_C1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_130ms,       0,     100,     80 }
       };

    const struct SBuzzerParam T_S_END_TUNE[] =
       {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_C1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_130ms,       0,     100,     80 },
          {       C_G1,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_C2,      3,     0, C_BUZZER_050ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_130ms,       0,     100,     80 }
       };

    const struct SBuzzerParam T_S_BEEP[] =
       {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {     C_D_2,      4,     0, C_BUZZER_170ms,       5,     100,    100 },
          {C_END_MUSIC,      0,    0, C_BUZZER_130ms,       0,     100,     80 }
       };

    const struct SBuzzerParam T_S_DOUBLE_BEEP[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {      C_D_2,      4,     0, C_BUZZER_100ms,       5,     100,     80 },
          {      C_D_2,      4,     0, C_BUZZER_100ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_BEEP_LID[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {      C_C_2,      7,     0, C_BUZZER_200ms,       13,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };


    const struct SBuzzerParam T_S_DRINK_BEEP[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_G2,      0,     0, C_BUZZER_200ms,       0,     100,     80 },
          {       C_C2,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {       C_A3,      0,     0, C_BUZZER_200ms,       0,     100,     80 },
          {       C_F2,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {       C_E2,      0,     0, C_BUZZER_200ms,       0,     100,     80 },
          {       C_C2,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {       C_D2,      0,     0, C_BUZZER_200ms,       0,     100,     80 },
          {  C_SILENCE,      0,     0,C_BUZZER_1250ms,       0,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_LOCK_BEEP[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_A2,      7,     0, C_BUZZER_700ms,      13,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_DRINK_START[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_A2,      0,     0,C_BUZZER_1000ms,       0,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_COMM_FAIL[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_D2,      0,     0, C_BUZZER_100ms,       0,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_100ms,       0,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_ENDOFCYCLE[] =
       {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_C2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_E2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {       C_G2,      0,     0, C_BUZZER_230ms,       5,     100,     70 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };


    const struct SBuzzerParam T_S_END_DELAY[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {      C_D_1,      2,     0, C_BUZZER_150ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_150ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_150ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_150ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_130ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_130ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_130ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_130ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_100ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_100ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_100ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_100ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_080ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_080ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_080ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_080ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_050ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_050ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_050ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_050ms,       5,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_030ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_030ms,       5,     100,     80 },
          {      C_D_1,      2,     0, C_BUZZER_030ms,       5,     100,     80 },
          {      C_F_1,      2,     0, C_BUZZER_030ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
          };

    const struct SBuzzerParam T_S_WARNING_BEEP[] =     // ODS
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_F2,      0,     0, C_BUZZER_250ms,       5,     100,     60 },
          {       C_G2,      0,     0, C_BUZZER_100ms,       5,     100,     60 },
          {      C_C_1,      0,     0, C_BUZZER_200ms,       13,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_100ms,       0,     100,     80 },
          {      C_C_1,      0,     0, C_BUZZER_200ms,       13,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_100ms,       0,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,      0,     100,     80 }
      };

    const struct SBuzzerParam T_S_TECHNICIAN_TEST[] =    // ODS
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_C3,      0,     0, C_BUZZER_170ms,       13,     100,     80 },
          {      C_F_1,      0,     0, C_BUZZER_050ms,       13,     100,     80 },
          {       C_E3,      0,     0, C_BUZZER_200ms,       13,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_020ms,       0,     100,     80 },
          {      C_D_2,      0,     0, C_BUZZER_100ms,       5,     100,     80 },
         {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_WASHER_OFF[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_B2,      7,     0, C_BUZZER_120ms,       13,     100,     80 },
          {       C_B2,      7,     0, C_BUZZER_150ms,       13,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_200ms,       0,     100,     80 },
          {      C_G_1,      7,     0, C_BUZZER_270ms,       13,     100,     80 },
          {  C_SILENCE,      0,     0, C_BUZZER_300ms,       0,     100,     80 },
          {       C_E1,      7,     0, C_BUZZER_750ms,       17,    100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_CANCEL[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_F1,      7,     0, C_BUZZER_150ms,       13,     100,     80 },
          {       C_C1,      5,     0, C_BUZZER_450ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_END_OF_CYCLE[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_B1,      7,     0, C_BUZZER_050ms,      13,     100,     80 },
          {       C_B1,      7,     0, C_BUZZER_050ms,      13,     100,     80 },
          {       C_A2,      7,     0, C_BUZZER_070ms,      13,     100,     80 },
          {       C_B2,      7,     0, C_BUZZER_100ms,      13,     100,     80 },
          {      C_F_2,      7,     0, C_BUZZER_270ms,      13,     100,     40 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_RIGHT_TURN[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_A1,      0,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_E1,      0,     0, C_BUZZER_130ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
          };

    const struct SBuzzerParam T_S_LEFT_TURN[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_E1,      0,     0, C_BUZZER_050ms,       5,     100,     80 },
          {       C_B1,      0,     0, C_BUZZER_130ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_CYCLE_START[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_G1,      2,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_E2,      2,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_A2,      2,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_B2,      2,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_E2,      2,     0, C_BUZZER_560ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_OK[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_B1,      4,     0, C_BUZZER_070ms,       5,     100,     80 },
          {       C_B2,      4,     0, C_BUZZER_100ms,       5,     100,     80 },
          {      C_G_1,      4,     0, C_BUZZER_400ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_JINGGLE_MABE[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_E2,      7,     0, C_BUZZER_170ms,      13,     100,     80 },
          {       C_E2,      7,     0, C_BUZZER_150ms,      13,     100,     80 },
          {      C_G_2,      7,     0, C_BUZZER_250ms,       13,     100,     80 },
          {       C_B2,      3,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_B2,      3,     0, C_BUZZER_200ms,       5,     100,     80 },
          {       C_A2,      7,     0, C_BUZZER_560ms,       13,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_CLICK[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_B2,      3,     0, C_BUZZER_170ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_DOUBLE_CLICK[] =
      {
    //      Tone-Freq , Attack, Decay,        Sustain, Release, PeakVol, SustainVol;
          {       C_B1,      3,     0, C_BUZZER_080ms,       5,     100,     80 },
          {       C_B1,      3,     0, C_BUZZER_130ms,       5,     100,     80 },
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam T_S_SILENCE[] =
      {
          {C_END_MUSIC,      0,     0, C_BUZZER_010ms,       0,     100,     80 }
      };

    const struct SBuzzerParam* const T_P_S_MUSIC[] =
          {
            T_S_SILENCE,        //0
            T_S_SOUND_TUNE,     //1
            T_S_INTRO_TUNE,     //2
            T_S_END_TUNE,       //3
            T_S_BEEP,           //4
            T_S_DOUBLE_BEEP,    //5
            T_S_DRINK_BEEP,     //6
            T_S_LOCK_BEEP,      //7
            T_S_DRINK_START,    //8
            T_S_COMM_FAIL,      //9
            T_S_ENDOFCYCLE,     //10
            T_S_END_DELAY,      //11
            T_S_BEEP_LID,       //12
            T_S_WARNING_BEEP,   //13
            T_S_TECHNICIAN_TEST,//14
            T_S_WASHER_OFF,     //15
            T_S_CANCEL,         //16
            T_S_END_OF_CYCLE,   //17
            T_S_RIGHT_TURN,     //18
            T_S_LEFT_TURN,      //19
            T_S_CYCLE_START,    //20
            T_S_OK,             //21
            T_S_JINGGLE_MABE,   //22
            T_S_CLICK,          //23
            T_S_DOUBLE_CLICK,   //24
          };
 
/*****************************************************************************
 Name:          SR_Buzzer
 Parameters:    none
 Returns:       none
 Called by:     main
 Calls:         Drv_TmrInterrupt03.h -> SR_DisableTmrInterrupt03
                Drv_TmrInterrupt03.h -> SR_EnableTmrInterrupt03
                Drv_TmrInterrupt03.h -> SR_SetTmrInterrupt03Freq
 Description:   Play a tone defined by specific notes and time lenght
******************************************************************************/
void SR_Buzzer(void)
{
    if (u16BuzzerCnt > 0)                                                               // Is Buzzer Counter higher than 0
      {
        u16BuzzerCnt--;                                                                 // Decrement Buzzer Counter
      }

    switch ( eBuzzerST)                                                                 // Process Buzzer State
      {
        case C_BUZZER_INIT_ST:                                                          // If in Buzzer Initialization State
            u8MusicPtr      = u8MusicPtr  + 1;                                          // Increment Tone pointer
            pS_BuzzerParam   = T_P_S_MUSIC[u8Tune];                                     // Get the Music Pointer
            u16Tone         = T_U16PWM_REG[pS_BuzzerParam[u8MusicPtr].u16FrequencyHz];                // Set the Main Frequency of the PWM -> The actual Tone to play
            u16PeakVolume    = pS_BuzzerParam[u8MusicPtr].u16PeakVolume;                  // Maximum volume in % for the Attack Wave Form
            u16SustainVolume = pS_BuzzerParam[u8MusicPtr].u16SustainVolume;               // Continuous volume in % Wave Form
            if (pS_BuzzerParam[u8MusicPtr].u16FrequencyHz == C_END_MUSIC)                                                 // If the Tone selection is Out of Range it means to stop the Tune
              {
                u16BuzzerCnt  = 0;                                                       // Reset the Counter
                SRE_BuzzerDriverSetVolumeDutty( 0 );                                    // Set the Volume PWM to 0% of Duty Cycle
                SR_DisableTmrInterrupt03();                     // Turn C_OFF buzzer
                eBuzzerST = C_BUZZER_KILL_ST;                                           // Change Buzzer State to Kill Music
              }
            else                                                                        // If the Tune has not finished
              {
                if (u16Tone == C_SILENCE)                                               // If the Frequency selected is 0
                  {
                    u16BuzzerCnt  = pS_BuzzerParam[u8MusicPtr].u16SustainTimeCsec;        // Set the Silence Duration
                    SRE_BuzzerDriverSetVolumeDutty( 0 );                                // Set the Volume PWM to 0% of Duty Cycle
                    SRE_BuzzerDriverSetToneFrequency( C_SILENCE );                      // Set the Main Frequency of PWM to 0 Hz
                    eBuzzerST    = C_BUZZER_SUSTAIN_ST;                                 // Change the Buzzer State to Sustain the Volume
                  }
                else                                                                    // The Frequency selected is not 0
                  {
                    u16BuzzerCnt      = pS_BuzzerParam[u8MusicPtr].u16AttackTimeCsec;     // Set the Volume Attack time
                    SRE_BuzzerDriverSetToneFrequency( u16Tone );                        // Set the Main Frequency to the Tone Selected
                    SR_EnableTmrInterrupt03();                 // Turn C_ON the buzzer
                    if (u16BuzzerCnt == 0 )                                              // If there is no Attack Time
                      {
                        u16BuzzerCnt = pS_BuzzerParam[u8MusicPtr].u16SustainTimeCsec;     // Set the Sustained Tone Duration
                        SRE_BuzzerDriverSetVolumeDutty( u16SustainVolume );              // Set the Volume PWM to the sustained Duty Cycle
                        eBuzzerST = C_BUZZER_SUSTAIN_ST;                                // Change Buzzer State to Sustained the Volume
                      }
                    else
                      {
                        u16VolumeIncrease = ( u16PeakVolume / u16BuzzerCnt );              // Calculate the Volume Step increase
                        u16SoundVolume    = u16VolumeIncrease;                            // Load the Volume to be played
                        SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                // Set the Volume PWM to the step Duty Cycle
                        eBuzzerST      = C_BUZZER_ATTACK_ST;                            // Change the Buzzer State to Attack
                      }
                  }      
              }
            break;
        case C_BUZZER_ATTACK_ST:                                                       // If in Buzzer Attack State
            if (u16BuzzerCnt == 0 )                                                     // If the Buzzer Counter Reached 0
              {
                u16BuzzerCnt = pS_BuzzerParam[u8MusicPtr].u16DecayTimeCsec;              // Load the Decay Time
                if (u16BuzzerCnt == 0)                                                  // If the Decay Time is 0
                  {
                    u16BuzzerCnt = pS_BuzzerParam[u8MusicPtr].u16SustainTimeCsec;        // Load the Sustained Time
                    SRE_BuzzerDriverSetVolumeDutty( u16SustainVolume );                 // Set the Volume PWM to the sustained Duty Cycle
                    eBuzzerST   = C_BUZZER_SUSTAIN_ST;                                 // Change Buzzer State to Sustained the Volume
                  }
                else                                                                   // The Decay Time is not 0
                  {
                    u16VolumeIncrease = ((u16PeakVolume - u16SustainVolume) / u16BuzzerCnt ); // Calculate the Volume Step decrease
                    u16SoundVolume    =  u16PeakVolume - u16VolumeIncrease;               // Load the Volume to be played
                    SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                   // Set the Volume PWM to the step Duty Cycle
                    eBuzzerST   = C_BUZZER_DECAY_ST;                                   // Change Buzzer State to Initialization
                  }
              }
            else
              {
                u16SoundVolume    = u16SoundVolume + u16VolumeIncrease;                   // Set the increased Volume
                SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                       // Load the Volume PWM to the step Duty Cycle
              }

            break;
       case C_BUZZER_DECAY_ST:                                                         // If in Buzzer Process State
            if (u16BuzzerCnt == 0 )                                                     // If the Buzzer Counter Reached 0
              {
                u16BuzzerCnt = pS_BuzzerParam[u8MusicPtr].u16SustainTimeCsec;            // Set the Tone Duration
                SRE_BuzzerDriverSetVolumeDutty( u16SustainVolume );                     // Set the Volume PWM to the sustained Duty Cycle
                eBuzzerST   = C_BUZZER_SUSTAIN_ST;                                     // Change Buzzer State to Sustained the Volumen
              }
            else
              {
                u16SoundVolume    = u16SoundVolume - u16VolumeIncrease;                  // Set the decreased Volume
                SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                      // Load the Volume PWM to the step Duty Cycle
              }
            break;
       case C_BUZZER_SUSTAIN_ST:                                                      // If in Sustained Duty Cycle State
           if (u16BuzzerCnt == 0 )                                                     // If the Buzzer Counter Reached 0
             {
               u16BuzzerCnt = pS_BuzzerParam[u8MusicPtr].u16ReleaseTimeCsec;            // Set the Release Tone Duration
               if (u16BuzzerCnt == 0)                                                  // If the Release Time is 0
                 {
                   eBuzzerST   = C_BUZZER_INIT_ST;                                    // Change Buzzer State to Initialization
                 }
               else                                                                   // The Release Time is not 0
                 {
                   u16VolumeIncrease = ( ( u16SustainVolume ) / u16BuzzerCnt );     // Calculate the Volume Step decrease
                   u16SoundVolume    = u16SustainVolume - u16VolumeIncrease;             // Load the Volume to be played
                   SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                   // Set the Volume PWM to the step Duty Cycle
                   eBuzzerST   = C_BUZZER_RELEASE_ST;                                 // Change Buzzer State to Release Tone State
                 }
             }
           break;
       case C_BUZZER_RELEASE_ST:                                                      // If in Buzzer Release State
           if (u16BuzzerCnt == 0 )                                                     // If the Buzzer Counter Reached 0
             {
               eBuzzerST   = C_BUZZER_INIT_ST;                                        // Change Buzzer State to Initialization
             }
           else
             {
               u16SoundVolume    = u16SoundVolume - u16VolumeIncrease;                   // Set the decreased Volume
               SRE_BuzzerDriverSetVolumeDutty( u16SoundVolume );                       // Load the Volume PWM to the step Duty Cycle
             }
           break;
        case C_BUZZER_KILL_ST:                                                        // If in Buzzer Kill State
        default:
             SR_DisableTmrInterrupt03();                         // Turn the Buzzer "C_OFF"
            u8MusicPtr = 255;                                                         // Initialize the Music Pointer
            break;
      }
}

/*****************************************************************************
 Name:          SR_PlayMusic
 Parameters:    lu8Music
 Returns:       none
 Called by:     none
 Calls:         none
 Description:   Initialize the execution of a tone
******************************************************************************/
void SR_PlayMusic(U8 lu8Music)
{
  u8MusicPtr = 255;               // Initialize the Music Pointer
  eBuzzerST = C_BUZZER_INIT_ST;
  u8Tune = lu8Music;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_BuzzerTest(void)
{
  if(u8PlayBuzzerTest < 255)
    {
      SR_PlayMusic(u8PlayBuzzerTest);
      u8PlayBuzzerTest = 255;
    }
}
