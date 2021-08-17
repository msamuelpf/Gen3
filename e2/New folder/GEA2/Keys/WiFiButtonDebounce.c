/*!
 * @file
 * @brief Routines to sample and debounce the WiFi button.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "WiFiButtonDebounce.h"

#define DEBOUNCED_TYPE WiFiButtonStatus_t
#define DEBOUNCER_NAME WiFiButtonDebouncer
#define ACCESS_SPECIFIER extern
#include "DebouncerBuilder_Implementation.h"

static void WiFiButtonSampling(void *context)
{
   REINTERPRET(instance, context, WiFiButtonDebounce_t *);
   WiFiButtonStatus_t rawButtonStatus;

   Input_Read(instance->_private.WiFiButtonInput, &rawButtonStatus);
   if(WiFiButtonDebouncer_Process(&instance->_private.WiFiButtonDebouncer, rawButtonStatus))
   {
      instance->_private.debouncedWiFiButtonState = WiFiButtonDebouncer_GetDebounced(&instance->_private.WiFiButtonDebouncer);
      Event_Synchronous_Publish(&instance->_private.WiFiButtonStatusChangeEvent, &instance->_private.debouncedWiFiButtonState);
   }
}

static void Read(I_Input_t *_instance, void *value)
{
   REINTERPRET(instance, _instance, WiFiButtonDebounce_t *);
   REINTERPRET(result, value, WiFiButtonStatus_t *);

   *result = instance->_private.debouncedWiFiButtonState;
}

static I_Event_t * GetOnChangeEvent(I_Input_t *_instance)
{
   REINTERPRET(instance, _instance, WiFiButtonDebounce_t *);
   return &instance->_private.WiFiButtonStatusChangeEvent.interface;
}

static const I_Input_Api_t api =
   { NULL, Read, GetOnChangeEvent };

void WiFiButtonDebounce_Init(
   WiFiButtonDebounce_t *instance,
   TimerModule_t *timerModule,
   I_Input_t *WiFiButtonInput,
   TimerTicks_t channelSamplePeriodMsec,
   uint8_t debounceMaxCount)
{
   instance->interface.api = &api;

   instance->_private.debouncedWiFiButtonState = WiFiButtonRelease;
   instance->_private.WiFiButtonInput = WiFiButtonInput;
   Event_Synchronous_Init(&instance->_private.WiFiButtonStatusChangeEvent);

   WiFiButtonDebouncer_Init(&instance->_private.WiFiButtonDebouncer, WiFiButtonRelease, debounceMaxCount);
   TimerModule_StartPeriodic(
     timerModule,
      &instance->_private.sampleTimer,
      channelSamplePeriodMsec,
      WiFiButtonSampling,
      instance);
}
