/*!
 * @file
 * @brief This file contains typedefs that are used in SystemErds.h
 * Most of the structures defined here must be moved as the modules that use them are created.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef ERDTYPEDEFS_H
#define ERDTYPEDEFS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum{
	MODULE_OFF,
	AP_MODE,
	CONNECTING,
	CONNECTED,
	CONNECTED_BUT_OFF,
	SCANNING,
	RECONNECTING,
	START_UP,
	WAIT_COMMISSIONING,
	INVALID	= 255
}WiFi_Status_t; 

enum
{
   //ApplianceType_TranslatorBoard = 22,
	ApplianceType_TranslatorBoard = 2,
   ApplianceType_Unknown = 255
};

typedef uint8_t ApplianceType_t;

typedef struct {
   uint8_t hours;
   uint8_t minutes;
   uint8_t seconds;
}SystemTime_t;

typedef struct
{
   uint8_t buffer[6];
} WiFi_MAC_Id_t;

typedef struct
{
   uint8_t buffer[32];
} WiFi_SS_Id_t;

typedef struct
{
   uint8_t buffer[32];
} WiFi_Passphrase_t;

//typedef uint8_t WiFi_Status_t;

// this is a real ERD type but included as an example of how to support a swapped field...
typedef struct
{
   uint8_t u8_FilterType;
   uint8_t u8_OrderStatus;
   uint8_t u8_PercentRemaining;
   uint16_t U16DaysRemaining;
   uint16_t u16DaysOverDue;
   uint16_t u16DispensesOverDue;
}TS_EntityWaterFilterStatus;

typedef uint8_t ControlLockState_t;
typedef uint8_t TuneVolumeLevel_t;
typedef uint16_t RmsVoltagex100_t;
typedef uint8_t Personality_t;
typedef struct
{
   char filename[20];
   uint16_t lineNumber;
} Uassert_Data_t;
typedef uint16_t CurrentAmpsx100_t;
typedef uint32_t AppliancePersonality_t;
typedef uint8_t ServiceModeStateRequest_t;
typedef uint8_t ServiceModeState_t;
typedef uint8_t ImageValidBitmask_t;
typedef struct
{
   uint8_t criticalMajor;
   uint8_t criticalMinor;
   uint8_t major;
   uint8_t minor;
} Version_t;
typedef uint16_t TimeDisplayMinutes_t;
typedef struct
{
   uint8_t gitHash[20];
} GitHash_t;

typedef uint8_t RemoteMachineState_t;

typedef uint8_t RemoteMachineSubCycleState_t;
typedef uint8_t CycleId_t;
typedef uint8_t LaundryOperatingMode_t;
typedef uint16_t RemainingTime_t;
typedef uint16_t DelayWashTimeInMin_t;
typedef uint8_t LidSwitchState_t;
typedef uint8_t LidLockState_t;
typedef uint8_t SoilLevel_t;
typedef uint8_t RemoteWaterTemp_t;
typedef uint8_t RemoteSpinLevel_t;
typedef uint8_t RemoteRinseOption_t;
typedef uint8_t StainPreTreat_t;
typedef uint8_t WarmRinse_t;
typedef uint8_t DrainPumpState_t;
typedef uint8_t RecircPumpState_t;
typedef uint16_t AutoSoakTimeInMin_t;
typedef struct
{
   uint32_t timeStampOfLastEntry;
   uint32_t cycleCountOfLastEntry;
   uint32_t bulkFlushModeEntryCount;
} BulkFlushModeUsageProfileRecord_t;
typedef uint8_t ModeShiftActualState_t;
//***typedef int16_t MotorSpeed_t;
typedef uint16_t MotorSpeed_t;
typedef uint16_t Rpm_t;
typedef uint8_t WaterValveFunctionBitmap_t;
typedef uint8_t DeepFill_t;
typedef uint16_t Gallonsx100_t;
typedef uint32_t InchesOfWaterx1000_t;
typedef uint16_t SmartDispenseCycleCount_t;
typedef uint16_t WaterOnDemandActivationsCount_t;
typedef uint8_t RemoteStatus_t;
enum
{
   TimeSaverOption_Disable = 0,
   TimeSaverOption_Enable,
   TimeSaverOption_Max
};
typedef uint8_t TimeSaverOption_t;

typedef bool TimeSaverOptionAllowables_t[TimeSaverOption_Max];

enum
{
   SteamOption_Disable = 0,
   SteamOption_Enable,
   SteamOption_Max
};
typedef uint8_t SteamOption_t;

typedef bool SteamOptionAllowables_t[SteamOption_Max];

enum
{
   PrewashOption_Disable = 0,
   PrewashOption_Enable,
   PrewashOption_Max
};
typedef uint8_t PrewashOption_t;

typedef bool PrewashOptionAllowables_t[PrewashOption_Max];

typedef struct
{
   uint8_t triacRqst;
   uint8_t triacControlPercent_MSB;
   uint8_t triacControlPercent_LSB;
   uint8_t loadRqst;
} LoadsRequest_t;

typedef struct
{
   uint8_t safetyRelay;
   uint8_t lineFreq;
   uint8_t temperatureSensor;
   uint8_t lidSwitch;
   uint8_t lidLock;
   uint8_t modeShifter;
   uint8_t loadReserved;
} LoadsStatus_t;

typedef struct
{
   uint8_t code;
   uint8_t reserved_1;
   uint8_t reserved_2;
} FailureCode_t;

typedef struct
{
   uint16_t coldInches;
   uint16_t hotInches;
   uint16_t coldLiters;
   uint16_t hotLiters;
} WaterInletFlow_t;

typedef struct
{
   uint8_t arcVsTime_MSB;
   uint8_t arcVsTime_LSB;
   uint8_t slowdownTime;
} Torque_t;

typedef struct
{
   uint8_t limiterCnt;
   uint8_t arc_MSB;
   uint8_t arc_LSB;
   uint8_t spm;
} AgitationSupervisor_t;

typedef struct
{
   uint8_t fillTime;
   uint8_t agitationTime_MSB;
   uint8_t agitationTime_LSB;
   uint8_t drainTime;
   uint8_t spinTime;
   uint8_t reserved_1_MSB;
   uint8_t reserved_1_LSB;
   uint8_t reserved_2_MSB;
   uint8_t reserved_2_LSB;
   uint8_t reserved_3;
   uint8_t reserved_4;
} CycleStageTime_t;

typedef struct
{
   uint32_t drainFlowInches;
} DrainFlow_t;

typedef struct
{
   uint8_t jerkCnt;
   uint8_t jerkValue_Byte3;
   uint8_t jerkValue_Byte2;
   uint8_t jerkValue_Byte1;
   uint8_t jerkValue_Byte0;
   uint8_t jerkLimit_Byte3;
   uint8_t jerkLimit_Byte2;
   uint8_t jerkLimit_Byte1;
   uint8_t jerkLimit_Byte0;
   uint8_t sudsingCnt;
   uint8_t sensorHallFailureCnt;
} SpinSupervisor_t;

typedef struct
{
   uint16_t partNumber;
   uint8_t group;
   uint8_t revision;
} ParameterTable_t;
//
#endif
