/*!
 * @file
 * @brief Supports prototypes designed to facilitate reading the basic WiFi module information.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFI_MODULE_INFO_QUERY_H
#define WIFI_MODULE_INFO_QUERY_H

#include <stdint.h>
#include "I_DataSource.h"
#include "I_Gea2MessageEndpoint.h"
#include "Timer.h"
#include "Fsm.h"

typedef struct
{
   struct
   {
      I_DataSource_t *dataSource;
      I_Gea2MessageEndpoint_t *messageEndpoint;
      TimerModule_t *timerModule;
      Erd_t queryErd;
      TimerTicks_t pollRateTimerTicks;

      Fsm_t fsm;
      Timer_t pollTimer;
      EventSubscription_t dataSourceSubscription;
      EventSubscription_t messageReceivedSubscription;
   } _private;
} WiFi_ModuleInfoQuery_t;


/*!
 * Routine to call to force a refresh of WIFI info regardless of state or query timer
 * @param instance
 */
void WiFi_ModuleInfoQuery_RefreshErd(WiFi_ModuleInfoQuery_t *instance);


/*!
 * Initialization routine that will start state machine to read specific information from WiFi module.  Once information has been
 * received the state machine will enter an idle mode.
 * @param instance - object
 * @param dataSource - information will be stored here
 * @param messageEndpoint - used to send ERD query
 * @param timerModule - used to time periodic
 * @param queryErd - which ERD to be queried
 * @param pollRateTimerTicks - how often to check for ERD - passing in to allow staggering requests...
 *
 */
void WiFi_ModuleInfoQuery_Init(
   WiFi_ModuleInfoQuery_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   Erd_t queryErd,
   TimerTicks_t pollRateTimerTicks);

#endif
