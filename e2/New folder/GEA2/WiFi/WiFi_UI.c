/*!
 * @file
 * @brief File supports UI interface to display status of WiFi connectivity and commission it
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */
#include <stdbool.h>
#include "WiFi_UI.h"
#include "WiFiServiceRequest.h"
#include "utils.h"
#include "Constants_Binary.h"

static void ToggleWiFiIconLED(void *context)
{
   REINTERPRET(instance, context, WiFi_UI_t *);

   instance->_private.iconLED_Status = !instance->_private.iconLED_Status;
   DigitalOutput_Write(instance->_private.iconLED, instance->_private.iconLED_Status);
}

static void UpdateBlinkingLED(WiFi_UI_t *instance)
{
   if(!TimerModule_IsRunning(instance->_private.timerModule, &instance->_private.blinkTimer))
   {
      TimerModule_StartPeriodic(
         instance->_private.timerModule,
         &instance->_private.blinkTimer,
         IconToggleInterval_ms,
         ToggleWiFiIconLED,
         instance);
      instance->_private.iconLED_Status = ON;
      DigitalOutput_Write(instance->_private.iconLED, instance->_private.iconLED_Status);
   }
}

static void SetIconAccordingToState(WiFi_UI_t *instance, WiFiServiceState_t state)
{
   bool iconState = OFF;
   bool updateLED = false;

   switch(state)
   {
      case WiFiServiceState_Unknown:
         break;

      case WiFiServiceState_Connecting:
         UpdateBlinkingLED(instance);
         break;

      case WiFiServiceState_Connected:
         updateLED = true;
         iconState = ON;
         break;

      case WiFiServiceState_Disconnected:
         default:
         updateLED = true;
         break;
   }

   if(updateLED)
   {
      TimerModule_Stop(instance->_private.timerModule, &instance->_private.blinkTimer);
      DigitalOutput_Write(instance->_private.iconLED, iconState);
   }
}

static void ButtonHoldCallback(void *context)
{
   REINTERPRET(instance, context, WiFi_UI_t *);
   WiFiServiceRequest_t requestedWiFiState = WiFiServiceRequest_Disconnect;

   DataSource_Write(instance->_private.dataSource, Erd_WifiRequestedState, &requestedWiFiState);
}

static void WiFiButtonStatusChangeCallback(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFi_UI_t *);
   REINTERPRET(WiFiButtonStatus, _args, const WiFiButtonStatus_t *);
   WiFiServiceState_t currentWiFiState;
   WiFiServiceRequest_t requestedWiFiState;

   if(WiFiButtonRelease == *WiFiButtonStatus)
   {
      // stop the hold timer.
      TimerModule_Stop(instance->_private.timerModule, &instance->_private.buttonHoldTimer);
   }
   else
   {
      DataSource_Read(instance->_private.dataSource, Erd_WifiActualState, &currentWiFiState);
      if(WiFiServiceState_Disconnected == currentWiFiState)
      {
         requestedWiFiState = WiFiServiceRequest_Connect;
         DataSource_Write(instance->_private.dataSource, Erd_WifiRequestedState, &requestedWiFiState);
      }
      else
      {
         TimerModule_StartOneShot(
            instance->_private.timerModule,
            &instance->_private.buttonHoldTimer,
            WiFiButtonHoldTime_ms,
            ButtonHoldCallback,
            instance);
      }
   }
}

static void DataSourceChangeCallback(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFi_UI_t *);
   REINTERPRET(args, _args, const DataSourceOnDataChangeArgs_t *);

   if((Erd_t)Erd_WifiActualState == args->erd)
   {
      SetIconAccordingToState(instance, *((WiFiServiceState_t *)args->data));
   }
}

void WiFi_UI_Init(
   WiFi_UI_t *instance,
   I_DataSource_t *dataSource,
   TimerModule_t *timerModule,
   I_Event_t *WiFiButtonStatusChange,
   I_DigitalOutput_t *WiFi_IconLED)
{
   WiFiServiceState_t currentWiFiState;

   instance->_private.dataSource = dataSource;
   instance->_private.timerModule = timerModule;
   instance->_private.iconLED = WiFi_IconLED;

   EventSubscription_Init(&instance->_private.dataSourceChangeSubscription, instance, DataSourceChangeCallback);
   Event_Subscribe(dataSource->OnDataChange, &instance->_private.dataSourceChangeSubscription);

   EventSubscription_Init(&instance->_private.WiFiButtonStatusChangeSubscription, instance, WiFiButtonStatusChangeCallback);
   Event_Subscribe(WiFiButtonStatusChange, &instance->_private.WiFiButtonStatusChangeSubscription);

   DataSource_Read(instance->_private.dataSource, Erd_WifiActualState, &currentWiFiState);
   SetIconAccordingToState(instance, currentWiFiState);
}
