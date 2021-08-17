/***********************************************************************/
/*                                                                     */
/*  FILE        :Communications.c                                      */
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

/*****************************************************************************
    Includes
*****************************************************************************/
#include "RAM.h"
#include "Communications.h"
#include "Drv_UART1.h"
#include "Buzzer.h"
#include "Tablas.h"
#include "crc.h"

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_SerialComm(void)
{
  U8 lu8UIComm;
  
  if(u8CommTimeout > 0)
    {
      u8CommTimeout--;
    }
  else
    {
      u8RxByteCnt = 0;
    }
    
  if(u8EnableSlaveTx == C_TRUE)
    {
      u8EnableSlaveTx = C_FALSE;
      u8TxByteCnt = 0;        // Clear Bytes sent counter
      u8RxByteCnt = 0;
      u8FrameReceivedStatus = FN_u8FrameReceivedStatus(au8BufferRx); // Check the status of the last frame received
      lu8UIComm = au8BufferRx[0] & 0x0F;
      if((u8FrameReceivedStatus == C_FRAME_RECEIVED_OK) && (lu8UIComm == C_DISPLAY_ID))
        {
          SR_DisableUart1Rx();
          SR_GetFrame();
          SR_SlaveDeviceManager();  // Define Slave device to send data
          SR_CommandManager(); // Define the command to be sent
          SR_SetFrame();          // Define the data to be sent
          SR_EnableUart1Tx();     // Enable Uart Tx
          TXD1 = au8BufferTx[0];  
        }
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
void SR_SetFrame(void)
{
  U8 lu8ChecksumByte;
  U8 lu8BufferLenght;
  union UInt_def lu16Crc;
  
  lu8ChecksumByte = C_COMM_FRAME_SIZE - 1;
  
  au8BufferTx[0] = u8TxRxID;
  au8BufferTx[1] = u8CommandTx;
  switch(u8TxRxID)
    {
      case C_DISPLAY_TO_TEST_EQUIPMENT:
        SR_SetTestEquipmentFrame(u8CommandTx);
        break;
      case C_DISPLAY_TO_MASTER:
        SR_SetDisplayFrame(u8CommandTx);
        break;
        
      default:
        break;
    }
  
  lu8BufferLenght = C_COMM_FRAME_SIZE - 2;
  lu16Crc.Uint = FN_CalcCRC(au8BufferTx, lu8BufferLenght);
  
  au8BufferTx[C_COMM_FRAME_SIZE - 2] = lu16Crc.nu8byte.MSByte;
  au8BufferTx[C_COMM_FRAME_SIZE - 1] = lu16Crc.nu8byte.LSByte;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_SetDisplayFrame(U8 lu8CommandTx)
{
  switch(lu8CommandTx)
    {
      case C_CMD_DISPLAY_RQST:
      case C_CMD_DISPLAY_RQST2:
        au8BufferTx[2] = u8BtnFilteredData1;
        au8BufferTx[3] = u8BtnFilteredData2;
        au8BufferTx[4] = 0;
        au8BufferTx[5] = 0;
        au8BufferTx[6] = 0;
        au8BufferTx[7] = u8BtnCoded;
        au8BufferTx[8] = 0;
        au8BufferTx[9] = 0;
        au8BufferTx[10] = 0;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = u8TxDispRqstData11 | u8Cycle;
        break;
        
      case C_CMD_REPORT_MODEL:
        au8BufferTx[1] = C_CMD_GET_MODEL;
        au8BufferTx[2] = 0x02;
        au8BufferTx[3] = 0x05;
        au8BufferTx[4] = T_HARDWARE_ID[0];
        au8BufferTx[5] = T_SW_PART_NUMBER[3];
        au8BufferTx[6] = T_SW_PART_NUMBER[4];
        au8BufferTx[7] = T_SW_PART_NUMBER[5];
        au8BufferTx[8] = T_SW_PART_NUMBER[6];
        au8BufferTx[9] = T_GROUP_NO;
        au8BufferTx[10] = T_REVISION_NO;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
        
      default:
        au8BufferTx[2] = 0;
        au8BufferTx[3] = 0;
        au8BufferTx[4] = 0;
        au8BufferTx[5] = 0;
        au8BufferTx[6] = 0;
        au8BufferTx[7] = 0;
        au8BufferTx[8] = 0;
        au8BufferTx[9] = 0;
        au8BufferTx[10] = 0;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
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
void SR_SetTestEquipmentFrame(U8 lu8Command)
{
  U8 lu8SwGroup;
  U8 lu8SwRev;
  
  switch(lu8Command)
    {
      case C_CMD_DEFAULT_FRAME:
        au8BufferTx[2] = 0;
        au8BufferTx[3] = 0;
        au8BufferTx[4] = 0;
        au8BufferTx[5] = 0;
        au8BufferTx[6] = 0;
        au8BufferTx[7] = 0;
        au8BufferTx[8] = 0;
        au8BufferTx[9] = 0;
        au8BufferTx[10] = 0;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
        
      case C_CMD_REPORT_MODEL:
        au8BufferTx[2] = 0x02;
        au8BufferTx[3] = 0x05;
        au8BufferTx[4] = 0;
        au8BufferTx[5] = T_SW_PART_NUMBER[3];
        au8BufferTx[6] = T_SW_PART_NUMBER[4];
        au8BufferTx[7] = T_SW_PART_NUMBER[5];
        au8BufferTx[8] = T_SW_PART_NUMBER[6];
        au8BufferTx[9] = T_GROUP_NO;
        au8BufferTx[10] = T_REVISION_NO;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
      
      case C_CMD_SET_TE_MODE:
        au8BufferTx[2] = 1;
        au8BufferTx[3] = 1;
        au8BufferTx[4] = 0x50;
        au8BufferTx[5] = 0;
        au8BufferTx[6] = 0;
        au8BufferTx[7] = 0;
        au8BufferTx[8] = 0;
        au8BufferTx[9] = 0;
        au8BufferTx[10] = 0;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
      
      case C_CMD_TEST_LOADS:
        au8BufferTx[2] = u8FCTData1;
        
        if(u8FCTData1 == 0xFF)
          {
            au8BufferTx[3] = u8FCTTestComplete;
          }
        else
          {
            au8BufferTx[3] = 0;
          }
        au8BufferTx[4] = 0;
        au8BufferTx[5] = 0;
        au8BufferTx[6] = 0;
        au8BufferTx[7] = 0;
        au8BufferTx[8] = 0;
        au8BufferTx[9] = 0;
        au8BufferTx[10] = 0;
        au8BufferTx[11] = 0;
        au8BufferTx[12] = 0;
        break;
        
      default:
        break;
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
void SR_CommandManager(void)
{
  switch(u8TxRxID)
    {
      case C_DISPLAY_TO_TEST_EQUIPMENT:
        SR_TestEquipmentCommandManager();
        break;
      default: //case C_DISPLAY_TO_MASTER:
        SR_DisplayCommandManager();
        break;
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
void SR_TestEquipmentCommandManager(void)
{
  u8CommandTx = u8TECmdRx;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_DisplayCommandManager(void)
{
  switch(u8CommandRx)
    {
      case C_CMD_GET_MODEL:
        u8CommandTx = C_CMD_REPORT_MODEL;
        break;
      default:
        u8CommandTx = u8CommandRx;
        break;
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
void SR_SlaveDeviceManager(void)
{
  switch(u8DeviceRqstID)
    {
      case C_TEST_EQUIPMENT_TO_DISPLAY:
        u8TxRxID = C_DISPLAY_TO_TEST_EQUIPMENT;
        break;
      default:
        u8TxRxID = C_DISPLAY_TO_MASTER;
        break;
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
void SR_CommLevelManager(void)
{
  if(u8CommandRx == C_CMD_SET_TE_MODE)
    {
      if(u8CommLevel == C_COMM_LEVEL_0)
        {
          u8CommLevel = C_COMM_LEVEL_1;
        }
      else
        {
          if(u8PersonalizeTimeElapsed == C_FALSE)
            {
              u8CommLevel = C_COMM_LEVEL_2;
            }
        }
    }

  if(u16SecondsElapsed > C_PERSONALIZE_TIME)
    {
      u8PersonalizeTimeElapsed = C_TRUE;
    }
    
  if((u8CommLevel != C_COMM_LEVEL_0) && (u8TestEquipmentDisconnectedCnt > C_TEST_EQUIPMENT_DISCONNECT_TICK))
    {
      u8CommLevel = C_COMM_LEVEL_0;
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
U8 FN_u8CalculateChecksum(U8 *lpu8ChecksumArray)
{
  U8 lu8Cnt;
  U8 lu8Checksum;
  U8 lu8ChecksumByte;
  
  lu8ChecksumByte = C_COMM_FRAME_SIZE - 1;
  lu8Checksum = 0;
  
  for(lu8Cnt = 0; lu8Cnt < lu8ChecksumByte; lu8Cnt++)
    {
      lu8Checksum = lu8Checksum + *(lpu8ChecksumArray + lu8Cnt);  // Calculate Checksum
    }
  return lu8Checksum;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
U8 FN_u8FrameReceivedStatus(U8 *lpuArrayReceived)
{
  U8 lu8ChecksumReceived;
  U8 lu8Status;
  U8 lu8ChecksumByte;
  U8 lu8BufferLenght;
  U16 lu16CrcBuffer;
  U16 lu16CrcReceived;

  lu8BufferLenght = C_COMM_FRAME_SIZE - 2;
  lu16CrcBuffer = FN_CalcCRC(au8BufferRx, lu8BufferLenght);
  lu16CrcReceived = ((U16)au8BufferRx[C_COMM_FRAME_SIZE - 2] << 8) | (U16)au8BufferRx[C_COMM_FRAME_SIZE - 1];
      
  if(lu16CrcBuffer == lu16CrcReceived)
    {
      lu8Status = C_FRAME_RECEIVED_OK;
    }
  else
    {
      lu8Status = C_FRAME_RECEIVED_INVALID;
    }
  
  return lu8Status;
}

/*****************************************************************************
 Name:          
 Parameters:    
 Returns:       
 Called by:     
 Calls:         
 Description:   
******************************************************************************/
void SR_GetFrame(void)
{
  u8DeviceRqstID = au8BufferRx[0];
  
  switch(u8DeviceRqstID)
    {
      case C_TEST_EQUIPMENT_TO_DISPLAY:
        u8TECmdRx = au8BufferRx[1];
        SR_GetTestEquipmentFrame(u8TECmdRx);
        break;
        
      case C_MASTER_TO_DISPLAY:
        u8CommandRx = au8BufferRx[1];
        SR_GetDisplayFrame(u8CommandRx);
        break;
        
      default:
        break;
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
void SR_GetDisplayFrame(U8 lu8CommandRx)
{
  switch(u8CommandRx)
    {
      case C_CMD_DISPLAY_RQST:
        u8RxDisplayRqst1Data1  = au8BufferRx[2];
        u8RxDisplayRqst1Data2  = au8BufferRx[3];
        u8RxDisplayRqst1Data3  = au8BufferRx[4];
        u8RxDisplayRqst1Data4  = au8BufferRx[5];
        u8RxDisplayRqst1Data5  = au8BufferRx[6];
        u8RxDisplayRqst1Data6  = au8BufferRx[7];
        u8RxDisplayRqst1Data7  = au8BufferRx[8];
        u8RxDisplayRqst1Data8  = au8BufferRx[9];
        u8RxDisplayRqst1Data9  = au8BufferRx[10];
        u8RxDisplayRqst1Data10 = au8BufferRx[11];
        u8RxDisplayRqst1Data11 = au8BufferRx[12];
        
        u8BuzzerTone = u8RxDisplayRqst1Data11 & 0x3F;
        if(u8BuzzerTone != 0)
          {
            SR_PlayMusic(u8BuzzerTone);
          }
        break;
      
      case C_CMD_DISPLAY_RQST2:
        u8TeensCoded = au8BufferRx[4];
        u8UnitsCoded = au8BufferRx[5];
        u8Teens = T_DISPLAY_VAL[u8TeensCoded];
        u8Units = T_DISPLAY_VAL[u8UnitsCoded];
        break;
        
      default:
        break;
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
void SR_GetTestEquipmentFrame(U8 lu8CommandRx)
{
  switch(u8TECmdRx)
    {
      case C_CMD_TEST_LOADS:
        u8FCTData1 = au8BufferRx[2];
        break;
      default:
        break;
    }
}
