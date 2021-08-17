/*!
 * @file
 * @brief Delegate for determining whether a GEA2 bus should accept a message with a given address.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef GEA2INTERFACEACCEPTDELEGATE_H
#define GEA2INTERFACEACCEPTDELEGATE_H

#include <stdbool.h>
#include <stdint.h>

/*!
 * Delegate invoked when a GEA2 bus is determining whether to "accept" (ie: ACK and then process) a received
 * message.
 * @param context Context provided during initialization.
 * @param address Destination address of the received message.
 * @return Return true if the message should be accepted, false otherwise.
 */
typedef bool (*Gea2InterfaceAcceptDelegateCallback_t)(void *context, const uint8_t address);

/*!
 * Accept delegate.  Struct members should be considered private.
 */
typedef struct
{
   struct
   {
      void *context;
      Gea2InterfaceAcceptDelegateCallback_t callback;
   } _private;
} Gea2InterfaceAcceptDelegate_t;

/*!
 * Initialize an accept delegate.  The context and callback will be populated.
 * @pre delegate != NULL
 * @pre callback != NULL
 * @param delegate The accept delegate.
 * @param context Callback context.
 * @param callback The callback.
 */
void Gea2InterfaceAcceptDelegate_Init(Gea2InterfaceAcceptDelegate_t *delegate, void *context, Gea2InterfaceAcceptDelegateCallback_t callback);

/*!
 * Check whether to accept a message by invoking the callback and returning the result.  The delegate
 * may be NULL.
 * @param delegate The accept delegate.
 * @param address The destination address to check.
 * @return Returns the result of the callback.
 */bool Gea2InterfaceAcceptDelegate_CheckAccept(const Gea2InterfaceAcceptDelegate_t *delegate, const uint8_t address);

#endif
