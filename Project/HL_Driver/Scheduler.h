/**
 * @file    <Scheduler.h>
 * @brief   **This is a simple Scheduler that can handle periodic tasks and Timers**
 *
 * The Scheduler implements a Round Robin Architecture without interruptions, the task are executing in a sequential
 * order following its taskId. The Timer can execute an special Task every X ms and be reprogramed at anytime.
 * 
 * Steps to create a periodic task in the scheduler:
 *  1) Init Scheduler
 *          tasks                   number of task to handle
 *          tick                    the time base in ms
 *          tasksCount;             internal task counter
 *          timeout;                the number of milliseconds the scheduler should run
 *          taskPtr                 Pointer to buffer for the TCB tasks
 *  2) Register Task
 *          period                  How often the task shoud run in ms
 *          elapsed                 the curent elapsed time
 *          initFunc                pointer to init task function (If there is no Init functions pass a Null pointer)
 *          taskFunc                pointer to task function
 *  3) Start task
 *          startFlag               flag to run task (Change the state to enable task execution in the Scheduler)
 *
 * @note    the maximum counting timeout posible is 2^32 
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "stdint.h"

#define IFX_INTPRIO_STM0_CMP0    10

typedef enum
{
  SCHD_INT_MODE_INACTIVE = 0,
  SCHD_INT_MODE_ACTIVE = 1
}SCHD_INT_MODES;

#define SCHD_INT_MODE            SCHD_INT_MODE_INACTIVE

/**
  * @brief    Task control block structure
  */
typedef struct _task
{
    uint32_t period;                /*!<How often the task shoud run in ms>*/
    uint32_t elapsed;               /*!<the curent elapsed time>*/
    uint8_t startFlag;              /*!<flag to run task>*/
    void (*initFunc)(void);         /*!<pointer to init task function>*/
    void (*taskFunc)(void);         /*!<pointer to task function>*/
    //Add more elements if required
}AppSched_Task;

/**
  * @brief   Timer control structure
  */
typedef struct _AppSched_Timer
{
    uint32_t timeout;               /*!< timer timeout to decrement and reload when the timer is re-started */
    uint32_t count;                  /*!< actual timer decrement count */
    uint8_t startFlag;              /*!< flag to start timer count */
    void(*callbackPtr)(void);       /*!< pointer to callback function function */
} AppSched_Timer;

/**
  * @brief   Scheduler control structure
  */
typedef struct _AppSched_Scheduler
{
    uint8_t tasks;                  /*!<number of task to handle>*/
    uint32_t tick;                  /*!<the time base in ms>*/
    uint8_t tasksCount;             /*!<internal task counter>*/
    uint32_t timeout;               /*!<the number of milliseconds the scheduler should run>*/
    AppSched_Task *taskPtr;         /*!<Pointer to buffer for the TCB tasks>*/
    uint8_t timers;                 /*!<number of software timer to use>*/
    AppSched_Timer *timerPtr;       /*!<Pointer to buffer timer array>*/
    /*Add more private elements if required*/
    uint8_t timerCount;             /*!<internal timer counter>*/
    uint32_t msCount;               /*!<miliseconds Count>*/
    uint8_t tickFlag;               /*!<tickflag indicator>*/
    uint8_t stm;                    /*!< module stm index >*/
} AppSched_Scheduler;

void AppSched_initScheduler( AppSched_Scheduler *scheduler );

uint8_t AppSched_registerTask( AppSched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period );

uint8_t AppSched_stopTask( AppSched_Scheduler *scheduler, uint8_t task );

uint8_t AppSched_startTask( AppSched_Scheduler *scheduler, uint8_t task );

uint8_t AppSched_periodTask( AppSched_Scheduler *scheduler, uint8_t task, uint32_t period );

void AppSched_startScheduler( AppSched_Scheduler *scheduler );


uint8_t AppSched_registerTimer( AppSched_Scheduler *scheduler, uint32_t timeout, void (*callbackPtr)(void) );

uint32_t AppSched_getTimer( AppSched_Scheduler *scheduler, uint8_t timer );

uint8_t AppSched_reloadTimer( AppSched_Scheduler *scheduler, uint8_t timer, uint32_t timeout );

uint8_t AppSched_startTimer( AppSched_Scheduler *scheduler, uint8_t timer );

uint8_t AppSched_stopTimer( AppSched_Scheduler *scheduler, uint8_t timer );

void AppSched_Callback_Tickflag_Core0(void);

void AppSched_Callback_Tickflag_Core1(void);

void AppSched_Callback_Tickflag_Core2(void);

#endif