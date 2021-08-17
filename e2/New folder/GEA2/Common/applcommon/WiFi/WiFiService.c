/*!
 * @file
 * @brief WiFi service implementation.
 *
 * On initialization, the service attempts to read the initial state of the WiFi module.
 * Either before reading the initial state or after having read the initial state, the
 * service accepts requests to connect or disconnect.
 *
 * In order to service a connect request, the service must first ensure that the module
 * is off to ensure that a state transition to AP mode is allowed. Once off, the service
 * will request that the module go to AP mode until it is connected. Although most of these
 * requests will be redundant, these extra requests to AP mode are not a problem because
 * the WiFi module will remain in AP mode or the connecting state even if AP mode is again
 * requested. Issuing these redundant requests is a simple way to ensure that the WiFi
 * module makes it to AP mode and initiates the commissioning process.
 *
 * In order to service a disconnect request, the service simply requests that the module
 * go off until it can be confirmed to be off.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#include "WiFiService.h"
#include "ErdCommands.h"
#include "utils.h"
#include "DataSourcePacketVerifier.h"
#include "DataSourcePacketParser.h"
#include "Constants_Time.h"

enum
{
   Signal_Entry = FSM_ENTRY,
   Signal_Exit = FSM_EXIT,
   Signal_PollTimerExpired = FSM_USER_SIGNAL_START,
   Signal_NetworkStateUpdated,
   Signal_RequestMade,

   WiFiModuleAddress = 0xBF,
   WiFiModuleNetworkStateErd = 0x6003,
   WiFiModuleFieldStateErd = 0x600D,
   FastPollRate = 5 * MSEC_PER_SEC,
   SlowPollRate = 30 * MSEC_PER_SEC,

   Retries = 2
};

static void UpdateActualNetworkState(WiFiService_t *instance, WiFiServiceState_t state)
{
   DataSource_Write(
      instance->_private.dataSource,
      instance->_private.stateErd,
      &state);
}

static void PollTimerExpired(void *context)
{
   REINTERPRET(instance, context, WiFiService_t *);
   Fsm_SendSignal(&instance->_private.fsm, Signal_PollTimerExpired, NULL);
}

static void ArmPollTimer(WiFiService_t *instance, TimerTicks_t ticks)
{
   TimerModule_StartPeriodic(
      instance->_private.timerModule,
      &instance->_private.pollTimer,
      ticks,
      PollTimerExpired,
      instance);
}

static void ReadNetworkState(WiFiService_t *instance)
{
   STACK_ALLOC_GEA2MESSAGE(message, 3);
   uint8_t *payload = Gea2Message_GetPayload(message);

   Gea2Message_SetCommand(message, ErdCommand_ReadRequest);
   Gea2Message_SetDestination(message, WiFiModuleAddress);

   payload[0] = 0x01;
   payload[1] = WiFiModuleNetworkStateErd >> 8;
   payload[2] = WiFiModuleNetworkStateErd & 0xFF;

   Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, message, Retries);
}

static void WriteNetworkState(WiFiService_t *instance, WiFiNetworkState_t state)
{
   STACK_ALLOC_GEA2MESSAGE(message, 5);
   uint8_t *payload = Gea2Message_GetPayload(message);

   Gea2Message_SetCommand(message, ErdCommand_WriteRequest);
   Gea2Message_SetDestination(message, WiFiModuleAddress);

   payload[0] = 0x01;
   payload[1] = WiFiModuleNetworkStateErd >> 8;
   payload[2] = WiFiModuleNetworkStateErd & 0xFF;
   payload[3] = 0x01;
   payload[4] = state;

   Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, message, Retries);
}

void SetCommissioning(WiFiService_t *instance, WiFiNetworkState_t state)
{
	WriteNetworkState(instance, state);
}

static void WriteFieldState(WiFiService_t *instance, uint8_t state)
{
   STACK_ALLOC_GEA2MESSAGE(message, 5);
   uint8_t *payload = Gea2Message_GetPayload(message);

   Gea2Message_SetCommand(message, ErdCommand_WriteRequest);
   Gea2Message_SetDestination(message, WiFiModuleAddress);

   payload[0] = 0x01;
   payload[1] = WiFiModuleFieldStateErd >> 8;
   payload[2] = WiFiModuleFieldStateErd & 0xFF;
   payload[3] = 0x01;
   payload[4] = state;

   Gea2MessageEndpoint_Send(instance->_private.messageEndpoint, message, Retries);
}

void SetFieldTest(WiFiService_t *instance, uint8_t state)
{
	WriteFieldState(instance, state);
}

static void DataSourceUpdated(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFiService_t *);
   REINTERPRET(args, _args, const DataSourceOnDataChangeArgs_t *);

   if(args->erd == instance->_private.requestErd)
   {
      Fsm_SendSignal(&instance->_private.fsm, Signal_RequestMade, args->data);
   }
}

static void MessageReceived(void *context, const void *_args)
{
   REINTERPRET(instance, context, WiFiService_t *);
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

      while(DataSourcePacketParser_ExtractErdWithData(&parser, &erd, &erdSize, &data))
      {
         if(erd == WiFiModuleNetworkStateErd)
         {
            instance->_private.wifiNetworkState = *(const WiFiNetworkState_t *)data;
            Fsm_SendSignal(&instance->_private.fsm, Signal_NetworkStateUpdated, NULL);
         }
      }
   }
}

static void SetServiceState(WiFiService_t *instance, WiFiServiceState_t state)
{
   DataSource_Write(instance->_private.dataSource, instance->_private.stateErd, &state);
}

static void SetServiceRequest(WiFiService_t *instance, WiFiServiceRequest_t request)
{
   DataSource_Write(instance->_private.dataSource, instance->_private.requestErd, &request);
}

static void UpdateServiceStateForIdle(WiFiService_t *instance)
{
   WiFiServiceState_t state;

   switch(instance->_private.wifiNetworkState)
   {
      case WiFiNetworkState_Connecting:
         case WiFiNetworkState_ApMode:
         case WiFiNetworkState_Reconnecting:
         state = WiFiServiceState_Connecting;
         break;

      case WiFiNetworkState_Off:
         case WiFiNetworkState_Connected_Off:
         state = WiFiServiceState_Disconnected;
         break;

      default:
         state = WiFiServiceState_Connected;
         break;
   }

   SetServiceState(instance, state);
}

static void State_ReadInitialState(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);
static void State_Idle(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);
static void State_PrepareToConnect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);
static void State_Connect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);
static void State_Disconnect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);

static void State_ReadInitialState(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFiService_t *instance = CONTAINER_OF(WiFiService_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         UpdateActualNetworkState(instance, WiFiServiceState_Unknown);
         ArmPollTimer(instance, FastPollRate);
         break;

      case Signal_PollTimerExpired:
         ReadNetworkState(instance);
         break;

      case Signal_RequestMade:
         switch(*(const WiFiServiceRequest_t *)data)
         {
            case WiFiServiceRequest_Connect:
               Fsm_Transition(fsm, State_PrepareToConnect);
               break;

            case WiFiServiceRequest_Disconnect:
               Fsm_Transition(fsm, State_Disconnect);
               break;
         }
         break;

      case Signal_NetworkStateUpdated:
         Fsm_Transition(fsm, State_Idle);
         break;
   }
}

static void State_Idle(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFiService_t *instance = CONTAINER_OF(WiFiService_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         SetServiceRequest(instance, WiFiServiceRequest_RemainInCurrentState);
         UpdateServiceStateForIdle(instance);
         ArmPollTimer(instance, SlowPollRate);
         break;

      case Signal_NetworkStateUpdated:
         UpdateServiceStateForIdle(instance);
         break;

      case Signal_RequestMade:
         switch(*(const WiFiServiceRequest_t *)data)
         {
            case WiFiServiceRequest_Connect:
               Fsm_Transition(fsm, State_PrepareToConnect);
               break;

            case WiFiServiceRequest_Disconnect:
               Fsm_Transition(fsm, State_Disconnect);
               break;
         }
         break;

      case Signal_PollTimerExpired:
         ReadNetworkState(instance);
         break;
   }
}

static void State_PrepareToConnect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFiService_t *instance = CONTAINER_OF(WiFiService_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         SetServiceState(instance, WiFiServiceState_Connecting);
         ArmPollTimer(instance, FastPollRate);
         break;

      case Signal_NetworkStateUpdated:
         if(instance->_private.wifiNetworkState == WiFiNetworkState_Off)
         {
            Fsm_Transition(fsm, State_Connect);
         }
         break;

      case Signal_RequestMade:
         switch(*(const WiFiServiceRequest_t *)data)
         {
            case WiFiServiceRequest_Disconnect:
               Fsm_Transition(fsm, State_Disconnect);
               break;
         }
         break;

      case Signal_PollTimerExpired:
         WriteNetworkState(instance, WiFiNetworkState_Off);
         ReadNetworkState(instance);
         break;
   }
}

static void State_Connect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFiService_t *instance = CONTAINER_OF(WiFiService_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         SetServiceState(instance, WiFiServiceState_Connecting);
         ArmPollTimer(instance, FastPollRate);
         break;

      case Signal_NetworkStateUpdated:
         if(instance->_private.wifiNetworkState == WiFiNetworkState_Connected)
         {
            Fsm_Transition(fsm, State_Idle);
         }
         break;

      case Signal_RequestMade:
         switch(*(const WiFiServiceRequest_t *)data)
         {
            case WiFiServiceRequest_Disconnect:
               Fsm_Transition(fsm, State_Disconnect);
               break;
         }
         break;

      case Signal_PollTimerExpired:
         WriteNetworkState(instance, WiFiNetworkState_ApMode);
         ReadNetworkState(instance);
         break;
   }
}

static void State_Disconnect(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   WiFiService_t *instance = CONTAINER_OF(WiFiService_t, _private.fsm, fsm);

   switch(signal)
   {
      case Signal_Entry:
         SetServiceState(instance, WiFiServiceState_Disconnected);
         ArmPollTimer(instance, FastPollRate);
         break;

      case Signal_NetworkStateUpdated:
         if(instance->_private.wifiNetworkState == WiFiNetworkState_Off)
         {
            Fsm_Transition(fsm, State_Idle);
         }
         break;

      case Signal_RequestMade:
         switch(*(const WiFiServiceRequest_t *)data)
         {
            case WiFiServiceRequest_Connect:
               Fsm_Transition(fsm, State_Connect);
               break;
         }
         break;

      case Signal_PollTimerExpired:
         WriteNetworkState(instance, WiFiNetworkState_Off);
         ReadNetworkState(instance);
         break;
   }
}

void WiFiService_Init(
   WiFiService_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   Erd_t serviceRequestErd,
   Erd_t serviceStateErd)
{
   instance->_private.dataSource = dataSource;
   instance->_private.stateErd = serviceStateErd;
   instance->_private.requestErd = serviceRequestErd;
   instance->_private.timerModule = timerModule;
   instance->_private.messageEndpoint = messageEndpoint;

   Fsm_Init(&instance->_private.fsm, State_ReadInitialState);

   EventSubscription_Init(&instance->_private.dataSourceSubscription, instance, DataSourceUpdated);
   Event_Subscribe(dataSource->OnDataChange, &instance->_private.dataSourceSubscription);

   EventSubscription_Init(&instance->_private.messageReceivedSubscription, instance, MessageReceived);
   Event_Subscribe(Gea2MessageEndpoint_GetOnReceiveEvent(messageEndpoint), &instance->_private.messageReceivedSubscription);
}
