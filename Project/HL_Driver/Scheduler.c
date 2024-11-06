/**
 * @file    <Scheduler.c>
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
#include <stdint.h>
#include "Ifx_Types.h"
#include "IfxStm.h"
#include "Scheduler.h"

#ifdef TESSY

    #include "Tessy.h"

#endif

/*Global variable to configure the STM0 Cmp0*/
static IfxStm_CompareConfig Stm_Cmp_Config0;
static IfxStm_CompareConfig Stm_Cmp_Config1;
static IfxStm_CompareConfig Stm_Cmp_Config2;

static AppSched_Scheduler *intScheduler0 = NULL;
static AppSched_Scheduler *intScheduler1 = NULL;
static AppSched_Scheduler *intScheduler2 = NULL;

#if (SCHD_INT_MODE)
/**
 * @brief   **calculates the current time passed on milliseconds **
 *
 *  calculates the current time passed on milliseconds
 *
 * @param   void no parameters to this function 
 *
 * @retval  None
 *
 */
static long milliseconds( void )
{
    return IfxStm_get( &MODULE_STM0 );
}
#endif

/**
 * @brief   ** Execute the init Functions for every registered task **
 *
 * Iterates between the registered task to execute its own Initialization Function, if there is no Init, just omits
 * that step
 *
 * @param[in]   scheduler This contains the Scheduler setting up parameters
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
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
            
            //AppSched_startTask(scheduler,scheduler->tasksCount + 1);
            scheduler->taskPtr[scheduler->tasksCount].taskFunc();
            /* Stop the run task after the complete code execution */
            //AppSched_stopTask(scheduler,scheduler->tasksCount + 1);
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
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

    switch (scheduler->stm)
    {
        case 0:
            intScheduler0 = scheduler;
            IfxStm_initCompareConfig( &Stm_Cmp_Config0 );
            Stm_Cmp_Config0.ticks = scheduler->tick;
            Stm_Cmp_Config0.comparator = IfxStm_Comparator_0;
            Stm_Cmp_Config0.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
            Stm_Cmp_Config0.triggerPriority = IFX_INTPRIO_STM0_CMP0;
            Stm_Cmp_Config0.typeOfService = IfxSrc_Tos_cpu0;
            /*Configure the comparator to se for 500ms and enable its corresponding interrupt
            * using its corresponding Service Request Node (SRN) */
            IfxStm_initCompare( scheduler->moduleStm, &Stm_Cmp_Config0 );
            break;
        case 1:
            intScheduler1 = scheduler;
            IfxStm_initCompareConfig( &Stm_Cmp_Config1 );
            Stm_Cmp_Config1.ticks = scheduler->tick;
            Stm_Cmp_Config1.comparator = IfxStm_Comparator_0;
            Stm_Cmp_Config1.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
            Stm_Cmp_Config1.triggerPriority = IFX_INTPRIO_STM0_CMP0;
            Stm_Cmp_Config1.typeOfService = IfxSrc_Tos_cpu1;
            /*Configure the comparator to se for 500ms and enable its corresponding interrupt
            * using its corresponding Service Request Node (SRN) */
            IfxStm_initCompare( scheduler->moduleStm, &Stm_Cmp_Config1 );
            break;
        case 2:
            intScheduler2 = scheduler;
            IfxStm_initCompareConfig( &Stm_Cmp_Config2 );
            Stm_Cmp_Config2.ticks = scheduler->tick;
            Stm_Cmp_Config2.comparator = IfxStm_Comparator_0;
            Stm_Cmp_Config2.comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
            Stm_Cmp_Config2.triggerPriority = IFX_INTPRIO_STM0_CMP0;
            Stm_Cmp_Config2.typeOfService = IfxSrc_Tos_cpu2;
            /*Configure the comparator to se for 500ms and enable its corresponding interrupt
            * using its corresponding Service Request Node (SRN) */
            IfxStm_initCompare( scheduler->moduleStm, &Stm_Cmp_Config2 );
            break;
        default:
            break;
    }

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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   initPtr The direction of the task initialization routine
 * @param[in]   taskPtr The direction of the task code to schedule
 * @param[in]   period Periodicity in miliseconds of the task register
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
    if(((period % (scheduler->tick)) == 0) && (scheduler->tasksCount < scheduler->tasks))
    {
        /* lets check if the value is lower than the max task No.  */
        /* we have to check how we are performing the pointer offset update we have to fit to the correct
        struct size */
        scheduler->tasksCount++;
        taskID = scheduler->tasksCount;

        /* set the TCB */
        /* the address of the function to hold the init routine for the given task */    
        scheduler->taskPtr[taskID - 1].initFunc = initPtr;

        /* the address for the actual routine that will run as the task */
        scheduler->taskPtr[taskID - 1].taskFunc = taskPtr;

        /* the periodicity in milliseconds of the task to register */
        scheduler->taskPtr[taskID - 1].period = period;

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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   task The task id
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   task The task id
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   task The task id
 * @param[in]   period The new periodicity shall be a multiple of the tick value
 *
 * @retval  <succ_stop> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
uint8_t AppSched_periodTask(AppSched_Scheduler *scheduler, uint8_t task, uint32_t period)
{
    uint8_t succSetPeriod = FALSE;

    /* First check if the id task is valid */
    if((task > 0) && (task <= scheduler->tasks) && ((period % (scheduler->tick)) == 0))
    {
        scheduler->taskPtr[task - 1].period = period;
        scheduler->taskPtr[task - 1].elapsed = scheduler->msCount;
        succSetPeriod = TRUE;
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 *
 * @retval  <succ_stop> TRUE if was succesfully stoped, FALSE if it wasnt
 * 
 */
void AppSched_startScheduler(AppSched_Scheduler *scheduler)
{

    /* the time in ms that has pasesed since the scheduler started */
    scheduler->msCount = 0;

    /* Call of the Initialization Functions */
    AppSched_execInitSchedulerTasks(scheduler);

    /* Infinite loop */
    #ifndef TESSY
        while (TRUE)
    #else
        (scheduler->msCount < scheduler->timeout)
    #endif
    {
        /* Check if the tick count has been reach */
        #ifdef SCHD_INT_MODE
            if(scheduler->tickFlag == TRUE)
        #else 
            if((milliseconds() - tickstart) >= scheduler->tick)
        #endif
        {
            scheduler->tickFlag = FALSE;
            /* This is the total time in ms that has passed since the scheduler started, to check the timeout condition */
            scheduler->msCount += scheduler->tick;
            
            
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   timeout The total count of the time in ms
 * @param[in]   callbackPtr Callback function to execute after the end of the timer count
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
        scheduler->timerPtr[scheduler->timerCount].count = timeout;
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   timer The timer id to check the remaining time
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   timer The timer id to check the remaining time
 * @param[in]   timeout remaining time
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   timer The timer id to check the remaining time
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
 * @param[in]   scheduler This contains the Scheduler setting up parameters
 * @param[in]   timer The timer id to check the remaining time
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

IFX_INTERRUPT( Isr_Stm0_Cmp0, 0, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    intScheduler0->tickFlag = TRUE;
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( intScheduler0->moduleStm, Stm_Cmp_Config0.comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( intScheduler0->moduleStm, Stm_Cmp_Config0.comparator, Stm_Cmp_Config0.ticks );
}

IFX_INTERRUPT( Isr_Stm1_Cmp0, 1, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    intScheduler1->tickFlag = TRUE;
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( intScheduler1->moduleStm, Stm_Cmp_Config1.comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( intScheduler1->moduleStm, Stm_Cmp_Config1.comparator, Stm_Cmp_Config1.ticks );
}

IFX_INTERRUPT( Isr_Stm2_Cmp0, 2, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    intScheduler2->tickFlag = TRUE;
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( intScheduler2->moduleStm, Stm_Cmp_Config2.comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( intScheduler2->moduleStm, Stm_Cmp_Config2.comparator, Stm_Cmp_Config2.ticks );
}