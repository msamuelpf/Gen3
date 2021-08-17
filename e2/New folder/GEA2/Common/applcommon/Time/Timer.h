/*!
 * @file
 * @brief Simple timer library.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "I_TimeSource.h"
#include "LinkedList.h"

/*!
 * Timer duration/tick count.
 */
typedef uint32_t TimerTicks_t;

/*!
 * Callback invoked when a timer expires.
 * @param context Callback context.
 */
typedef void (*TimerCallback_t)(void *context);

/*!
 * Timer definition.  Struct members should be considered private.
 */
typedef struct
{
   LinkedListNode_t node;
   TimerCallback_t callback;
   void *context;
   TimerTicks_t startTicks;
   union
   {
      TimerTicks_t expiration;
      TimerTicks_t pause;
   } ticks;
   bool autoReload :1;
   bool paused :1;
   bool expired :1;
} Timer_t;

/*!
 * Timer module.  Manages running timers.  Struct members should be considered private.
 */
typedef struct
{
   I_TimeSource_t *timeSource;
   LinkedList_t timers;
   TimerTicks_t lastTicks;
   TimeSourceTickCount_t lastTimeSourceTickCount;
} TimerModule_t;

/*!
 * Initialize a timer module.
 * @pre module != NULL
 * @pre timeSource != NULL
 * @param module The timer module.
 * @param timeSource Time source used to handle timing.
 */
void TimerModule_Init(TimerModule_t *module, I_TimeSource_t *timeSource);

/*!
 * Start a one shot timer.
 * @pre module != NULL
 * @pre timer != NULL
 * @pre callback != NULL
 * @param module Timer module in which to start the timer.
 * @param timer Timer to start.
 * @param ticks Tick duration until expiration.
 * @param callback Callback to invoke on expiration.
 * @param context Callback context.
 */
void TimerModule_StartOneShot(TimerModule_t *module, Timer_t *timer, const TimerTicks_t ticks, TimerCallback_t callback, void *context);

/*!
 * Start a periodic timer.
 * @pre module != NULL
 * @pre timer != NULL
 * @pre callback != NULL
 * @param module Timer module in which to start the timer.
 * @param timer Timer to start.
 * @param ticks Tick duration until expiration.
 * @param callback Callback to invoke on expiration.
 * @param context Callback context.
 */
void TimerModule_StartPeriodic(TimerModule_t *module, Timer_t *timer, const TimerTicks_t ticks, TimerCallback_t callback, void *context);

/*!
 * Stop a timer.
 * @param module Timer module in which to stop the timer.
 * @param timer Timer to stop.
 */
void TimerModule_Stop(TimerModule_t *module, Timer_t *timer);

/*!
 * Determine whether a timer is running.
 * @param module Timer module in which to check for a running timer.
 * @param timer The timer.
 * @return True if the timer is running, false otherwise.
 */
bool TimerModule_IsRunning(TimerModule_t *module, Timer_t *timer);

/*!
 * Pause a timer.
 * @param module Timer module in which to pause the timer.
 * @param timer Timer to pause.
 */
void TimerModule_Pause(TimerModule_t *module, Timer_t *timer);

/*!
 * Resume a timer.
 * @param module Timer module in which to resume the timer.
 * @param timer Timer to resume.
 */
void TimerModule_Resume(TimerModule_t *module, Timer_t *timer);

/*!
 * Determine whether a timer is paused.
 * @param module Timer module in which to check for a paused timer.
 * @param timer The timer to check paused or not.
 * @return True if the timer is paused, false otherwise.
 */
bool TimerModule_IsPaused(TimerModule_t *module, Timer_t *timer);

/*!
 * Get the number of ticks that a timer was started with.
 * @param module Timer module that contains the running timer.
 * @param timer The timer.
 * @return The starting ticks for the timer.  If the timer is not running 0 is returned.
 */
TimerTicks_t TimerModule_StartTicks(TimerModule_t *module, Timer_t *timer);

/*!
 * Get the ticks remaining until expiration of a running timer.
 * @param module Timer module that contains the running timer.
 * @param timer The timer.
 * @return The ticks remaining until expiration.  If the timer is not running 0 is returned.
 */
TimerTicks_t TimerModule_RemainingTicks(TimerModule_t *module, Timer_t *timer);

/*!
 * Get the number of ticks that have elapsed since starting a running timer.
 * @note This will never exceed the starting tick count.
 * @param module Timer module that contains the running timer.
 * @param timer The timer.
 * @return The ticks elapsed since start.  If the timer is not running 0 is returned.
 */
TimerTicks_t TimerModule_ElapsedTicks(TimerModule_t *module, Timer_t *timer);

/*!
 * Get the number of ticks since the timer was last started.
 * @pre Timer must have been started previously.
 * @pre !IsPaused(timer)
 * @note The timer does not have to be running.
 * @note If the timer was paused this will not be accurate.
 * @param module Timer module that timer was started in.
 * @param timer The timer.
 * @return The number of ticks since the timer was last started.
 */
TimerTicks_t TimerModule_TicksSinceLastStarted(TimerModule_t *module, Timer_t *timer);

/*!
 * Run a timer module.  Causes at most one timer to expire.
 * @param module The timer module.
 * @return True if a timer expired, false otherwise.
 */
bool TimerModule_Run(TimerModule_t *module);

#endif
