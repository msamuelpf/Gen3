/*!
 * @file
 * @brief Simple FSM implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stddef.h>
#include "Fsm.h"
#include "uassert.h"

void Fsm_SendSignal(Fsm_t *fsm, const FsmSignal_t signal, const void *data)
{
   fsm->currentState(fsm, signal, data);
}

void Fsm_Init(Fsm_t *fsm, FsmState_t initialState)
{
   uassert(initialState);

   fsm->currentState = initialState;
   Fsm_SendSignal(fsm, FSM_ENTRY, NULL);
}

void Fsm_Transition(Fsm_t *fsm, FsmState_t targetState)
{
   uassert(targetState);

   Fsm_SendSignal(fsm, FSM_EXIT, NULL);
   fsm->currentState = targetState;
   Fsm_SendSignal(fsm, FSM_ENTRY, NULL);
}
