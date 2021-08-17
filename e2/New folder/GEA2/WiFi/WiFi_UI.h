/*!
 * @file
 * @brief WiFi UI prototypes supporting status and ability to commission using the WiFi Button
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFI_UI_H
#define WIFI_UI_H

#include <WasherErds.h>

#include <stdint.h>
#include "I_DataSource.h"
#include "Timer.h"
#include "I_DigitalOutput.h"
#include "I_Event.h"

enum
{
   IconToggleInterval_ms = 500,  // support a 1 Hz blink indication.
   WiFiButtonHoldTime_ms = 3000, // disconnect WiFi if button hold time satisfied

   WiFiButtonRelease = 0,
   WiFiButtonPress = 1,
};

typedef bool WiFiButtonStatus_t;

typedef struct
{
   struct
   {
      I_DataSource_t *dataSource;
      I_DigitalOutput_t *iconLED;
      TimerModule_t *timerModule;

      bool iconLED_Status;
      Timer_t blinkTimer;
      Timer_t buttonHoldTimer;
      EventSubscription_t dataSourceChangeSubscription;
      EventSubscription_t WiFiButtonStatusChangeSubscription;
   } _private;
} WiFi_UI_t;

/*!
 * Initialization for the "UI" that controls commissioning
 * @param instance -- the UI
 * @param dataSource
 * @param timerModule
 * @param WiFiKeyStatusChange - event that indicates status of WIFI button.  Assumed to be released to start.
 * @param WiFi_IconLED - how to light the Icon
 */
void WiFi_UI_Init(
   WiFi_UI_t *instance,
   I_DataSource_t *dataSource,
   TimerModule_t *timerModule,
   I_Event_t *WiFiButtonStatusChange,
   I_DigitalOutput_t *WiFi_IconLED);

#endif
