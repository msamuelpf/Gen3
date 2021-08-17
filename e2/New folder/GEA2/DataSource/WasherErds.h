/*!
 * @file
 * @brief System-wide ERD definitions.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include <WasherErdTypedefs.h>

#include <stdint.h>
#include "ModelNumber.h"
#include "SerialNumber.h"
#include "WiFiServiceState.h"

#ifndef SYSTEMERDS_H
#define SYSTEMERDS_H

#ifndef EndiannessFree
#define EndiannessFree false
#endif

#ifndef EndiannessSwap
#define EndiannessSwap true
#endif

#ifndef InputAndInputOutputEnable
#define InputAndInputOutputEnable 1
#endif

#ifndef InputAndInputOutputDisable
#define InputAndInputOutputDisable 0
#endif

#ifndef OutputEnable
#define OutputEnable 1
#endif

#ifndef OutputDisable
#define OutputDisable 0
#endif

// XMACRO used to define ERDs and data types for the system. Updating this table will automatically update the application data source parameters
// ENTRY(Enumeration, ERD ID, DataType, EndiannessAware, inputAndInputOutputAbility, OutputAbility)

// NOTE: Due to using linear search algorithms  - if speed becomes an issue - put the most used ERDs near the top of the list to improve throughput
// we can go to a binary search if speed is still an issue after that.
// for now arranging in ascending order so it is possible to use binary search later.
#define ERD_TABLE(ENTRY) \
   ENTRY(Erd_ModelNumber,                       			0x0001,  ModelNumber_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SerialNumber,                      			0x0002,  SerialNumber_t,                        EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SoftwareControlUiLocked,                 0x0004,  ControlLockState_t,                    EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SystemTime,                        			0x0005,  SystemTime_t,                          EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_ApplianceType,                     			0x0008,  ApplianceType_t,                       EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Public_SystemVoltageRmsx100,             0x000E,  RmsVoltagex100_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Public_SystemCurrentAmpsx100,            0x0034,  CurrentAmpsx100_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_CycleCount,                              0x008E,  uint32_t,                              EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_BrandId,                                 0x0099,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable)\
   ENTRY(Erd_ApplicationVersionErd,                   0x0100,  Version_t,                             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WaterFilterStatus,                 			0x1009,  TS_EntityWaterFilterStatus,            EndiannessSwap,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_MachineState,              				0x2000,  RemoteMachineState_t,                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_SubCycleState,              			0x2001,  RemoteMachineSubCycleState_t,          EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_EocState,                   			0x2002,  bool,                                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LaundryRemainingCycleTimeInSeconds,			0x2007,  RemainingTime_t,                       EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LaundryCurrentSelectedCycle,       			0x200A,  CycleId_t,                             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LaundryPublicOperatingMode,        			0x200E,  LaundryOperatingMode_t,                EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_DelayStartTimeInMinutesPublic,     			0x2010,  DelayWashTimeInMin_t,                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MC_LidSwitchStatePublic,           			0x2012,  LidSwitchState_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MC_LidLockActualStatePublic,       			0x2013,  LidLockState_t,                        EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_UI_OptionSoilLevel,                			0x2015,  SoilLevel_t,                           EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_WashTemperatureLevel,       			0x2016,  RemoteWaterTemp_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_SpinTimeLevel,              			0x2017,  RemoteSpinLevel_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Remote_RinseOption,                			0x2018,  RemoteRinseOption_t,                   EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_EocAlarmNotifier,                  			0x201D,  bool,                                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_UI_OptionStainPretreat,            			0x2024,  StainPreTreat_t,                       EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_UI_OptionWarmRinse,                			0x2025,  WarmRinse_t,                           EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MC_DrainPumpActualStatePublic,     			0x2026,  DrainPumpState_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Public_RecirculationPumpState,     			0x2027,  RecircPumpState_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_UI_OptionUserSetAutoSoakTimeInMinutes,	  0x2028,  AutoSoakTimeInMin_t,                   EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_BulkFlushModeUsageProfileRecord,   			0x2029,  BulkFlushModeUsageProfileRecord_t,     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Drive_ModeShiftActualStatePublic,  			0x202A,  ModeShiftActualState_t,                EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Drive_MotorTargetBasketSpeed,      			0x202B,  MotorSpeed_t,                          EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Drive_SpeedSensorBasket,           			0x202C,  Rpm_t,                                 EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MC_WaterValvesActualStatePublic,   			0x202D,  WaterValveFunctionBitmap_t,            EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_UI_OptionDeepFillPublic,           			0x202E,  DeepFill_t,                            EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MC_CurrentTubInGallonsx100Public,  			0x202F,  Gallonsx100_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MaxWaterVolumeGallonsx100,         			0x2030,  Gallonsx100_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MaxWaterLevelInchesOfWaterx1000,   			0x2031,  InchesOfWaterx1000_t,                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MaxSpinSpeedRpm,                         0x2032,  Rpm_t,                                 EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SmartDispenseUsageProfileRecordSmall,		0x2033,  SmartDispenseCycleCount_t,             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SmartDispenseUsageProfileRecordMedium,		0x2034,  SmartDispenseCycleCount_t,             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SmartDispenseUsageProfileRecordLarge,    0x2035,  SmartDispenseCycleCount_t,             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SmartDispenseUsageProfileRecordAuto,     0x2036,  SmartDispenseCycleCount_t,             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WaterOnDemandActivationsUsageProfileRecord,	0x2037,  WaterOnDemandActivationsCount_t,		EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_RemoteSetDelayStartTime,                 0x2038,  DelayWashTimeInMin_t,                  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_RemoteStatus,                            0x2039,  RemoteStatus_t,                        EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_RemoteStopCycleCommand,                  0x2040,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_TimeSaverOptionRequest,                  0x2054,  TimeSaverOption_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_TimeSaverOption,                         0x2055,  TimeSaverOption_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_TimeSaverOptionAllowable,                0x2056,  TimeSaverOptionAllowables_t,           EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SteamOptionRequest,                      0x2057,  SteamOption_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SteamOption,                             0x2058,  SteamOption_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SteamOptionAllowables,                   0x2059,  SteamOptionAllowables_t,               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_PrewashOptionRequest,                    0x205A,  PrewashOption_t,                       EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_PrewashOption,                           0x205B,  PrewashOption_t,                       EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_PrewashOptionAllowables,                 0x205C,  PrewashOptionAllowables_t,             EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WaterLevelSelection,                     0x2F00,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SensedWaterLevelSelection,               0x2F01,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_ManualSelection,                         0x2F02,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SoilLevelSelection,                      0x2F03,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_TemperatureLevelSelection,               0x2F04,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SpinLevelSelection,                      0x2F05,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WasherOptions,                           0x2F06,  uint16_t,                              EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LoadsRequest,                            0x2F07,  LoadsRequest_t,                        EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LoadsStatus,                             0x2F08,  LoadsStatus_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_FailureCode,                             0x2F09,  FailureCode_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_CycleFunction,                           0x2F0A,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_RunApplicationState,                     0x2F0B,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_MainState,                               0x2F0C,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_RemoteEnable,                            0x2F0D,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WaterInletFlow,                          0x2F0E,  WaterInletFlow_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_Torque,                                  0x2F0F,  Torque_t,                              EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_AgitationSupervisor,                     0x2F10,  AgitationSupervisor_t,                 EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_CycleStageTime,                          0x2F11,  CycleStageTime_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_DrainFlow,                               0x2F12,  DrainFlow_t,                           EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_SpinSupervisor,                          0x2F13,  SpinSupervisor_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_LidOpenWhileRunningCycle,                0x2F14,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_ParameterTable,                          0x2F15,  ParameterTable_t,                      EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WiFi_MAC_Id,                       			0x6000,  WiFi_MAC_Id_t,                         EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WiFi_SS_Id,                        			0x6001,  WiFi_SS_Id_t,                          EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WiFi_Passphrase,                   			0x6002,  WiFi_Passphrase_t,                     EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WiFi_Status,		                   			  0x6003,  WiFi_Status_t,                     	  EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_HeartbeatServer,                         0x600D,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WifiActualState,                   			0xE000,  WiFiServiceState_t,                    EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_WifiRequestedState,                			0xE001,  WiFiServiceState_t,                    EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \
   ENTRY(Erd_BookEndToPreventPaddingIssue,      			0xFFFF,  uint8_t,                               EndiannessFree,   InputAndInputOutputDisable, OutputDisable) \

#define ERD_EXPAND_AS_ENUM(ErdEnum, Number, DataType, EndiannessAware, inputAndInputOutputAbility, OutputAbility) ErdEnum = Number,

#define ERD_EXPAND_AS_DATASOURCE_RAM_ENTRIES(ErdEnum, Number, DataType, EndiannessAware, InputAndInputOutputAbility, OutputAbility) \
       { ErdEnum, sizeof(DataType)},

enum
{
   ERD_TABLE(ERD_EXPAND_AS_ENUM)
   ENUM_DUMMY_USED_FOR_XMACRO_COMPILE_WARNING};

// ******* note below will not work with any negative numbers specified as the "Number"

// the following #define and XMACRO expansion prevent ERD ID duplication in E2Studio.
// The enumeration created should not be used for anything because there is no meaning.
// If a ERD ID is used more than once in the ERD_TABLE this
// enumeration will cause the following error in the compile.
// redefinition of enumerator "ERD_DUPLICATE0x????"
//#define EXPAND_AS_DUPLICATE_PREVENTION_ENUM(ErdEnum, Number, DataType, EndiannessAware, inputAndInputOutputAbility, OutputAbility) ERD_DUPLICATE ## Number,
//
//enum
//{
//   ERD_TABLE(EXPAND_AS_DUPLICATE_PREVENTION_ENUM)
//   ERD_DUPLICATE_PREVENTION_DUMMY_USED_FOR_XMACRO_COMPILE_WARNING
//};

#endif
