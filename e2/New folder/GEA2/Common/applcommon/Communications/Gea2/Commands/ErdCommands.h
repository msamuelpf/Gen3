/*!
 * @file
 * @brief Definitions of GEA2 ERD commands
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef ERDCOMMMANDS_H
#define ERDCOMMMANDS_H

#include <stdint.h>

enum
{
   ErdCommand_ReadRequest = 0xF0,
   ErdCommand_ReadResponse = 0xF0,
   ErdCommand_WriteRequest = 0xF1,
   ErdCommand_WriteResponse = 0xF1,
   ErdCommand_SubscribeRequest = 0xF2,
   ErdCommand_SubscribeResponse = 0xF2,
   ErdCommand_UnsubscribeRequest = 0xF4,
   ErdCommand_UnsubscribeResponse = 0xF4,
   ErdCommand_SubscriptionListRequest = 0xF3,
   ErdCommand_SubscriptionListResponse = 0xF3,
   ErdCommand_Publish = 0xF5,
   ErdCommand_PublishAcknowledgement = 0xF5,
   ErdCommand_OpenLoopWriteRequest = 0xF6
};
typedef uint8_t ErdCommand_t;

#endif
