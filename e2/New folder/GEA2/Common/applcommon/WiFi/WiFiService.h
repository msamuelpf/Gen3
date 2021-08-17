/*!
 * @file
 * @brief Service that presents a simplified interface to an embedded WiFi module and handles GEA2
 * traffic related to network configuration and state.
 *
 * This component accepts requests to connect, disconnect, or remain in the current state and
 * communicates a sanitized WiFi state back to the client.
 * - When a connect is requested, the service will immediately report a state of "connecting" and
 *   will walk the module through the process of finalizing the current connection and then going
 *   to AP mode so that a consumer can commission the device. Once the device has been successfully
 *   commissioned, the service will report a state of "connected". Note that the service will
 *   wait forever for the module to be successfully commissioned by a consumer unless the connection
 *   is canceled with a disconnect request.
 * - When a disconnect is requested, the service will immediately report a state of "disconnected"
 *   and will walk the module through the process of disconnecting.
 * - When no connection or disconnection is requested (or after a connection or disconnection has
 *   been completed) the service will continue to report the high level state of the module. For
 *   example, if the module disconnects and attempts to reconnect, the service will report that it
 *   is connecting.
 * - When a connection or disconnection is completed, the request is "consumed" and becomes a
 *   request to maintain the current state. This allows a request to be re-issued if, for example,
 *   the current connection is lost.
 *
 * Copyright GE Appliances - Confidential - All rights reserved.
 */

#ifndef WIFISERVICE_H
#define WIFISERVICE_H

#include <stdint.h>
#include "I_DataSource.h"
#include "I_Gea2MessageEndpoint.h"
#include "Timer.h"
#include "Fsm.h"
#include "WiFiNetworkState.h"
#include "WiFiServiceState.h"
#include "WiFiServiceRequest.h"

typedef struct
{
   struct
   {
      I_DataSource_t *dataSource;
      I_Gea2MessageEndpoint_t *messageEndpoint;
      TimerModule_t *timerModule;
      Timer_t pollTimer;
      Fsm_t fsm;
      EventSubscription_t messageReceivedSubscription;
      EventSubscription_t dataSourceSubscription;
      Erd_t requestErd;
      Erd_t stateErd;
      WiFiNetworkState_t wifiNetworkState;
   } _private;
} WiFiService_t;

extern void SetCommissioning(WiFiService_t *instance, WiFiNetworkState_t state);

extern void SetFieldTest(WiFiService_t *instance, uint8_t state);

/*!
 * Initialize a WiFi service.
 * @note The provided timer module should use a 1 msec tick in order to ensure proper timing.
 * @param instance The WiFi service.
 * @param dataSource The data source used to accept requests and communicate its state.
 * @param messageEndpoint Endpoint used to communicate with the WiFi module.
 * @param timerModule Millisecond timer module used to maintain time within the service.
 * @param serviceRequestErd ERD used to request a connection or disconnection.
 * @param serviceStateErd ERD used to communicate the service's state.
 */
void WiFiService_Init(
   WiFiService_t *instance,
   I_DataSource_t *dataSource,
   I_Gea2MessageEndpoint_t *messageEndpoint,
   TimerModule_t *timerModule,
   Erd_t serviceRequestErd, //! WiFiServiceRequest_t
   Erd_t serviceStateErd); //! WiFiServiceState_t

#endif
