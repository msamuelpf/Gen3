/*!
 * @file
 * @brief Simple finite state machine.
 *
 * This module does not implement all of UML state charts -- this was a conscious design decision to
 * drive simplicity.  In particular it eschews the Init signal and init pseudo-state in favor of
 * having a entry to a defined initial state at FSM init.  This allows the same pattern to be
 * implemented, but introduces fewer concepts.
 *
 * Quick Overview:
 *
 *    States
 *       States are modeled by functions.  The function for a state is invoked when a signal/event is
 *       sent to the state.  Note that a state only receives signals when it is the active/current state.
 *
 *    Signals
 *       Signals are sent to states to indicate what event occurred.  If any data is required, it will
 *       be accessible via void *data, but it is up to the receiving state to interpret the void *
 *       appropriately based on the received signal.
 *
 *       Note that signals can cause a transition, but they can also trigger state-dependent responses
 *       that leave the state machine in the same state.
 *
 *    Transitions
 *       Transitions are the means by which the current state changes.  During a transition, the current
 *       state is left and the new state is entered.  Prior to leaving the current state, the exit signal
 *       (FSM_EXIT) is sent.  Upon entry to the new state, the entry signal (FSM_ENTRY) is sent to the
 *       new state.
 *
 *    Initialization
 *       The current state is set during initialization.  At the end of initialization the entry signal
 *       (FSM_ENTRY) is sent to the initial state.
 *
 * Example:
 *    +---------+    Sig_3    +---------+
 *    | State_A <-------------+ State_C |
 *    +----+----+             +----^----+
 *         |      +---------+      |
 *         +------> State_B +------+
 *       Sig_1    +---------+    Sig_2
 *
 *    Consider the state machine shown above with three states and three transitions.
 *
 *    If the state machine is initialized to State B, the following signals will be sent:
 *       Entry -> State B
 *
 *    If the current state is A and Sig_1 is sent, the following signals will be sent:
 *       Sig_1 -> State A (transition is triggered)
 *       Exit -> State A
 *       Entry -> State B
 *
 *    If the current state is B and Sig_3 is sent, the following signals will be sent:
 *       Sig_3 -> State B (signal is ignored)
 *
 *    Sample Implementation:
 *       State functions that implement this state machine are given below:
 *
 *       static void State_A(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
 *       {
 *          switch(signal)
 *          {
 *             case FSM_ENTRY:
 *                // Entry actions
 *                break;
 *
 *             case Sig_1:
 *                Fsm_Transition(fsm, State_B);
 *                break;
 *
 *             case FSM_EXIT:
 *                // Exit actions
 *                break;
 *          }
 *       }
 *
 *       static void State_B(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
 *       {
 *          switch(signal)
 *          {
 *             case FSM_ENTRY:
 *                // Entry actions
 *                break;
 *
 *             case Sig_2:
 *                Fsm_Transition(fsm, State_C);
 *                break;
 *
 *             case FSM_EXIT:
 *                // Exit actions
 *                break;
 *          }
 *       }
 *
 *       static void State_C(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data)
 *       {
 *          switch(signal)
 *          {
 *             case FSM_ENTRY:
 *                // Entry actions
 *                break;
 *
 *             case Sig_3:
 *                Fsm_Transition(fsm, State_A);
 *                break;
 *
 *             case FSM_EXIT:
 *                // Exit actions
 *                break;
 *          }
 *       }
 *
 * @warning A transition must be the last action taken when handling a signal.  The result of an
 * action taken after a transition is implementation-defined.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef FSM_H
#define FSM_H

#include <stdint.h>

enum
{
   /*!
    * Entry signal sent upon entry to a state.
    */
   FSM_ENTRY,

   /*!
    * Exit signal sent upon exit from a state.
    */
   FSM_EXIT,

   /*!
    * Start of user-defined signals.  All user signals must have an integer value >= this.
    */
   FSM_USER_SIGNAL_START,

   Fsm_Entry = FSM_ENTRY,
   Fsm_Exit = FSM_EXIT,
   Fsm_UserSignalStart = FSM_USER_SIGNAL_START
};

/*!
 * Signal sent to an FSM state.
 */
typedef uint16_t FsmSignal_t;

struct Fsm_t;

/*!
 * FSM state.  Invoked when a signal is sent to the state.
 * @param fsm The FSM.
 * @param signal The signal being sent.
 * @param data Signal data being sent.
 */
typedef void (*FsmState_t)(struct Fsm_t *fsm, const FsmSignal_t signal, const void *data);

/*!
 * Finite state machine.  Struct members should be considered private.
 */
typedef struct Fsm_t
{
   FsmState_t currentState;
} Fsm_t;

/*!
 * Initialize an FSM.  The initial state will receive the entry signal with no data.
 * @pre fsm != NULL
 * @pre initialState != NULL
 * @param fsm The FSM.
 * @param initialState The initial state.
 */
void Fsm_Init(Fsm_t *fsm, FsmState_t initialState);

/*!
 * Send a signal to the current state.
 * @pre fsm != NULL
 * @param fsm The FSM.
 * @param signal The signal to send.
 * @param data Data sent along with the signal.
 */
void Fsm_SendSignal(Fsm_t *fsm, const FsmSignal_t signal, const void *data);

/*!
 * Transition the FSM from the current state to the target state.  The current state will receive
 * the exit signal with no data and the target state will receive the entry signal with no data.
 * The target state will become the new current state.
 * @pre fsm != NULL
 * @pre targetState != NULL
 * @param fsm The FSM.
 * @param targetState The target state.
 */
void Fsm_Transition(Fsm_t *fsm, FsmState_t targetState);

#endif
