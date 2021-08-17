/***********************************************************************/
/*                                                                     */
/*  FILE        :Test.c                                                */
/*  DATE        :29/09/2015                                            */
/*  DESCRIPTION :Set test routines                                     */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     :Kraken washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

#include "RAM.h"
#include "Test.h"
#include "Buzzer.h"
#include "Tablas.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_FCT_Test(void)
{
  U8 lu8BtnData1Pressed;
  U8 lu8BtnData2Pressed;
  
  u8FCTTestComplete = C_FALSE;
        
  switch(u8TestSt)
    {
      case C_TEST_INIT:
        u8RxDisplayRqst1Data1 = 0;
        u8RxDisplayRqst1Data2 = 0;
        u8RxDisplayRqst1Data3 = 0;
        u8WaterLevel = C_WATER_LEVEL_OFF;
        u8SoilLevel = C_SOIL_LEVEL_OFF;
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_OFF;
        u8SpinLevel = C_SPIN_LEVEL_OFF;
        u8EcoLevel = C_OFF;
        bf_Led_Manuals_Spin = C_OFF;
        bf_Led_Manuals_Rinse = C_OFF;
        bf_Led_Manuals_Wash = C_OFF;
        bf_Led_Manuals_Soak = C_OFF;
        bf_Led_LidLock = C_OFF;
        u8TeensCoded = C_DISPLAY_CLR;
        u8UnitsCoded = C_DISPLAY_CLR;
        
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFE;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((u8CycleSelectorADC > 214) && (u8CycleSelectorADC < 244))  // V = 4.48V
          {
            u8UserInterfaceType = C_HYBRID;
            SR_PlayMusic(23);
            u8TestSt = C_TEST_1;
            u8FCTSt = C_TEST_1;
          }
        else if((bf_Btn_0_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            u8UserInterfaceType = C_DIGITAL;
            SR_PlayMusic(23);
            u8TestSt = C_TEST_2;
            u8FCTSt = C_TEST_1;
          }
        break;
      
      case C_TEST_1:
        SR_FCT_TestHybrid();
        break;
      
      case C_TEST_2:
        SR_FCT_TestDigital();
        break;
        
      default:
        break;
    }
  u8Teens = T_DISPLAY_VAL[u8TeensCoded];
  u8Units = T_DISPLAY_VAL[u8UnitsCoded];
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_FCT_TestHybrid(void)
{
  U8 lu8BtnData1Pressed;
  U8 lu8BtnData2Pressed;
  
  u8FCTTestComplete = C_FALSE;
  u16TestTickCnt++;
  u8RxDisplayRqst1Data1 = 0;
  u8RxDisplayRqst1Data2 = 0;
  u8RxDisplayRqst1Data3 = 0;
  u8WaterLevel = C_WATER_LEVEL_OFF;
  u8SoilLevel = C_SOIL_LEVEL_OFF;
  u8TemperatureLevel = C_TEMPERATURE_LEVEL_OFF;
  u8SpinLevel = C_SPIN_LEVEL_OFF;
  u8EcoLevel = C_OFF;
  bf_Led_Manuals_Spin = C_OFF;
  bf_Led_Manuals_Rinse = C_OFF;
  bf_Led_Manuals_Wash = C_OFF;
  bf_Led_Manuals_Soak = C_OFF;
  bf_Led_LidLock = C_OFF;
  u8TeensCoded = C_DISPLAY_CLR;
  u8UnitsCoded = C_DISPLAY_CLR;
  
  switch(u8FCTSt)
    {
      case C_TEST_1:
        u8UnitsCoded = C_DISPLAY_SEG_A;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0x7F;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_7_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_2;
          }
        break;
      case C_TEST_2:
        u8UnitsCoded = C_DISPLAY_SEG_B;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0x7F;
        if((bf_Btn_15_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_3;
          }
        break;
      case C_TEST_3:
        u8UnitsCoded = C_DISPLAY_SEG_C;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFB;
        if((bf_Btn_10_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_4;
          }
        break;
      case C_TEST_4:
        u8UnitsCoded = C_DISPLAY_SEG_D;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xF7;
        if((bf_Btn_11_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_5;
          }
        break;
      case C_TEST_5:
        u8UnitsCoded = C_DISPLAY_SEG_E;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xEF;
        if((bf_Btn_12_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_6;
          }
        break;
      case C_TEST_6:
        u8UnitsCoded = C_DISPLAY_SEG_F;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xDF;
        if((bf_Btn_13_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_7;
          }
        break;
      case C_TEST_7:
        u8UnitsCoded = C_DISPLAY_SEG_G;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xBF;
        if((bf_Btn_14_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_8;
          }
        break;
      case C_TEST_8:
        bf_Led_8 = C_ON;  // LED Delay
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFE;
        if((bf_Btn_8_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_9;
          }
        break;
      case C_TEST_9:
        u8WaterLevel = C_WATER_LEVEL_LOW;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((u16TestTickCnt >= C_500_ms) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_10;
          }
        break;
      case C_TEST_10:
        u8WaterLevel = C_WATER_LEVEL_MID;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_11;
          }
        break;
      case C_TEST_11:
        u8WaterLevel = C_WATER_LEVEL_HIGH;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_12;
          }
        break;
      case C_TEST_12:
        u8TeensCoded = C_DISPLAY_SEG_E;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_13;
          }
        break;
      case C_TEST_13:
        bf_Led_Manuals_Rinse = C_ON;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_14;
          }
        break;
      case C_TEST_14:
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_HOT;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_15;
          }
        break;
      case C_TEST_15:
        u8RxDisplayRqst1Data1 = 0xFF;
        u8RxDisplayRqst1Data2 = 0xFF;
        u8RxDisplayRqst1Data3 = 0xFF;
        u8WaterLevel = C_WATER_LEVEL_ALL_ON;
        u8SoilLevel = C_SOIL_LEVEL_HIGH;
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_ON;
        u8SpinLevel = C_SPIN_LEVEL_HIGH;
        u8EcoLevel = C_ON;
        bf_Led_Manuals_Spin = C_ON;
        bf_Led_Manuals_Rinse = C_ON;
        bf_Led_Manuals_Wash = C_ON;
        bf_Led_Manuals_Soak = C_ON;
        bf_Led_LidLock = C_ON;
        u8TeensCoded = C_DISPLAY_8;
        u8UnitsCoded = C_DISPLAY_8;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0x7F;
        if(u16TestTickCnt >= C_500_ms)
          {
            u16TestTickCnt = 0;
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_16;
          }
        break;
      case C_TEST_16:
        if(u8FCTData1 == 0xFE)
          {
            u8FCTSt = C_TEST_17;
          }
        break;
      case C_TEST_17:
        if(u8FCTData1 == 0xFF)
          {
            SR_PlayMusic(3);
            u8FCTSt = C_TEST_18;
          }
        break;
      
      default:
        u8FCTTestComplete = C_TRUE;
        break;
    }
  u8Teens = T_DISPLAY_VAL[u8TeensCoded];
  u8Units = T_DISPLAY_VAL[u8UnitsCoded];
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_FCT_TestDigital(void)
{
  U8 lu8BtnData1Pressed;
  U8 lu8BtnData2Pressed;
  
  u8FCTTestComplete = C_FALSE;
  u8RxDisplayRqst1Data1 = 0;
  u8RxDisplayRqst1Data2 = 0;
  u8RxDisplayRqst1Data3 = 0;
  u8WaterLevel = C_WATER_LEVEL_OFF;
  u8SoilLevel = C_SOIL_LEVEL_OFF;
  u8TemperatureLevel = C_TEMPERATURE_LEVEL_OFF;
  u8SpinLevel = C_SPIN_LEVEL_OFF;
  u8EcoLevel = C_OFF;
  bf_Led_Manuals_Spin = C_OFF;
  bf_Led_Manuals_Rinse = C_OFF;
  bf_Led_Manuals_Wash = C_OFF;
  bf_Led_Manuals_Soak = C_OFF;
  bf_Led_LidLock = C_OFF;
  u8TeensCoded = C_DISPLAY_CLR;
  u8UnitsCoded = C_DISPLAY_CLR;
  
  switch(u8FCTSt)
    {
      case C_TEST_1:
        u8UnitsCoded = C_DISPLAY_SEG_A;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFD;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_1_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_2;
          }
        break;
      case C_TEST_2:
        u8UnitsCoded = C_DISPLAY_SEG_B;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFB;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_2_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_3;
          }
        break;
      case C_TEST_3:
        u8UnitsCoded = C_DISPLAY_SEG_C;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xF7;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_3_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_4;
          }
        break;
      case C_TEST_4:
        u8UnitsCoded = C_DISPLAY_SEG_D;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xEF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_4_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_5;
          }
        break;
      case C_TEST_5:
        u8UnitsCoded = C_DISPLAY_SEG_E;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xDF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_5_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_6;
          }
        break;
      case C_TEST_6:
        u8UnitsCoded = C_DISPLAY_SEG_F;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xBF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_6_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_7;
          }
        break;
      case C_TEST_7:
        u8UnitsCoded = C_DISPLAY_SEG_G;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0x7F;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFF;
        if((bf_Btn_7_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_8;
          }
        break;
      case C_TEST_8:
        bf_Led_8 = C_ON;  // LED Delay
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFE;
        if((bf_Btn_8_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_9;
          }
        break;
      case C_TEST_9:
        u8WaterLevel = C_WATER_LEVEL_LOW;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFD;
        if((bf_Btn_9_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_10;
          }
        break;
      case C_TEST_10:
        u8WaterLevel = C_WATER_LEVEL_MID;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xFB;
        if((bf_Btn_10_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_11;
          }
        break;
      case C_TEST_11:
        u8WaterLevel = C_WATER_LEVEL_HIGH;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xF7;
        if((bf_Btn_11_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_12;
          }
        break;
      case C_TEST_12:
        u8TeensCoded = C_DISPLAY_SEG_E;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xEF;
        if((bf_Btn_12_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_13;
          }
        break;
      case C_TEST_13:
        bf_Led_Manuals_Rinse = C_ON;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xDF;
        if((bf_Btn_13_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_14;
          }
        break;
      case C_TEST_14:
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_HOT;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0xBF;
        if((bf_Btn_14_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_15;
          }
        break;
      case C_TEST_15:
        u8RxDisplayRqst1Data1 = 0xFF;
        u8RxDisplayRqst1Data2 = 0xFF;
        u8RxDisplayRqst1Data3 = 0xFF;
        u8WaterLevel = C_WATER_LEVEL_ALL_ON;
        u8SoilLevel = C_SOIL_LEVEL_HIGH;
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_ON;
        u8SpinLevel = C_SPIN_LEVEL_HIGH;
        u8EcoLevel = C_ON;
        bf_Led_Manuals_Spin = C_ON;
        bf_Led_Manuals_Rinse = C_ON;
        bf_Led_Manuals_Wash = C_ON;
        bf_Led_Manuals_Soak = C_ON;
        bf_Led_LidLock = C_ON;
        u8TeensCoded = C_DISPLAY_8;
        u8UnitsCoded = C_DISPLAY_8;
        lu8BtnData1Pressed = u8BtnFilteredData1 & 0xFF;
        lu8BtnData2Pressed = u8BtnFilteredData2 & 0x7F;
        if((bf_Btn_15_Filtered == C_BTN_PRESSED) && (lu8BtnData1Pressed == 0) && (lu8BtnData2Pressed == 0))
          {
            SR_PlayMusic(23);
            u8FCTSt = C_TEST_16;
          }
        break;
      case C_TEST_16:
        if(u8FCTData1 == 0xFE)
          {
            u8FCTSt = C_TEST_17;
          }
        break;
      case C_TEST_17:
        if(u8FCTData1 == 0xFF)
          {
            SR_PlayMusic(3);
            u8FCTSt = C_TEST_18;
          }
        break;
      
      default:
        u8FCTTestComplete = C_TRUE;
        break;
    }
  u8Teens = T_DISPLAY_VAL[u8TeensCoded];
  u8Units = T_DISPLAY_VAL[u8UnitsCoded];
}
/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_UserInterfaceTest(void)
{
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:      
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_ALT_Test(void)
{
  u16AltTestTimeCnt++;
  
  switch(u8AltTestSt)
    {
      case C_TEST_INIT:
        u8RxDisplayRqst1Data1  = 0;
        u8RxDisplayRqst1Data2  = 0;
        u8RxDisplayRqst1Data3  = 0;
        u8RxDisplayRqst1Data4  = 0;
        u8RxDisplayRqst1Data5  = 0;
        u8RxDisplayRqst1Data6  = 0;
        u8RxDisplayRqst1Data7  = 0;
        u8RxDisplayRqst1Data8  = 0;
        u8RxDisplayRqst1Data9  = 0;
        u8RxDisplayRqst1Data10 = 0;
        u8RxDisplayRqst1Data11 = 0;
        u8Teens = T_DISPLAY_VAL[C_DISPLAY_CLR];
        u8Units = T_DISPLAY_VAL[C_DISPLAY_CLR];
        if(u16AltTestTimeCnt > C_ALT_PERIOD)
          {
            u16AltTestTimeCnt = 0;
            SR_PlayMusic(2);
            u8AltTestSt = C_TEST_1;
          }
        break;
        
      case C_TEST_1:
        bf_Led_0 = C_ON;
        bf_Led_1 = C_ON;
        bf_Led_2 = C_ON;
        bf_Led_3 = C_ON;
        bf_Led_4 = C_ON;
        bf_Led_5 = C_ON;
        bf_Led_6 = C_ON;
        bf_Led_7 = C_OFF;
        bf_Led_8 = C_OFF;
        bf_Led_9 = C_OFF;
        bf_Led_15 = C_OFF;
        bf_Led_LidLock = C_OFF;
        u8Teens = T_DISPLAY_VAL[C_DISPLAY_CLR];
        u8Units = T_DISPLAY_VAL[C_DISPLAY_CLR];
        bf_Led_Manuals_Spin = C_OFF;
        bf_Led_Manuals_Rinse = C_OFF;
        bf_Led_Manuals_Wash = C_OFF;
        bf_Led_Manuals_Soak = C_OFF;
        u8WaterLevel = C_WATER_LEVEL_OFF;
        u8SoilLevel = C_SOIL_LEVEL_OFF;
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_OFF;
        u8SpinLevel = C_SPIN_LEVEL_OFF;
       
        if(u16AltTestTimeCnt > C_ALT_PERIOD)
          {
            u16AltTestTimeCnt = 0;
            u8AltTestSt = C_TEST_2;
          }
        break;
        
      case C_TEST_2:
        bf_Led_0 = C_OFF;
        bf_Led_1 = C_OFF;
        bf_Led_2 = C_OFF;
        bf_Led_3 = C_OFF;
        bf_Led_4 = C_OFF;
        bf_Led_5 = C_OFF;
        bf_Led_6 = C_OFF;
        bf_Led_7 = C_ON;
        bf_Led_8 = C_ON;
        bf_Led_9 = C_ON;
        bf_Led_15 = C_OFF;
        bf_Led_LidLock = C_ON;
        u8Teens = T_DISPLAY_VAL[C_DISPLAY_8];
        u8Units = T_DISPLAY_VAL[C_DISPLAY_8];
        bf_Led_Manuals_Spin = C_OFF;
        bf_Led_Manuals_Rinse = C_OFF;
        bf_Led_Manuals_Wash = C_OFF;
        bf_Led_Manuals_Soak = C_OFF;
        u8WaterLevel = C_WATER_LEVEL_OFF;
        u8SoilLevel = C_SOIL_LEVEL_OFF;
        u8TemperatureLevel = C_TEMPERATURE_LEVEL_OFF;
        u8SpinLevel = C_SPIN_LEVEL_OFF;
        if(u16AltTestTimeCnt > C_ALT_PERIOD)
          {
            u16AltTestTimeCnt = 0;
            u8AltTestSt = C_TEST_3;
          }
        break;
        
      case C_TEST_3:
        bf_Led_0 = C_OFF;
        bf_Led_1 = C_OFF;
        bf_Led_2 = C_OFF;
        bf_Led_3 = C_OFF;
        bf_Led_4 = C_OFF;
        bf_Led_5 = C_OFF;
        bf_Led_6 = C_OFF;
        bf_Led_7 = C_OFF;
        bf_Led_8 = C_OFF;
        bf_Led_9 = C_OFF;
        bf_Led_15 = C_ON;
        bf_Led_LidLock = C_OFF;
        u8Teens = T_DISPLAY_VAL[C_DISPLAY_CLR];
        u8Units = T_DISPLAY_VAL[C_DISPLAY_CLR];
        bf_Led_Manuals_Spin = C_ON;
        bf_Led_Manuals_Rinse = C_ON;
        bf_Led_Manuals_Wash = C_ON;
        bf_Led_Manuals_Soak = C_ON;
        u8WaterLevel = 15;
        u8SoilLevel = 15;
        u8TemperatureLevel = 15;
        u8SpinLevel = 15;
        if(u16AltTestTimeCnt > C_ALT_PERIOD)
          {
            u16AltTestTimeCnt = 0;
            u8AltTestSt = C_TEST_4;
          }
        break;
        
      case C_TEST_4:
        u16AltTestTimeCnt = 0;
        u8AltTestSt = C_TEST_1;
        SR_PlayMusic(3);
        break;
        
      default:
        break;
    }
    
  if((u8BtnFilteredData1 == 0) && (u8BtnFilteredData2 == 0))
      {
        u8ReleaseBtn = 1;
      }
      
    if((u8BtnFilteredData1 > 0) || (u8BtnFilteredData2 > 0))
      {
        if(u8ReleaseBtn == 1)
          {
            u8ReleaseBtn = 0;
            SR_PlayMusic(23);
          }
      }
}
