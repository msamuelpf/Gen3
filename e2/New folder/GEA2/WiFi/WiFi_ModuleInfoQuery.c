/*!
 * @file
 * @brief Designed to facilitate reading the basic WiFi module information.
 *       At startup the service will periodically query the WiFi module for specific ERD information.
 *       Once the information has been received the service will go into an idle state.  The application
 *       can trigger a refresh information at any time.  If in the periodic mode, object will send the query
 *       and restart the periodic time.  If in Idle it will query the information one time.
 *       It will be assumed that any data written to the ERD being monitored implies the query no longer
 *       needs to happen.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "WiFi_ModuleInfoQuery.h"
#include "ErdCommands.h"
#include "utils.h"
#include "DataSourcePacketVerifier.h"
#include "DataSourcePacketParser.h"
#include "Constants_Time.h"
#include "../gea2Com.h"
#include "WasherErds.h"

enum
{
   Signal_Entry = FSM_ENTRY,
   Signal_Exit = FSM_EXIT,
   Signal_PollTimerExpired = FSM_USER_SIGNAL_START,
   Signal_QueryErdUpdated,

   WiFiModuleAddress = 0xBF,
   Retries = 2
};

static void MessageReceived(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFi_ModuleInfoQuery_t *);
   REINTERPRET(args, _args, const Gea2MessageEndpointOnReceiveArgs_t *);

   bool commandMatches = (bool)(Gea2Message_GetCommand(args->message) == ErdCommand_ReadResponse);
   bool sourceMatches = (bool)(Gea2Message_GetSource(args->message) == WiFiModuleAddress);
   bool validErdResponse = DataSourcePacketVerifier_Verify(
      Gea2Message_GetConstPayload(args->message),
      Gea2Message_GetPayloadLength(args->message),
      DataSourcePacketType_ReadResponse);

   if(commandMatches && sourceMatches && validErdResponse)
   {
      DataSourcePacketParser_t parser;
      Erd_t erd;
      uint8_t erdSize;
      const uint8_t *data;
      DataSourcePacketParser_Init(&parser, Gea2Message_GetConstPayload(args->message));

      if (parser._private.erdCount == 1)
      {
         if(DataSourcePacketParser_ExtractErdWithData(&parser, &erd, &erdSize, &data))
         {
            if(erd == instance->_private.queryErd)
            {
               // check the length and then write it....
               if(DataSource_Has(instance->_private.dataSource, erd)
                  && (erdSize == DataSource_SizeOf(instance->_private.dataSource, erd)))
               {
                  DataSource_Write(instance->_private.dataSource, erd, data);
               }
            }
            if(erd == Erd_WiFi_Status){
            	WiFiModuleStatus = (WiFi_Status_t)(*data);
            }
         }
      }
   }
}

static void SendErdReadRequest(WiFi_ModuleInfoQuery_t *instance)
{
   STACK_ALLOC_GEA2MESSAGE(message, 3);
   uint8_t *payload = Gea2Message_GetPayload(message);

   Gea2Message_SetCommand(message, ErdCommand_ReadRequest);
   Gea2Message_SetDestination(message, WiFiModuleAddress);

   payload[0] = 0x01;
   payload[1] = (uint8_t)(instance->_private.queryErd >> 8);
   payload[2] = (uint8_t)(instance->_private.queryErd & 0xFF);

   Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, message, Retries);
}

static void DataSourceUpdated(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFi_ModuleInfoQuery_t *);
   REINTERPRET(args, _args, const DataSourceOnDataChangeArgs_t *);

   if(args->erd == instance->_private.queryErd)
   {
      Fsm_SendSignal(&instance->_private.fsm, Signal_QueryErdUpdated, args->data);
   }
}

static void PollTimerExpired(void *context)
{
   REINTERPRET(instance, context, WiFi_ModuleInfoQuery_t *);
   Fsm_SendSignal(&instance->_private.fsm, Signal_PollTimerExpired, NULL);
}

static void StartQueryTimer(WiFi_ModuleInfoQuery_t *instance)
{
   TimerModule_StartPeriodic(
      instance->_private.timerModule,
      &instance->_private.pollTimer,
      instance->_private.pollRateTimerTicks,
      PollTimerExpired,
      instance);
}

static void State_PollErd(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);
static void State_Idle(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);

/*!
 * FSM state will periodically send GEA2 read request for designated ERD.
 * @param fsm
 * @param signal
 * @param data
 */
static void State_PollErd(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFi_ModuleInfoQuery_t *instance = CONTAINER_OF(WiFi_ModuleInfoQuery_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         StartQueryTimer(instance);
         break;

      case Signal_PollTimerExpired:
         SendErdReadRequest(instance);
         break;

      case Signal_QueryErdUpdated:
         Fsm_Transition(fsm, State_Idle);
         break;

      case Signal_Exit:
         TimerModule_Stop(instance->_private.timerModule, &instance->_private.pollTimer);
         break;
   }
}

/*!
 * Idle State - polling ERD no longer required after it has been initialized.
 * @param fsm
 * @param signal
 * @param data
 */
static void State_Idle(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   IGNORE(fsm);
   IGNORE(signal);
   IGNORE(data);
}

void WiFi_ModuleInfoQuery_RefreshErd(WiFi_ModuleInfoQuery_t *instance)
{
   if(TimerModule_IsRunning(instance->_private.timerModule, &instance->_private.pollTimer))
   {
      StartQueryTimer(instance);
   }
   SendErdReadRequest(instance);
}

void WiFi_ModuleInfoQuery_Init(
   WiFi_ModuleInfoQuery_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   Erd_t queryErd,
   TimerTicks_t pollRateTimerTicks)
{
   instance->_private.dataSource = dataSource;
   instance->_private.messageEndpoint = messageEndpoint;
   instance->_private.timerModule = timerModule;
   instance->_private.queryErd = queryErd;
   instance->_private.pollRateTimerTicks = pollRateTimerTicks;

   Fsm_Init(&instance->_private.fsm, State_PollErd);

   EventSubscription_Init(&instance->_private.dataSourceSubscription, instance, DataSourceUpdated);
   Event_Subscribe(dataSource->OnDataChange, &instance->_private.dataSourceSubscription);

   EventSubscription_Init(&instance->_private.messageReceivedSubscription, instance, MessageReceived);
   Event_Subscribe(Gea2MessageEndpoint_GetOnReceiveEvent(messageEndpoint), &instance->_private.messageReceivedSubscription);
}
