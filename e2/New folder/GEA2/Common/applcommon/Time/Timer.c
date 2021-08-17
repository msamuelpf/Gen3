/*!
 * @file
 * @brief Timer implementation.
 *
 * Copyright GE Appliances - Confidential - All rights reserved
 */

#include <stdbool.h>
#include <stddef.h>
#include "Timer.h"
#include "I_TimeSource.h"
#include "LinkedList.h"
#include "uassert.h"
#include "utils.h"

#define MAX_TICKS ((TimerTicks_t)(-1))

typedef struct
{
   TimerModule_t *module;
   TimerTicks_t expirationTicks;
   size_t index;
} FindInsertionIndexContext_t;

static bool ForEach_FindInsertionIndex(LinkedListNode_t *node, void *_context, const size_t index)
{
   REINTERPRET(context, _context, FindInsertionIndexContext_t *);
   REINTERPRET(timer, node, Timer_t *);

   if(timer->paused || timer->expired)
   {
      return true;
   }
   else
   {
      TimerTicks_t remainingTicksForCurrentTimer = timer->ticks.expiration - context->module->lastTicks;
      TimerTicks_t remainingTicksForTimerToInsert = context->expirationTicks - context->module->lastTicks;

      if(remainingTicksForCurrentTimer > remainingTicksForTimerToInsert)
      {
         context->index = index;
         return false;
      }

      return true;
   }
}

static void AddTimer(TimerModule_t *module, Timer_t *timer)
{
   FindInsertionIndexContext_t context;
   context.module = module;
   context.expirationTicks = timer->ticks.expiration;
   context.index = LinkedList_Count(&module->timers);
   LinkedList_ForEach(&module->timers, ForEach_FindInsertionIndex, &context);

   LinkedList_Insert(&module->timers, &timer->node, context.index);
}

static void RemoveTimer(TimerModule_t *module, Timer_t *timer)
{
   LinkedList_Remove(&module->timers, &timer->node);
}

void TimerModule_Stop(TimerModule_t *module, Timer_t *timer)
{
   RemoveTimer(module, timer);
}

static TimerTicks_t PendingTicks(TimerModule_t *module)
{
   TimeSourceTickCount_t newTickCount = TimeSource_GetTicks(module->timeSource);
   return (TimerTicks_t)((TimeSourceTickCount_t)(newTickCount - module->lastTimeSourceTickCount));
}

static void StartTimer(TimerModule_t *module, Timer_t *timer, const TimerTicks_t ticks, TimerCallback_t callback, void *context)
{
   TimerTicks_t timerDuration = TRUNCATE_UNSIGNED_ADDITION(ticks, PendingTicks(module), MAX_TICKS);

   TimerModule_Stop(module, timer);

   timer->startTicks = ticks;
   timer->ticks.expiration = module->lastTicks + timerDuration;
   timer->context = context;
   timer->callback = callback;
   timer->paused = false;
   timer->expired = false;

   AddTimer(module, timer);
}

void TimerModule_StartOneShot(TimerModule_t *module, Timer_t *timer, const TimerTicks_t ticks, TimerCallback_t callback, void *context)
{
   uassert(callback);

   timer->autoReload = false;
   StartTimer(module, timer, ticks, callback, context);
}

void TimerModule_StartPeriodic(TimerModule_t *module, Timer_t *timer, const TimerTicks_t ticks, TimerCallback_t callback, void *context)
{
   uassert(callback);

   timer->autoReload = true;
   StartTimer(module, timer, ticks, callback, context);
}

bool TimerModule_IsRunning(TimerModule_t *module, Timer_t *timer)
{
   return LinkedList_Contains(&module->timers, (const LinkedListNode_t *)timer);
}

void TimerModule_Pause(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      timer->ticks.pause = TimerModule_RemainingTicks(module, timer);
      timer->paused = true;
   }
}

void TimerModule_Resume(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      TimerTicks_t remainingTicks = TRUNCATE_UNSIGNED_ADDITION(timer->ticks.pause, PendingTicks(module), MAX_TICKS);
      timer->paused = false;

      RemoveTimer(module, timer);
      timer->ticks.expiration = module->lastTicks + remainingTicks;
      AddTimer(module, timer);
   }
}

bool TimerModule_IsPaused(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      return timer->paused;
   }
   else
   {
      return false;
   }
}

TimerTicks_t TimerModule_StartTicks(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      return timer->startTicks;
   }
   else
   {
      return 0;
   }
}

TimerTicks_t TimerModule_RemainingTicks(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      if(TimerModule_IsPaused(module, timer))
      {
         return timer->ticks.pause;
      }
      else
      {
         return timer->ticks.expiration - (module->lastTicks + PendingTicks(module));
      }
   }
   else
   {
      return 0;
   }
}

TimerTicks_t TimerModule_TicksSinceLastStarted(TimerModule_t *module, Timer_t *timer)
{
   uassert(!TimerModule_IsPaused(module, timer));
   return module->lastTicks - (timer->ticks.expiration - timer->startTicks) + PendingTicks(module);
}

TimerTicks_t TimerModule_ElapsedTicks(TimerModule_t *module, Timer_t *timer)
{
   if(TimerModule_IsRunning(module, timer))
   {
      return timer->startTicks - TimerModule_RemainingTicks(module, timer);
   }
   else
   {
      return 0;
   }
}

void TimerModule_Init(TimerModule_t *module, I_TimeSource_t *timeSource)
{
   module->timeSource = timeSource;
   module->lastTimeSourceTickCount = TimeSource_GetTicks(timeSource);
   LinkedList_Init(&module->timers);
}

typedef struct
{
   TimerModule_t *module;
   TimerTicks_t newTicks;
   TimerTicks_t lastTicks;
} UpdateExpiredContext_t;

static bool ForEach_UpdateExpired(LinkedListNode_t *node, void *_context, const size_t index)
{
   REINTERPRET(context, _context, UpdateExpiredContext_t *);
   REINTERPRET(timer, node, Timer_t *);

   IGNORE_ARG(index);

   if(!timer->paused)
   {
      TimerTicks_t elapsedTicks = (context->newTicks - context->lastTicks);
      TimerTicks_t remainingTicksForTimer = (timer->ticks.expiration - context->lastTicks);

      if(elapsedTicks >= remainingTicksForTimer)
      {
         timer->expired = true;
      }
   }

   return (bool)(timer->expired || timer->paused);
}

static void ExecuteTimer(TimerModule_t *module, Timer_t *timer)
{
   if(!timer->autoReload)
   {
      TimerModule_Stop(module, timer);
   }

   timer->callback(timer->context);

   // If the timer was stopped in the callback we should not restart the timer
   if(TimerModule_IsRunning(module, timer) && timer->autoReload)
   {
      RemoveTimer(module, timer);
      timer->expired = false;
      timer->ticks.expiration = module->lastTicks + timer->startTicks;
      AddTimer(module, timer);
   }
}

typedef struct
{
   TimerModule_t *module;
   bool executedTimer;
} ExecuteContext_t;

static bool ForEach_Execute(LinkedListNode_t *node, void *_context, const size_t index)
{
   REINTERPRET(timer, node, Timer_t *);
   REINTERPRET(context, _context, ExecuteContext_t *);

   IGNORE_ARG(index);

   if(!timer->paused && timer->expired)
   {
      ExecuteTimer(context->module, timer);
      context->executedTimer = true;
   }

   return (bool)!context->executedTimer;
}

bool TimerModule_Run(TimerModule_t *module)
{
   {
      TimeSourceTickCount_t newTickCount = TimeSource_GetTicks(module->timeSource);
      TimerTicks_t deltaTicks = (TimerTicks_t)((TimeSourceTickCount_t)(newTickCount - module->lastTimeSourceTickCount));
      TimerTicks_t newTicks = module->lastTicks + deltaTicks;

      UpdateExpiredContext_t context;
      context.newTicks = newTicks;
      context.module = module;
      context.lastTicks = module->lastTicks;

      module->lastTicks = newTicks;
      module->lastTimeSourceTickCount = newTickCount;

      LinkedList_ForEach(&module->timers, ForEach_UpdateExpired, &context);
   }

   {
      ExecuteContext_t context;
      context.module = module;
      context.executedTimer = false;

      LinkedList_ForEach(&module->timers, ForEach_Execute, &context);

      return context.executedTimer;
   }
}
