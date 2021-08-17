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

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Display.h"
#include "CycleSelector.h"
#include "Communications.h"
#include "Drv_UART1.h"
#include "Buzzer.h"
#include "Tablas.h"
#include "Test.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_RefreshDisplay(void)
{
  U16 lu16DisplaySegment;
  U8 lu8CycleSelector;
  
  u8MuxCnt++;
  if(u8MuxCnt > C_MUX_LINES)
    {
      u8MuxCnt = 1;
    }
    
  P_MUX_1 = C_ON;
  P_MUX_2 = C_ON;
  P_MUX_3 = C_ON;
  P_MUX_4 = C_ON;
  
  switch(u8MuxCnt)
    {
      case 1:
        #ifdef C_EFX1870P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_1();
        #endif
        #ifdef C_EFX2009P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_1_Centauro();
        #endif
        break;

      case 2:
        #ifdef C_EFX1870P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_2();
        #endif
        #ifdef C_EFX2009P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_2_Centauro();
        #endif
        break;
      
      case 3:
        #ifdef C_EFX1870P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_3();
        #endif
        #ifdef C_EFX2009P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_3_Centauro();
        #endif
        break;
      
      case 4:
        #ifdef C_EFX1870P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_4();
        #endif
        #ifdef C_EFX2009P001
          lu16DisplaySegment = FN_u16DISPLAY_MUX_4_Centauro();
        #endif
        break;
      
      default:
        lu16DisplaySegment = 0;
        break;
    }
  P_S1 = (lu16DisplaySegment >> 0) & 0x01;
  P_S2 = (lu16DisplaySegment >> 1) & 0x01;
  P_S3 = (lu16DisplaySegment >> 2) & 0x01;
  P_S4 = (lu16DisplaySegment >> 3) & 0x01;
  P_S5 = (lu16DisplaySegment >> 4) & 0x01;
  P_S6 = (lu16DisplaySegment >> 5) & 0x01;
  P_S7 = (lu16DisplaySegment >> 6) & 0x01;
  P_S8 = (lu16DisplaySegment >> 7) & 0x01;
  P_S9 = (lu16DisplaySegment >> 8) & 0x01;
  P_S10 = (lu16DisplaySegment >> 9) & 0x01;
  P_S11 = (lu16DisplaySegment >> 10) & 0x01;

  switch(u8MuxCnt)
    {
      case 1:
        P_MUX_1 = C_OFF;
        break;

      case 2:
        P_MUX_2 = C_OFF;
        break;
      
      case 3:
        P_MUX_3 = C_OFF;
        break;
      
      case 4:
        P_MUX_4 = C_OFF;
        break;
      
      default:
        break;
    }
  
  SR_ReadBtn(u8MuxCnt);
  
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal        S11   S10   S9    S8   S7   S6   S5   S4    S3   S2  S1
            Ubyte_def    B10   B9    B8    B7   B6   B5   B4   B3    B2   B1  B0
            CodeMessage  Led1  Led3  Led0  U.E  U.D  U.G  U.C  Led8  U.B  U.A U.F

******************************************************************************/
U16 FN_u16DISPLAY_MUX_1(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;

  lu16DisplaySegment.Ubit.b0 = ~bf_Units_Seg_F;
  lu16DisplaySegment.Ubit.b1 = ~bf_Units_Seg_A;
  lu16DisplaySegment.Ubit.b2 = ~bf_Units_Seg_B;
  lu16DisplaySegment.Ubit.b3 = bf_Led_8;
  lu16DisplaySegment.Ubit.b4 = ~bf_Units_Seg_C;
  lu16DisplaySegment.Ubit.b5 = ~bf_Units_Seg_G;
  lu16DisplaySegment.Ubit.b6 = ~bf_Units_Seg_D;
  lu16DisplaySegment.Ubit.b7 = ~bf_Units_Seg_E;
  lu16DisplaySegment.Ubit.b8 = bf_Led_0;
  lu16DisplaySegment.Ubit.b9 = bf_Led_3;
  lu16DisplaySegment.Ubit.b10 = bf_Led_1;
  
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal        S11   S10   S9    S8    S7   S6   S5   S4   S3   S2   S1
            Ubyte_def    B10   B9    B8    B7    B6   B5   B4   B3   B2   B1   B0
            CodeMessage  Led4  Led2  Led5  Led8  T.C  T.D  T.E  T.F  T.G  T.A  T.B

******************************************************************************/
U16 FN_u16DISPLAY_MUX_2(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b0 = ~bf_Teens_Seg_B;
  lu16DisplaySegment.Ubit.b1 = ~bf_Teens_Seg_A;
  lu16DisplaySegment.Ubit.b2 = ~bf_Teens_Seg_G;
  lu16DisplaySegment.Ubit.b3 = ~bf_Teens_Seg_F;
  lu16DisplaySegment.Ubit.b4 = ~bf_Teens_Seg_E;
  lu16DisplaySegment.Ubit.b5 = ~bf_Teens_Seg_D;
  lu16DisplaySegment.Ubit.b6 = ~bf_Teens_Seg_C;
  lu16DisplaySegment.Ubit.b7 = bf_Led_LidLock;
  lu16DisplaySegment.Ubit.b8 = bf_Led_5;//Jeans
  lu16DisplaySegment.Ubit.b9 = bf_Led_2;//Color
  lu16DisplaySegment.Ubit.b10 = bf_Led_7;//Eco
  
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal            S11    S10    S9     S8     S7    S6    S5     S4   S3    S2    S1
            Bit              B10     B9    B8     B7     B6    B5    B4     B3   B2    B1    B0
            CodeMessage     Carga  Carga  Carga  Carga  Soak  Wash  Rinse  Spin  Led9  Led7  Led6
                             min    mid    max   auto                           
******************************************************************************/
U16 FN_u16DISPLAY_MUX_3(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b0 = bf_Led_6;//Express
  lu16DisplaySegment.Ubit.b1 = bf_Led_4;//Bulky
  lu16DisplaySegment.Ubit.b2 = bf_Led_9;//Autolimpieza
  lu16DisplaySegment.Ubit.b3 = bf_Led_Manuals_Spin;
  lu16DisplaySegment.Ubit.b4 = bf_Led_Manuals_Rinse;
  lu16DisplaySegment.Ubit.b5 = bf_Led_Manuals_Wash;
  lu16DisplaySegment.Ubit.b6 = bf_Led_Manuals_Soak;
  
  switch(u8WaterLevel)
    {
      case C_WATER_LEVEL_OFF:
        //lu16DisplaySegment.Uint = lu16DisplaySegment.Uint;
        break;
      case C_WATER_LEVEL_LOW:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0400;
        break;
      case C_WATER_LEVEL_MID:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0600;
        break;
      case C_WATER_LEVEL_HIGH:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0700;
        break;
      case C_WATER_LEVEL_AUTO:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0080;
        break;
      default:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0780;
        break;
    }
  
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
 Mensaje Codificado
            Señal        S11  S10   S9    S8    S7    S6    S5    S4    S3    S2    S1
            Bit          B10  B9    B8    B7    B6    B5    B4    B3    B2    B1    B0
            CodeMessage      Spin  Spin  Spin  Cold  Warm   Hot  Led15  Soil  Soil  Soil
                              min   mid   max                           min   mid   max
******************************************************************************/
U16 FN_u16DISPLAY_MUX_4(void)
{
  union UInt_def lu16DisplaySegment;
  
  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b3 = bf_Led_15;
  lu16DisplaySegment.Ubit.b10 = bf_Led_15;
  
  switch(u8SoilLevel)
    {
      case C_SOIL_LEVEL_OFF:
        //lu16DisplaySegment.Uint = lu16DisplaySegment.Uint;
        break;
      case C_SOIL_LEVEL_LOW:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0004;
        break;
      case C_SOIL_LEVEL_MID:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0006;
        break;
      case C_SOIL_LEVEL_HIGH:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0007;
        break;
      default:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0007;
        break;
    }
  
  switch(u8TemperatureLevel)
    {
      case C_TEMPERATURE_LEVEL_OFF:
        //lu16DisplaySegment.Uint = lu16DisplaySegment.Uint;
        break;
      case C_TEMPERATURE_LEVEL_COLD:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0040;
        break;
      case C_TEMPERATURE_LEVEL_WARM:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0020;
        break;
      case C_TEMPERATURE_LEVEL_HOT:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0010;
        break;
      case C_TEMPERATURE_LEVEL_ON:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0070;
        break;
      default:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0070;
        break;
    }
  
  switch(u8SpinLevel)
    {
      case C_SPIN_LEVEL_OFF:
        //lu16DisplaySegment.Uint = lu16DisplaySegment.Uint;
        break;
      case C_SPIN_LEVEL_LOW:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0200;
        break;
      case C_SPIN_LEVEL_MID:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0300;
        break;
      case C_SPIN_LEVEL_HIGH:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0380;
        break;
      default:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0380;
        break;
    }

    
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_ReadBtn(U8 lu8Mux)
{
  U16 u16BtnComparative;
  U8 lu8CurrentBtn;
  
  U8 lu8ButtonPressed;
  
  lu8ButtonPressed = 0;
  switch(lu8Mux)
    {
      case 1:
        if(P_ROW_1 == C_ON)
          {
            bf_Btn_0 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_0 = C_BTN_NOT_PRESSED;
          }
        
        #ifdef C_EFX1870P001
        if(P_ROW_2 == C_ON)
          {
            bf_Btn_1 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_1 = C_BTN_NOT_PRESSED;
          }
        #endif

        if(P_ROW_3 == C_ON)
          {
            bf_Btn_3 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_3 = C_BTN_NOT_PRESSED;
          }
          
        if(P_ROW_4 == C_ON)
          {
            bf_Btn_5 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_5 = C_BTN_NOT_PRESSED;
          }
        break;

      case 2:
        if(P_ROW_1 == C_ON)
          {
            bf_Btn_2 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_2 = C_BTN_NOT_PRESSED;
          }
        
        #ifdef C_EFX1870P001
        if(P_ROW_2 == C_ON)
          {
            bf_Btn_4 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_4 = C_BTN_NOT_PRESSED;
          }
        #endif
          
        if(P_ROW_3 == C_ON)
          {
            bf_Btn_6 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_6 = C_BTN_NOT_PRESSED;
          }
          
        if(P_ROW_4 == C_ON)
         {
            bf_Btn_7 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_7 = C_BTN_NOT_PRESSED;
          }
        break;

      case 3:
        if(P_ROW_1 == C_ON)
          {
            bf_Btn_8 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_8 = C_BTN_NOT_PRESSED;
          }
        
        #ifdef C_EFX1870P001
        if(P_ROW_2 == C_ON)
          {
            bf_Btn_9 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_9 = C_BTN_NOT_PRESSED;
          }
        #endif
        
        if(P_ROW_3 == C_ON)
          {
            bf_Btn_11 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_11 = C_BTN_NOT_PRESSED;
          }
          
        if(P_ROW_4 == C_ON)
          {
            bf_Btn_13 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_13 = C_BTN_NOT_PRESSED;
          }
        break;
        
      case 4:
        if(P_ROW_1 == C_ON)
          {
            bf_Btn_10 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_10 = C_BTN_NOT_PRESSED;
          }
          
        #ifdef C_EFX1870P001
        if(P_ROW_2 == C_ON)
          {
            bf_Btn_12 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_12 = C_BTN_NOT_PRESSED;
          }
        #endif  
        
        if(P_ROW_3 == C_ON)
          {
            bf_Btn_14 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_14 = C_BTN_NOT_PRESSED;
          }
          
        if(P_ROW_4 == C_ON)
          {
            bf_Btn_15 = C_BTN_PRESSED;
          }
        else
          {
            bf_Btn_15 = C_BTN_NOT_PRESSED;
          }
        break;
        
      default:
        break;
    }
  
  lu8CurrentBtn = u8BtnPressedData1;
  SR_DigitalBtnFilter(lu8CurrentBtn, &stFilterBtnData1);
  u8BtnFilteredData1 = stFilterBtnData1.u8FilteredSignal;
  
  lu8CurrentBtn = u8BtnPressedData2;
  SR_DigitalBtnFilter(lu8CurrentBtn, &stFilterBtnData2);
  u8BtnFilteredData2 = stFilterBtnData2.u8FilteredSignal;
  
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:      
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_DigitalBtnFilter(U8 lu8Input, struct stFilterBtnParameters *lpstFilterParam)
{
  if(lpstFilterParam->u8LastSignal != lu8Input)
    {
      lpstFilterParam->u8TimeCnt = lpstFilterParam->u8TimeLimit;
    }
  lpstFilterParam->u8LastSignal = lu8Input;
  
  if((lpstFilterParam->u8TimeCnt) > 0)
    {
      (lpstFilterParam->u8TimeCnt)--;
    }
  else
    {
      lpstFilterParam->u8FilteredSignal = lu8Input;
    }
  
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:      
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_InitBtnFilter(struct stFilterBtnParameters *lpstFilterParam)
{
  lpstFilterParam->u8FilteredSignal = 0;
  lpstFilterParam->u8LastSignal = 0;
  lpstFilterParam->u8TimeCnt = 0;
  lpstFilterParam->u8TimeLimit = C_BTN_TIME_FILTER_TICK;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal        S11   S10   S9    S8   S7   S6   S5   S4    S3   S2  S1
            Ubyte_def    B10   B9    B8    B7   B6   B5   B4   B3    B2   B1  B0
            CodeMessage  Led1  Led3  Led0  U.E  U.D  U.G  U.C  Led8  U.B  U.A U.F

******************************************************************************/
U16 FN_u16DISPLAY_MUX_1_Centauro(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;

  lu16DisplaySegment.Ubit.b0 = ~bf_Units_Seg_B;
  lu16DisplaySegment.Ubit.b1 = ~bf_Units_Seg_A;
  lu16DisplaySegment.Ubit.b2 = ~bf_Units_Seg_F;
  lu16DisplaySegment.Ubit.b3 = 0;
  lu16DisplaySegment.Ubit.b4 = ~bf_Units_Seg_E;
  lu16DisplaySegment.Ubit.b5 = ~bf_Units_Seg_G;
  lu16DisplaySegment.Ubit.b6 = ~bf_Units_Seg_D;
  lu16DisplaySegment.Ubit.b7 = ~bf_Units_Seg_C;
  lu16DisplaySegment.Ubit.b8 = 0;
  lu16DisplaySegment.Ubit.b9 = 0;
  lu16DisplaySegment.Ubit.b10 = 0;

  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal        S11   S10   S9    S8    S7   S6   S5   S4   S3   S2   S1
            Ubyte_def    B10   B9    B8    B7    B6   B5   B4   B3   B2   B1   B0
            CodeMessage  Led4  Led2  Led5  Led8  T.C  T.D  T.E  T.F  T.G  T.A  T.B

******************************************************************************/
U16 FN_u16DISPLAY_MUX_2_Centauro(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b0 = ~bf_Teens_Seg_B; //S1
  lu16DisplaySegment.Ubit.b1 = ~bf_Teens_Seg_A; //S2
  lu16DisplaySegment.Ubit.b2 = ~bf_Teens_Seg_G; //S3
  lu16DisplaySegment.Ubit.b3 = ~bf_Teens_Seg_F; //S4
  lu16DisplaySegment.Ubit.b4 = ~bf_Teens_Seg_E; //S5
  lu16DisplaySegment.Ubit.b5 = ~bf_Teens_Seg_D; //S6
  lu16DisplaySegment.Ubit.b6 = ~bf_Teens_Seg_C; //S7
  lu16DisplaySegment.Ubit.b7 = bf_Led_LidLock; //S8
  lu16DisplaySegment.Ubit.b8 = 0;//Jeans //S9
  lu16DisplaySegment.Ubit.b9 = 0;//Color //S10
  lu16DisplaySegment.Ubit.b10 = 0;//Eco //S11
  
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
            Mensaje Codificado
            Señal            S11    S10    S9     S8     S7    S6    S5     S4   S3    S2    S1
            Bit              B10     B9    B8     B7     B6    B5    B4     B3   B2    B1    B0
            CodeMessage     Carga  Carga  Carga  Carga  Soak  Wash  Rinse  Spin  Led9  Led7  Led6
                             min    mid    max   auto                           
******************************************************************************/
U16 FN_u16DISPLAY_MUX_3_Centauro(void)
{
  union UInt_def lu16DisplaySegment;

  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b0 = 0;//Express  //S1
  lu16DisplaySegment.Ubit.b1 = 0;//Bulky  //S2
  lu16DisplaySegment.Ubit.b2 = 0;//Autolimpieza   //S3
  lu16DisplaySegment.Ubit.b3 = bf_Led_Manuals_Spin; //S4
  lu16DisplaySegment.Ubit.b4 = bf_Led_Manuals_Rinse; //S5
  lu16DisplaySegment.Ubit.b5 = bf_Led_Manuals_Wash; //S6
  lu16DisplaySegment.Ubit.b6 = bf_Led_Manuals_Soak; //S7
  
  switch(u8WaterLevel)
    {
      case C_WATER_LEVEL_OFF:
        //lu16DisplaySegment.Uint = lu16DisplaySegment.Uint;
        break;
      case C_WATER_LEVEL_HIGH:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0200;
        break;
      case C_WATER_LEVEL_MID:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0100;
        break;
      case C_WATER_LEVEL_LOW:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0080;
        break;
      case C_WATER_LEVEL_AUTO:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0400;
        break;
      default:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0780;
        break;
    }
  
  return ~lu16DisplaySegment.Uint;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
 Mensaje Codificado
            Señal        S11  S10   S9    S8    S7    S6    S5    S4    S3    S2    S1
            Bit          B10  B9    B8    B7    B6    B5    B4    B3    B2    B1    B0
            CodeMessage      Spin  Spin  Spin  Cold  Warm   Hot  Led15  Soil  Soil  Soil
                              min   mid   max                           min   mid   max
******************************************************************************/
U16 FN_u16DISPLAY_MUX_4_Centauro(void)
{
  union UInt_def lu16DisplaySegment;
  
  lu16DisplaySegment.Uint = 0;
  
  lu16DisplaySegment.Ubit.b0 = bf_Led_7; //Aqua Saver  //S1
  lu16DisplaySegment.Ubit.b10 = bf_Led_15;  //S11
  
  switch(u8TemperatureLevel)
    {
      case C_TEMPERATURE_LEVEL_OFF:
        break;
      case C_TEMPERATURE_LEVEL_COLD:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0020;
        break;
      case C_TEMPERATURE_LEVEL_WARM:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0010;
        break;
      case C_TEMPERATURE_LEVEL_HOT:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0004;
        break;
      case C_TEMPERATURE_LEVEL_AUTO:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0040;
        break;
      case C_TEMPERATURE_LEVEL_ON:
        lu16DisplaySegment.Uint = lu16DisplaySegment.Uint | 0x0074;
        break;
      default:
        break;
    }
  
  return ~lu16DisplaySegment.Uint;
}
