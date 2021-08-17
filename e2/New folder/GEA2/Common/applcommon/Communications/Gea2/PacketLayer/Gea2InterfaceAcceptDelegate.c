/*!
 * @file
 * @brief Implementation of GEA2 bus accept delegate API.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include "Gea2InterfaceAcceptDelegate.h"
#include "uassert.h"

void Gea2InterfaceAcceptDelegate_Init(Gea2InterfaceAcceptDelegate_t *delegate, void *context, Gea2InterfaceAcceptDelegateCallback_t callback)
{
   delegate->_private.context = context;
   delegate->_private.callback = callback;
}

bool Gea2InterfaceAcceptDelegate_CheckAccept(const Gea2InterfaceAcceptDelegate_t *delegate, const uint8_t address)
{
   if(delegate)
   {
      return delegate->_private.callback(delegate->_private.context, address);
   }
   else
   {
      return false;
   }
}
