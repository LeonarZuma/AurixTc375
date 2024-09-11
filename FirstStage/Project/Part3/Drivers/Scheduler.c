#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "Phase1.h"
#include "Scheduler.h"

/**
 * @brief   **calculates the current time passed on milliseconds **
 *
 *  calculates the current time passed on milliseconds
 *
 * @param   <void> no parameters to this function 
 *
 * @retval  None
 *
 */
static long milliseconds( void )
{
    return clock() / ( CLOCKS_PER_SEC / 1000 );
}

/**
 * @brief   ** Execute the init Functions for every registered task **
 *
 * Iterates between the registered task to execute its own Initialization Function, if there is no Init, just omits
 * that step
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 *
 * @retval  None
 *
 */
static void AppSched_execInitSchedulerTasks(AppSched_Scheduler *scheduler)
{
    for(scheduler->tasksCount = 0; scheduler->tasksCount < scheduler->tasks; scheduler->tasksCount++)
    {
        if (scheduler->taskPtr[scheduler->tasksCount].initFunc != NULL)
        {
            scheduler->taskPtr[scheduler->tasksCount].initFunc();              
        }
        else
        {
            /* Do nothing, this task has not init function*/
        }
    }
}

/**
 * @brief   ** Execute the Functions call for every registered task **
 *
 * Iterates between the registered task to execute its own Function once the periodicity has been reach, this are
 * the periodic task that has been previously 
 * 
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 *
 * @retval  None
 *
 */
static void AppSched_execFuncSchedulerTasks(AppSched_Scheduler *scheduler)
{
    for(scheduler->tasksCount = 0; scheduler->tasksCount < scheduler->tasks; scheduler->tasksCount++)
    {
        /* Check if the period of the current pointing task has been reach to execute this task */
        if((scheduler->msCount - scheduler->taskPtr[scheduler->tasksCount].elapsed) == scheduler->taskPtr[scheduler->tasksCount].period)
        {
            /* This is the new seed for a future called of the task  */
            scheduler->taskPtr[scheduler->tasksCount].elapsed = scheduler->msCount;
            
            AppSched_startTask(scheduler,scheduler->tasksCount + 1);
            scheduler->taskPtr[scheduler->tasksCount].taskFunc();
            /* Stop the run task after the complete code execution */
            AppSched_stopTask(scheduler,scheduler->tasksCount + 1);
        }
        else
        {
            /* Do nothing */
        }
    }
}

/**
 * @brief   ** Update the Timers Count Down to Execute the CallBack Function previously defined **
 *
 * Iterates between the registered task to execute its own Function once the periodicity has been reach, this are
 * the periodic task that has been previously 
 * 
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 *
 * @retval  None
 *
 */
static void AppSched_updSchedulerTimers(AppSched_Scheduler *scheduler)
{
    for(scheduler->timerCount = 0; scheduler->timerCount < scheduler->timers; scheduler->timerCount++)
    {
        /* Check if the current task is able to  been executing actually */
        if(scheduler->timerPtr[scheduler->timerCount].startFlag == TRUE)
        {
            /* Decrease timer counter */
            scheduler->timerPtr[scheduler->timerCount].count-= scheduler->tick;

            /* If the counter has reach the zero value execute the CallBackPtr */
            if(AppSched_getTimer(scheduler, scheduler->timerCount + 1) == 0)
            {
                scheduler->timerPtr[scheduler->timerCount].startFlag = FALSE;
                scheduler->timerPtr[scheduler->timerCount].callbackPtr();
            }
            else
            {
                /* Do nothing, just the count decrease has to been executed  */
            }
        }
        else
        {
            /* Do nothing */
        }
    }
}

/**
 * @brief   **Initialize the Scheduler Structure with the values passed as parameters**
 *
 * The function should initialize the scheduler structure with the values passed as parameters, the number of 
 * tasks to use, the tick value use a base time, the address of the array of task TCBs,and the amount of time the 
 * scheduler should run.   
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 *
 * @retval  None
 *
 * @note This is optional, just in case something very special needs to be take into account
 */
void AppSched_initScheduler(AppSched_Scheduler *scheduler)
{
    /* Set to zero the counters for Timer and Tasks */
    scheduler->tasksCount = 0;
    scheduler->timerCount = 0;
}

/**
 * @brief   **Provide a brief fucntion description (just one line)**
 *
 * The function will set the task TCB with the following parameters, the address of the function to hold the init 
 * routine for the given task and the address for the actual routine that will run as the task, plus the periodicity
 * in milliseconds of the task to register, if the task does not have an init routine a NULL parameter should be 
 * accepted by the function, another thing to validate is the Periodicity should not be less than the tick value and
 * always be multiple. The function shall return a Task ID which will be a number from 1 to n task registered if the
 *  operation was a success, otherwise, it will return zero.
 *
 * @param   <scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <*initPtr>[in] The direction of the task initialization routine
 * @param   <*initPtr>[in] The direction of the task code to schedule
 * @param   <period>[in] Periodicity in miliseconds of the task register
 * @param   <taskID>[out] This registers if the operation was success (1 to No. of tasks), otherwise 0 (NS)
 *
 * @retval  Describe the return value and its potential values, 
 *          if void type None
 *
 * @note The Initialization is Execute once Per function, if the task doesnot have an init routine, a null pointer
 *  should be accepted 
 */
uint8_t AppSched_registerTask(AppSched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period)
{
    uint8_t taskID = 0;

    /* validate if the Periodicity should not be less than the tick value and always be multiple */
    /* only one logic sequence needed, because the module == 0 is for multiples and values higher than period */
    /* I havent chekc if the value of period is equal to the tick counter */
    if((period % (scheduler->tick)) == 0)
    {
        /* lets check if the value is lower than the max task No.  */
        if(scheduler->tasksCount < (scheduler->tasks - 1))
        {
            /* we have to check how we are performing the pointer offset update we have to fit to the correct
            struct size */
            scheduler->taskPtr += 1;
            scheduler->tasksCount++;
        }
        else
        {
            scheduler->taskPtr = scheduler->taskPtr - scheduler->tasksCount;
            scheduler->tasksCount = 0;
        }
        /* set the TCB */
        /* the address of the function to hold the init routine for the given task */    
        scheduler->taskPtr->initFunc = initPtr;

        /* the address for the actual routine that will run as the task */
        scheduler->taskPtr->taskFunc = taskPtr;

        /* the periodicity in milliseconds of the task to register */
        scheduler->taskPtr->period = period;

        /* Assign the task id value */
        taskID = scheduler->tasksCount + 1;

    }
    else
    {
        /* Do nothing */
    }

    return taskID;
}

/**
 * @brief   **interface to stop any of the registered tasks from keeping running**
 *
 * By default after registering a task this will start running within the scheduler, this function can prevent it 
 * from being dispatched. The second parameter indicates the task to be stopped, which is a number from 1 to n task
 * registered. Number zero is forbidden. the function will return a TRUE if the task was stopped otherwise returns 
 * FALSE   
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <task>[in] The task id
 *
 * @retval  <succ_stop> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
uint8_t AppSched_stopTask(AppSched_Scheduler *scheduler, uint8_t task)
{
    uint8_t succStop = FALSE;
    /* if the taskid inserted its a valid number, the task could be succesfully stoped */
    if((task > 0) && (task <= scheduler->tasks))
    {
        succStop = TRUE;
        scheduler->taskPtr[task - 1].startFlag = FALSE;
    }
    else
    {
        /* Do nothing */
    }
    return succStop;
}

/**
 * @brief   **interface to start any of the registered tasks previously stopped**
 *
 * Once a task is stopped using the function Scheduler_StopTask, it can be active again using this function. The 
 * second parameter indicates the task to be started, which is a number from 1 to n task registered. Number zero is
 * forbidden. the function will return a TRUE if the task was started otherwise returns FALSE 
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <task>[in] The task id
 *
 * @retval  <succ_start> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
uint8_t AppSched_startTask(AppSched_Scheduler *scheduler, uint8_t task)
{
    uint8_t succStart = FALSE;

    /* if the taskid inserted its a valid number, the task could be succesfully stoped */
    if((task > 0) && (task <= scheduler->tasks))
    {
        succStart = TRUE;
        scheduler->taskPtr[task - 1].startFlag = TRUE;
    }
    else
    {
        /* Do nothing */
    }
    return succStart;
}


/**
 * @brief   **interface that will run the different tasks that have been registered**
 *
 * The new periodicity shall be a multiple of the tick value otherwise won’t be affected by the new period. The 
 * second parameter indicates the task to be started, which is a number from 1 to n task registered. Number zero is
 * forbidden. the function will return a TRUE if the task was correctly set otherwise returns FALSE. 
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <task>[in] The task id
 * @param   <period>[in] The new periodicity shall be a multiple of the tick value
 *
 * @retval  <succ_stop> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
uint8_t AppSched_periodTask(AppSched_Scheduler *scheduler, uint8_t task, uint32_t period)
{
    uint8_t succSetPeriod = FALSE;

    /* First check if the id task is valid */
    if((task > 0) && (task <= scheduler->tasks))
    {
        if((period % (scheduler->tick)) == 0)
        {
            scheduler->taskPtr[task - 1].period = period;
            succSetPeriod = TRUE;
        }
        else
        {
            /* Do nothing */
        }
    }
    else
    {
        /* Do nothing */
    }
    
    return succSetPeriod;
}

/**
 * @brief   **interface that will run the different tasks that have been registered**
 *
 * This is the function in charge of running the task init functions one single time and actual run each registered
 * task according to their periodicity in an infinite loop, the function will never return at least something wrong
 * happens, but this will be considered a malfunction. A timer will need to accomplish this purpose, for practical
 * reasons, we can use the clock functions and the milliseconds functions you can see down below
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 *
 * @retval  <succ_stop> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
void AppSched_startScheduler(AppSched_Scheduler *scheduler)
{
    long tickstart = milliseconds();

    /* the time in ms that has pasesed since the scheduler started */
    scheduler->msCount = 0;

    /* Call of the Initialization Functions */
    AppSched_execInitSchedulerTasks(scheduler);

    /* Infinite loop */
    while (scheduler->msCount < scheduler->timeout)
    {
        /* Check if the tick count has been reach */
        if((milliseconds() - tickstart) >= scheduler->tick)
        {
            /* This is the total time in ms that has passed since the scheduler started, to check the timeout condition */
            scheduler->msCount += scheduler->tick;
            tickstart = milliseconds();/*we get the actual ms again once we are inside the loop for the next execution */
            
            /* i've decide that the timers has a higher priority than tasks execution */
            AppSched_updSchedulerTimers(scheduler);

            /* Depending on the scheduler counter we have to execute the schedule tasks */
            /* check if the tickCount has reach the period of each task and enable the start flag of each task */
    
            /* a loop to check each existing task for enable it in case of being necessary */
            AppSched_execFuncSchedulerTasks(scheduler);
        }
        else
        {
            /* Do nothing */
        }
    }
}


/**
 * @brief   **Interface to register the timer to run**
 *
 * The function will register a new software timer to be updated on every tick, the timer shall count from a timeout
 * value down to zero, and once its count ended the timer will stop and execute the function callback registered 
 * (the third parameter is optional in case no callback is needed a NULL shall be passed). To successfully register
 * a timer the time in milliseconds should be larger than the actual tick and multiple. The function returns an ID 
 * which is a value from 1 to the number of timer registers in the scheduler, otherwise, it will return zero 
 * indicating the timer couldn't be registered. 
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <timeout>[in] The total count of the time in ms
 * @param   <*callbackPtr>[in] Callback function to execute after the end of the timer count
 *
 * @retval  <registerId> If the register was succesful returns the Id of the new register timer, it will return 
 *          zero indicating the timer couldn't be registered.
 * 
 */
uint8_t AppSched_registerTimer(AppSched_Scheduler *scheduler, uint32_t timeout, void (*callbackPtr)(void))
{
    uint8_t registerId = 0;

    /* To successfully register a timer the time in milliseconds should be larger than the actual tick and multiple */
    if (((timeout > scheduler->tick) && (timeout % scheduler->tick) == 0) && (scheduler->timerCount <= (scheduler->timers - 1)))
    {
    /* lets check if the value is lower than the max task No.  */
        
        scheduler->timerPtr[scheduler->timerCount].timeout = timeout;
        scheduler->timerPtr[scheduler->timerCount].count = (timeout / scheduler->tick);
        scheduler->timerPtr[scheduler->timerCount].callbackPtr = callbackPtr;
        scheduler->timerPtr[scheduler->timerCount].startFlag = FALSE;
        /* Increase the timerCount for the new added timer */
        scheduler->timerCount++;

        /* sucessfully register timer */
        registerId = scheduler->timerCount;
        /* if The timer count has reach the maximum number of possible counter reset to zero */
    }
    else
    {
        /* It cant be asigned the timeout as a valid time count */
    }
    return registerId;
}

/**
 * @brief   **Interface to get the current timer time**
 *
 * The function will return the current timer pending time in milliseconds, in case the timer does not been 
 * registered the function returns a zero value
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <timer>[in] The timer id to check the remaining time
 *
 * @retval  <pndgTime> current pending time, in case the timer not registerd, the function returns a zero value
 * 
 */
uint32_t AppSched_getTimer(AppSched_Scheduler *scheduler, uint8_t timer)
{
    uint32_t pndgTime = 0;
    
    if((timer <= scheduler->timers)  && (timer > 0))
    {
        pndgTime = scheduler->timerPtr[timer - 1].count;
    }
    else
    {
        /* the timer is not register */
    }
    return pndgTime;
}

/**
 * @brief   **Interface to reload a timer with a new period value**
 *
 * The timer will be reloaded with a new value in milliseconds it will also start the timer, the function does not
 * require the timer to stop first, but if the timer to reload has not been registered no action will be taken and
 * it will return a zero, otherwise return one as an indication of success.
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <timer>[in] The timer id to check the remaining time
 *
 * @retval  <succReload> FALSE in case the timer not registerd, otherwise return TRUE
 * 
 */
uint8_t AppSched_reloadTimer(AppSched_Scheduler *scheduler, uint8_t timer, uint32_t timeout)
{
    uint8_t succReload = FALSE;

    if((timer <= scheduler->timers)  && (timer > 0))
    {
        scheduler->timerPtr[timer - 1].timeout = timeout;
        scheduler->timerPtr[timer - 1].count = timeout;
        /* Set the start Flag to ensure the timer will start after the reload */
        scheduler->timerPtr[timer - 1].startFlag = TRUE;
        /* Succesfull operation set TRUE the return value */
        succReload = TRUE;
    }
    else
    {
        /* the timer is not register */
    }

    return succReload;
}

/**
 * @brief   **Interface to start the timer count**
 *
 * By default the timer count does not start when the timer is registered, it is necessary to call this function, 
 * the actual timer decrement count is carried out during each tick occurrence. The function will also serve as a 
 * mechanism of restart the timer from its timeout. If the timer to start has not been registered no action will be
 * taken and it will return a zero, otherwise return one as an indication of success.
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <timer>[in] The timer id to check the remaining time
 *
 * @retval  <succStart> FALSE in case the timer not registerd, otherwise return TRUE
 * 
 */
uint8_t AppSched_startTimer(AppSched_Scheduler *scheduler, uint8_t timer)
{
    uint8_t succStart = FALSE;
    /* Calling the reload function because its essencially the same logic */
    succStart = AppSched_reloadTimer(scheduler, timer, scheduler->timerPtr[timer - 1].timeout);

    return succStart;
}

/**
 * @brief   **Interface to start the timer count**
 *
 * The function will indicate the timer should not be decremented during each tick occurrence.  If the timer to stop
 * has not been registered no action will be taken and it will return a zero, otherwise return one as an indication
 * of success.
 *
 * @param   <AppSched_Scheduler>[in] This contains the Scheduler setting up parameters
 * @param   <timer>[in] The timer id to check the remaining time
 *
 * @retval  <succStop> FALSE in case the timer not registerd, otherwise return TRUE
 * 
 */
uint8_t AppSched_stopTimer(AppSched_Scheduler *scheduler, uint8_t timer)
{
    uint8_t succStop = FALSE;

    if((timer <= scheduler->timers)  && (timer > 0))
    {
        /* Set the start Flag to ensure the timer will start after the reload */
        scheduler->timerPtr[timer - 1].startFlag = FALSE;
        /* Succesfull operation set TRUE the return value */
        succStop = TRUE;
    }
    else
    {
        /* the timer is not register, so dont */
    }

    return succStop;
}