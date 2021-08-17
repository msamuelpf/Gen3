/**********************************************************************

  FILE        : EFX1854P001.h
  DATE        : 06/04/2015
  DESCRIPTION : Header file for the Mabe Safety library.
                It declares all the subroutines / functions that works as interface
                between the library and application.
  CPU TYPE    : RX210 R5F52105BDFN
  AUTHOR      : jrmmexdi
  PROJECT     : Kraken 27
  IDE         : E2 Studio Version 3.1.2.10
  Compiler    : Renesas RX Compiler V2.03.00

  Copyright (c) 2015 Mabe TyP
  All rights reserved

**********************************************************************/
#ifndef _EFX1854P001_H_
#define _EFX1854P001_H_

#include <MabeTypeDefine.h>

/***********************************************************************
             CPU module functions with Safety Link
***********************************************************************/
#define C_MAIN_TICK_MS             (U32) 10

extern U8 FNE_u8CommunicationTick(void);


/***********************************************************************
             Lid module functions with Safety Link
***********************************************************************/
// Type definition for lid switch interaction. It defines the possible lid switch states.
typedef enum {
  E_LID_SWITCH_CLOSED ,
  E_LID_SWITCH_OPENED ,
  E_LID_SWITCH_IN_PROCESS,
  E_LID_SWITCH_ERROR
}ELidSwitchStatus;

// Type definition for lid lock interaction. It defines the possible lid lock states.
typedef enum {
  E_LID_LOCK_LOCKED   ,
  E_LID_LOCK_UNLOCKED ,
  E_LID_LOCK_IN_PROCESS,
  E_LID_LOCK_ERROR
}ELidLockStatus;

// Type definition for lid lock interaction. It defines the possible lid lock request.
typedef enum {
  E_LID_LOCK_LOCK   ,
  E_LID_LOCK_UNLOCK
}ELidLockRequestState;

extern ELidSwitchStatus FNE_eLidSwitchReadState ( void );
extern ELidLockStatus FNE_eLidLockReadState(void);
extern void SRE_LidLockSetState(ELidLockRequestState leLidLockRequestState);
extern ELidLockStatus FNE_GetLidLockTargetStatus(void);

/***********************************************************************
             MCU Self Test module functions with Safety Link
***********************************************************************/
extern U16 FNE_u16FlashCRC(void);


/***********************************************************************
             Safety Algorithms module functions with Safety Link
***********************************************************************/
// Type definition for Safety failure type
typedef enum {
  E_SAFETY_FAILURE_NO_FAIL                       = 0,  // No failure
  E_SAFETY_FAILURE_AMP1                          = 1,  // E1 -> Speed > 60rpm Lid Lock open
  E_SAFETY_FAILURE_AMP2                          = 2,  // E2 -> Motor Off and speed
  E_SAFETY_FAILURE_AMP3                          = 3,  // E3 -> Motor On and No speed
  E_SAFETY_FAILURE_AMP5                          = 4,  // E4 -> Lid Lock Error
  E_SAFETY_FAILURE_AMP6                          = 5,  // E5 -> Speed > 1000rpms
  E_SAFETY_FAILURE_AMP7                          = 6,  // E6 -> Safety Relay Short
  E_SAFETY_FAILURE_AMP8                          = 7,  // E7 -> Triac Short
  E_SAFETY_FAILURE_OVE1                          = 8,  // E8 -> Overflow
  E_SAFETY_FAILURE_OVE2                          = 9,  // E9 -> No Water Change
  E_SAFETY_FAILURE_OVE3                          = 10, // EA -> Pressure Sensor Out of Range
  E_SAFETY_FAILURE_HOSE_DISCONNECTED             = 11, // EB -> Hose Disconnected
  E_SAFETY_FAILURE_OVERFLOW_DRAIN_PUMP           = 12, // EC -> No Drain
  E_SAFETY_FAILURE_ZC1                           = 13, // ED -> High Frequency
  E_SAFETY_FAILURE_ZC2                           = 14, // EE -> Low Frequency
  E_SAFETY_FAILURE_CRC_FAIL                      = 15, // EF -> Bad CRC
  E_SAFETY_FAILURE_MEMORY_FAIL                   = 16, // EG -> Bad Memory
  E_SAFETY_FAILURE_DUMY_17                       = 17, // EH -> Not Implemented
  E_SAFETY_FAILURE_DUMY_18                       = 18, // EJ -> Not Implemented
  E_SAFETY_FAILURE_DUMY_19                       = 19, // EL -> Not Implemented
  E_SAFETY_FAILURE_DUMY_20                       = 20, // En -> Not Implemented
  E_SAFETY_FAILURE_PRESSURE_SENSOR_DISCONNECT    = 21, // EP -> Pressure Sensor Disconnected
  E_SAFETY_FAILURE_PRESSURE_HOSE_RESTRICTION     = 22, // Er -> Pressure Sensor Disconnected
  E_SAFETY_FAILURE_NO_PARAM                      = 23, // Et -> Pressure Sensor Disconnected
  E_SAFETY_FAILURE_SHIFTER                       = 24, // Eu -> Shifter Error
}ESafetyFailureCode;

extern void SRE_SafetyAlgorithmsStartUpTest(void);
extern void SRE_SafetyProcess(void);
extern ESafetyFailureCode FNE_eReadSafetyFailureCode(void);
extern U8 FNE_u8SafetyWaterLevelIncreasing(void);

extern void SRE_UpdateBrownOutAppVariables( U8 * lpu8BufferToSave , U8 lu8EnableWriteProcess);
extern void SRE_ReturnBrownOutAppVariables( U8 * lpu8BufferToSave);

extern U16 FNE_u16GetSafetyOverflowLimit(void);
/***********************************************************************
             Data Flash module functions with Safety Link
***********************************************************************/
#define C_NO_ERRASE_ERROR             (0)
#define C_ERRASE_OUT_RANGE            (1)

/**** Function Return Values ****/
/* Operation was successful */
#define C_API_FLASH_SUCCESS           (0x00)   /* Flash area checked was blank, making this 0x00 as well to keep existing code checking compatibility */
#define C_API_FLASH_BLANK             (0x00)   /* The address that was supplied was not on aligned correctly for ROM or DF */
#define C_API_FLASH_ERROR_ALIGNED     (0x01)   /* Flash area checked was not blank, making this 0x01 as well to keep existing code checking compatibility */
#define C_API_FLASH_NOT_BLANK         (0x01)   /* The number of bytes supplied to write was incorrect */
#define C_API_FLASH_ERROR_BYTES       (0x02)   /* The address provided is not a valid ROM or DF address */
#define C_API_FLASH_ERROR_ADDRESS     (0x03)   /* Writes cannot cross the 1MB boundary on some parts */
#define C_API_FLASH_ERROR_BOUNDARY    (0x04)   /* Flash is busy with another operation */
#define C_API_FLASH_BUSY              (0x05)   /* Operation failed */
#define C_API_FLASH_FAILURE           (0x06)   /* Lock bit was set for the block in question */
#define C_API_FLASH_LOCK_BIT_SET      (0x07)   /* Lock bit was not set for the block in question */
#define C_API_FLASH_LOCK_BIT_NOT_SET  (0x08)   /* 'Address + number of bytes' for this operation went past the end of this * memory area. */
#define C_API_FLASH_ERROR_OVERFLOW    (0x09)

#define C_PARAM_BLOCK_SIZE            (0x80)
#define C_CYCLES_ERASE_BLOCK_SIZE     (0x80)

#define C_MAX_PARAM_BLOCK             (16)
#define C_MAX_FACTORY_ELEMENTS        (0x80)
#define C_MAX_MY_CYCLE_ELEMENTS       (0x80)
#define C_MAX_SKU_ELEMENTS            (0x80)
#define C_MAX_CYCLE_ELEMENTS          (1600)
#define C_MEM_NUMBER_CYCLE_BLOCKS     (13)//((U16)((U16)C_MAX_CYCLE_ELEMENTS/(U16)C_CYCLES_ERASE_BLOCK_SIZE) - 1)
#define C_MAX_CYCLE_MEMORY            (2048)
//#define C_MAX_CYCLE_BLOCK             (2)
#define C_MAX_CYCLE_BLOCK             (C_MEM_NUMBER_CYCLE_BLOCKS + 1)

#define C_API_DATA_FLASH_PARAM_SECTION_START      (U32) 0x00100800
#define C_API_DATA_FLASH_FACTORY_SECTION_START    (U32) 0x00101000
#define C_API_DATA_FLASH_MY_CYCLE_SECTION_START   (U32) 0x00101400
#define C_API_DATA_FLASH_CYCLES_SECTION_START     (U32) 0x00101800

extern void SRE_SafetyEnableDataFlashBlock2( void );
extern void SRE_SafetyDisableDataFlash( void );
extern ESafetyFailureCode FNE_u8DataFlashReadFailure ( void );
extern void SRE_ReturnFailureLog (U8 * lpu8Data);
extern void SRE_ReturnFailureLogRAM (U8 * lpu8Data);
extern U8 FNE_u8EraseParameterBlock( U8 lu8Block );
extern U8 FNE_u8EraseFactoryData( void );
extern U8 FNE_u8EraseMyCycleData( void );
extern U8 FNE_u8EraseCycleBlock( U8 lu8Block );
extern U8 FNE_u8ProgramParameterBlock( U8 lu8Block, U8* lpu8ParamRam );
extern U8 FNE_u8ProgramFactoryData( U8* lpu8ParamRam, U8 lu8Size);
extern U8 FNE_u8ProgramMyCycleData( U8* lpu8ParamRam, U8 lu8Size);
extern U8 FNE_u8ProgramCycleData( U32 lu32Address, U8* lpu8CyclesRam, U8 lu8Size);
extern U8 FNE_u8CheckCycleDataBlank( U32 lu32ParamRam );
extern U8 FNE_u8GetFlashDebugVar( void );
extern U8 FNE_u8EraseSkuData( void );
extern U8 FNE_u8ProgramSkuData( U8* lpu8ParamRam, U8 lu8Size);

/***********************************************************************
             Speed Sensor module functions with Safety Link
***********************************************************************/

// Type definition for speed sensor internal states.
typedef enum {
  E_SPEED_SENSOR_INIT  ,
  E_SPEED_SENSOR_VALID_SPEED
}ESpeedSensorState;

extern U32  FNE_u32SpeedSensorReadSpeed(void);
extern ESpeedSensorState FNE_eSpeedSensorReadState(void);
extern U32 FNE_u32SpeedSensorReadSpeedRaw(void);

/***********************************************************************
             Arc Sensor module functions with Safety Link
***********************************************************************/

extern U16 FNE_u16ArcSensorReadPulses (void );
extern void SRE_ArcSensorResetArc(void);
extern U32 FNE_u32SpeedSensorReadAverage(void);

/***********************************************************************
             Zero Cross module functions with Safety Link
***********************************************************************/
// Type definition for frequency value.
typedef enum {
  E_ZERO_CROSS_FREQUENCY_50_HZ,
  E_ZERO_CROSS_FREQUENCY_60_HZ,
  E_ZERO_CROSS_FREQUENCY_HI_AC,
  E_ZERO_CROSS_FREQUENCY_LOW_AC,
  E_ZERO_CROSS_FREQUENCY_UNDEFINED
}EZeroCrossFrequency;

// Type definition for frequency states.
typedef enum {
  E_ZERO_CROSS_FREQUENCY_ST_INIT,
  E_ZERO_CROSS_FREQUENCY_ST_PROCESS
}EZeroCrossFrequencyState;

extern EZeroCrossFrequency FNE_eZeroCrossReadFrequency(void);

/***********************************************************************
            Pressure Sensor module functions with Safety Link
***********************************************************************/
typedef enum {
   E_ST_PRESSURE_SENSOR_ERROR,
   E_ST_PRESSURE_SENSOR_NORMAL,
   E_ST_PRESSURE_SENSOR_OVERFLOW,
   E_ST_PRESSURE_SENSOR_SHORT_CIRCUIT,
   E_ST_PRESSURE_SENSOR_OPEN,
}E_PRESSURE_SENSOR_STATES;

extern U16 FNE_u16PressureSensorRead(void);
extern E_PRESSURE_SENSOR_STATES FNE_u8PressureSensorState(void);

/***********************************************************************
             Safety Digital Filter module functions with Safety Link
***********************************************************************/
#define C_FILTER_STATE_INIT     (U8)0
#define C_FILTER_STATE_PROCESS  (U8)1

#define C_FILTER_MIN_SAMPLES    (U8)3
#define C_FILTER_SCALE_FACTOR   (U16)128

struct stFilterParameters
  {
    U8 u8FilterState;
    U8 u8SampleCnt;
    U32 u32FilteredSignal;
    U32 u32LastFilteredSignal;
    U16 u16FilterCoef;
  };

extern void SRE_DigitalFilter(U32 lu32SignalValue, struct stFilterParameters *lpstFilterParam);
extern void SRE_InitFilter(struct stFilterParameters *lpstFilterParam, U16 lu16FilterCoef);
extern void SRE_SetFilterOrder(struct stFilterParameters *lpstFilterParam, U16 lu16FilterCoef);


/***********************************************************************
             Motor module functions with Safety Link
***********************************************************************/
enum {
  C_DIR_CCW, C_DIR_CW
};
extern void SRE_MotorSet( U8 lu8MotorDirSt, U16 lu16PowerPercentSet );
extern U8 FNE_u8GetMotorDir(void);
extern U16 FNE_u16GetMotorPercent(void);

/***********************************************************************
             UART driver functions with Safety Link
***********************************************************************/

/* ---- Mabe Comm Protocol ---- */
#define C_UPPER_SAFETY_RAM        (U8 *)0x00001800


/***********************************************************************
             ADC functions with Safety Link
***********************************************************************/

typedef enum {
  E_DUMMY = 0 ,
  E_KNOB_1 ,
  E_KNOB_2 ,
  E_KNOB_3 ,
  E_KNOB_4 ,
  E_KNOB_5 ,
  E_NULL
}EAdcSelection;

extern U16 FNE_u16GetAdcValue(   EAdcSelection leDeviceSelection  );
extern U16 FNE_u16ReadVoltageADC_Data (void );
extern U16 FNE_u16ReadCurrentSensorADC_Data(void);

/***********************************************************************
             Shifter functions with Safety Link
***********************************************************************/
// Mode shifter public or visible states
// Type definition for shifter interaction. It defines the possible shifter states.
typedef enum {
  E_SHIFTER_AGITATE ,
  E_SHIFTER_SPIN ,
  E_SHIFTER_IN_PROCESS,
  E_SHIFTER_ERROR
}EShifterStatus;

// Type definition for shifter interaction. It defines the possible shifter request.
typedef enum {
  E_SHIFTER_GO_TO_AGITATE,
  E_SHIFTER_GO_TO_SPIN
}EShifterRequestState;

typedef enum {
  E_SHIFTER_TYPE_ROTATIONAL = 0,
  E_SHIFTER_TYPE_THERMAL = 1
}EShifterType;


// Type definition for shifter interaction. It defines the possible shifter request.
typedef enum {
  E_MODE_SHIFTER_INTERNAL_ST_DONT_KNOW   ,
  E_MODE_SHIFTER_INTERNAL_ST_SPIN,
  E_MODE_SHIFTER_INTERNAL_ST_SPIN_DISENGAGE,
  E_MODE_SHIFTER_INTERNAL_ST_AGITATE,
  E_MODE_SHIFTER_INTERNAL_ST_AGITATE_DISENGAGE,
  E_MODE_SHIFTER_INTERNAL_ST_GOING_AGITATE,
  E_MODE_SHIFTER_INTERNAL_ST_GOING_SPIN,
  E_MODE_SHIFTER_INTERNAL_ST_WAIT,
  E_MODE_SHIFTER_INTERNAL_ST_CONFIRM_SWITCH,
  E_MODE_SHIFTER_INTERNAL_ST_SPIN_JITTER,
  E_MODE_SHIFTER_INTERNAL_ST_AGITATE_JITTER,
  E_MODE_SHIFTER_INTERNAL_ST_ERROR
}EModeShifterInternalState;

typedef enum {
  E_SHIFTER_DISANGAGE_SPIN_AGITATE,
  E_SHIFTER_DISANGAGE_AGITATE_SPIN,
  E_SHIFTER_ENGAGE_AGITATE,
  E_SHIFTER_ENGAGE_SPIN
}EShifterTransitionEngageState;

struct SJitterVar
  {
    U8  u8RepeatTimes;
    U8  u8OnTimeCCW;
    U8  u8OffTimeCCW;
    U8  u8OnTimeCW;
    U8  u8OffTimeCW;
    U8  u8PauseTime;
  };

extern void SRE_ShifterInit(EShifterType leShifterType, U8 lu8TimeToSpinSeconds, U8 lu8TimeToAgitateSeconds);
extern void SRE_ShifterMoveTo(EShifterRequestState leShifterRequestState);
extern EShifterStatus FNE_eShifterReadState(void);
extern void SRE_ShifterProcess(void);
extern void SRE_SetJitterParameters (EShifterTransitionEngageState leShifterTransitionEngageState, struct SJitterVar * lpsJitterPaarmeters);

extern EModeShifterInternalState FNE_GetModeShifterTargetState(void);

/***********************************************************************
             CRC functions with Safety Link
***********************************************************************/

extern U16 FNE_CalcCRC(U8* lpu8Buf, U16 lu16Len);
extern void SRE_SafetyPartNo(U8 *lpu8Array);

#define C_SAFETY_PART_NO_SIZE  (36)

/***********************************************************************
             Safety Relay functions with Safety Link
***********************************************************************/
// Type definition for safety relay interaction. It defines the possible safety relay states.
typedef enum {
  E_SAFETY_RELAY_OPENED  ,
  E_SAFETY_RELAY_CLOSED  ,
  E_SAFETY_RELAY_IN_PROCESS,
  E_SAFETY_RELAY_ERROR_TRIAC,
  E_SAFETY_RELAY_ERROR_RELAY
}ESafetyRelayStatus;

// Type definition for safety relay interaction. It defines the possible safety relay request.
typedef enum {
  E_SAFETY_RELAY_REQUEST_CLOSE  ,
  E_SAFETY_RELAY_REQUEST_OPEN
}ESafetyRelayRequestState;

extern ESafetyRelayStatus FNE_eSafetyRelayReadState(void);
extern void SRE_SafetyRelaySetState (ESafetyRelayRequestState leSafetyRelayRequestState);
extern ESafetyRelayStatus FNE_GetSafetyRelayRqst(void);
/***********************************************************************
             Refresh functions with Safety Link
***********************************************************************/

extern void SRE_RefreshRecircPump(U8 lu8LoadValue);
extern void SRE_RefreshDrainPump (U8 lu8LoadValue);
extern void SRE_RefreshColdValve (U8 lu8LoadValue);
extern void SRE_RefreshHotValve (U8 lu8LoadValue);
extern void SRE_RefreshD1Valve (U8 lu8LoadValue);
extern void SRE_RefreshD2Valve (U8 lu8LoadValue);
extern void SRE_RefreshLed01 (U8 lu8LoadValue);
extern void SRE_RefreshLed02 (U8 lu8LoadValue);
extern void SRE_RefreshLed03 (U8 lu8LoadValue);
extern void SRE_RefreshLed04 (U8 lu8LoadValue);
extern void SRE_RefreshLed05 (U8 lu8LoadValue);
extern void SRE_RefreshLed06 (U8 lu8LoadValue);
extern void SRE_RefreshLed07 (U8 lu8LoadValue);
extern void SRE_RefreshLed08 (U8 lu8LoadValue);
extern void SRE_RefreshLed09 (U8 lu8LoadValue);
extern void SRE_RefreshLed10 (U8 lu8LoadValue);
extern void SRE_RefreshLedHeartBeat (U8 lu8LoadValue);
extern void SRE_RefreshTestPoint (U8 lu8LoadValue);
extern U8 FNE_u8GetValveRelayRqst(void);
extern U8 FNE_u8DrainPumpOn(void);

/***********************************************************************
             Buzzer driver functions with Safety Link
***********************************************************************/
extern void SRE_BuzzerDriverSetToneFrequency(U32 lu32DesiredFrequencyHz);
extern void SRE_BuzzerDriverSetVolumeDutty(U8 lu8VolumeDutty);

/***********************************************************************
             Led driver functions with Safety Link
***********************************************************************/
// Type definition for led in DTC
typedef enum {
  // Digital UI
  E_LED_Z101,
  E_LED_Z103,
  E_LED_Z104,
  E_LED_Z105,
  E_LED_Z106,
  E_LED_Z107,
  E_LED_Z108,
  E_LED_Z109,
  E_LED_Z110,
  E_LED_Z111,
  E_LED_Z112,
  E_LED_Z113,
  E_LED_Z114,
  E_LED_Z115,
  E_LED_Z116,
  E_LED_Z117,
  E_LED_Z118,
  E_LED_Z119,
  E_LED_Z120,
  E_LED_Z121,
  E_LED_Z122,
  E_LED_Z123,
  E_LED_Z124,
  E_LED_Z125,
  E_LED_Z126,
  E_LED_Z127,
  E_LED_Z128,
  E_LED_Z129,
  E_LED_Z130,
  E_LED_Z131,
  E_LED_Z132,
  E_LED_Z133,
  E_LED_Z134,
  E_LED_Z135,
  E_LED_Z136,
  E_LED_Z137,
  E_LED_Z138,
  E_LED_Z139,
  E_LED_Z140,
  E_LED_Z141,
  E_LED_Z142,
  E_LED_Z143,
  E_LED_Z144,
  E_LED_Z145,
  E_LED_Z146,
  E_LED_Z147,
  E_LED_Z148,
  E_LED_Z149,
  E_LED_Z150,
  E_LED_Z151,
  E_LED_Z152,
  E_LED_Z153,
  E_LED_Z154,
  E_LED_Z155,
  E_LED_Z156,
  E_LED_Z157,
  E_LED_Z158,
  E_LED_Z159,
  E_LED_Z160,
  E_LED_Z161,
  E_LED_Z162,
  E_LED_Z163,
  E_LED_Z164,
  E_LED_Z165,
  E_LED_Z166,
  E_LED_Z167,
  E_LED_Z168,
  E_LED_Z169,
  E_LED_Z170,
  E_LED_Z171,
  E_LED_Z172,
  E_LED_Z173,
  E_LED_Z174,
  E_LED_Z175,
  E_LED_Z176,
  E_LED_Z177,
  E_LED_Z178,
  E_LED_Z179,
  // Knobs UI
  E_LED_Z401,
  E_LED_Z402,
  E_LED_Z403,
  E_LED_Z404,
  E_LED_Z405,
  E_LED_Z406,
  E_LED_Z407,
  E_LED_Z408,
  E_LED_Z409,
  E_LED_Z410,
}ELed;


typedef enum {
  E_INTENSITY_0 ,    // 0%
  E_INTENSITY_20 ,   // 20%
  E_INTENSITY_40 ,   // 40%
  E_INTENSITY_60 ,   // 60%
  E_INTENSITY_80 ,   // 80%
  E_INTENSITY_100   // 100%
}EDisplayIntensityLevel;

typedef enum {
  E_ENCODER_POSITION_00,
  E_ENCODER_POSITION_01,
  E_ENCODER_POSITION_02,
  E_ENCODER_POSITION_03,
  E_ENCODER_POSITION_04,
  E_ENCODER_POSITION_05,
  E_ENCODER_POSITION_06,
  E_ENCODER_POSITION_07,
  E_ENCODER_POSITION_08,
  E_ENCODER_POSITION_09,
  E_ENCODER_POSITION_10,
  E_ENCODER_POSITION_11,
  E_ENCODER_POSITION_12,
  E_ENCODER_POSITION_13,
  E_ENCODER_POSITION_14,
  E_ENCODER_POSITION_15
}EEncoderPosition;

typedef enum {
  E_UI_LOW_END,
  E_UI_HIGH_END
}EUserInterfaceType;

extern EUserInterfaceType FNE_eReadUserInterfaceType (void );
extern void SRE_eSetUserInterfaceType (EUserInterfaceType leUserInterfaceToSet );
extern void SRE_SetLed(ELed leLedToSet, U8 lu8ValueToSet);
extern void SRE_SetDisplayIntensity(EDisplayIntensityLevel leDisplayIntensityLevel);
extern void SRE_SetDisplayBuffer (U32* lpu32DisplayData);
extern U16 FNE_u16ReadButtonsStatus(void);
extern EEncoderPosition  FNE_eReadLowEndEncoderStatus(void);
extern EEncoderPosition  FNE_eReadHiEndEncoderStatus(void);

extern U8 FNE_u8UI_LowEndReadButtons(void);
extern EEncoderPosition FNE_UI_LowEndReadEncoderPosition(void);
extern void SRE_UI_LowEndSetLed(ELed leLedToSet, U8 lu8ValueToSet);


typedef enum {
  E_TRIAC_STATUS_UNKNOWN,
  E_TRIAC_STATUS_OK,
  E_TRIAC_STATUS_SHORT
}ETriacsStatus;

extern ETriacsStatus FNE_eGetTriacStatus(void);

extern void SRE_DebugDrainPump(U16 *lpu16Array);
extern U16 FNE_u16DebugPressureAdcValue(void);
extern void SRE_DebugSwitchOnDrainPump(U8 lu8Status);

typedef enum {
  E_TRIAC_ST_INIT                   = 0,
  E_TRIAC_ST_DELAY                  = 1,
  E_TRIAC_ST_INIT_AGITATION_PROCESS = 2,
  E_TRIAC_ST_SPIN_PROCESS           = 3,
  E_TRIAC_ST_FAIL                   = 4,
  E_TRIAC_ST_ACTIVATED              = 5,
  E_TRIAC_ST_PAUSE                  = 6,
}ECheckTriacState;

extern void SR_DebugVariables (U32 *lpu32Array);


extern void SRI_SafetyBreakpoint(void);
extern void SRI_BuzzerDriverInit (void );
extern void SRI_BuzzerDriverDisable(void);
extern U8 FNE_u8GetSelfTestStatus(void);
#endif

