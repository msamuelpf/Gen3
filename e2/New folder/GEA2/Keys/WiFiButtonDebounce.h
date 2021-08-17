/*!
 * @file
 * @brief Prototypes for basic routines to sample and debounce the WiFi button.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFI_BUTTON_DEBOUNCE_H
#define WIFI_BUTTON_DEBOUNCE_H

#include "WiFi_UI.h"
#include "Timer.h"
#include "I_Input.h"
#include "Event_Synchronous.h"

#define DEBOUNCED_TYPE WiFiButtonStatus_t
#define DEBOUNCER_NAME WiFiButtonDebouncer
#define ACCESS_SPECIFIER extern
#include "DebouncerBuilder_Declaration.h"

typedef struct
{
   I_Input_t interface;

   struct
   {
      I_Input_t *WiFiButtonInput;

      Event_Synchronous_t WiFiButtonStatusChangeEvent;
      WiFiButtonStatus_t debouncedWiFiButtonState;
      WiFiButtonDebouncer_t WiFiButtonDebouncer;
      Timer_t sampleTimer;
   } _private;
} WiFiButtonDebounce_t;

/*!
 * Initialization routine for the WiFi Button Sampling
 * @param instance
 * @param timerModule
 * @param WiFiButtonInput
 * @param channelSamplePeriodMsec
 * @param debounceMaxCount
 */
void WiFiButtonDebounce_Init(
   WiFiButtonDebounce_t *instance,
   TimerModule_t *timerModule,
   I_Input_t *WiFiButtonInput,
   TimerTicks_t channelSamplePeriodMsec,
   uint8_t debounceMaxCount);

#endif
