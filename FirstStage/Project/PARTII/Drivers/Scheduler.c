#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "Phase1.h"
#include "Scheduler.h"

/**
 * @brief   **calculates the current time passed on milliseconds **
 *
 *  
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
void AppSched_initScheduler( AppSched_Scheduler *scheduler )
{
    /* Here write the initi sentences */
}

/**
 * @brief   **Provide a brief fucntion description (just one line)**
 *
 * Provide the proper and detailed description for your function, you can use as many
 * lines as you want but keep each line less than 100 characteres
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
uint8_t AppSched_registerTask( AppSched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period )
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
        if(initPtr != NULL)
        {
            scheduler->taskPtr->initFunc = initPtr;
        }
        else
        {
            scheduler->taskPtr->initFunc = NULL;
        }

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
uint8_t AppSched_stopTask( AppSched_Scheduler *scheduler, uint8_t task )
{
    uint8_t succStop = FALSE;
    AppSched_Task *ptr_currentTask = (scheduler->taskPtr + (task - 1));
    /* if the taskid inserted its a valid number, the task could be succesfully stoped */
    if((task > 0) && (task <= scheduler->tasks))
    {
        succStop = TRUE;
        ptr_currentTask->startFlag = FALSE;
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
uint8_t AppSched_startTask( AppSched_Scheduler *scheduler, uint8_t task )
{
    uint8_t succStart = FALSE;
    AppSched_Task *ptr_currentTask = (scheduler->taskPtr + (task - 1));
    /* if the taskid inserted its a valid number, the task could be succesfully stoped */
    if((task > 0) && (task <= scheduler->tasks))
    {
        succStart = TRUE;
        ptr_currentTask->startFlag = TRUE;
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
uint8_t AppSched_periodTask( AppSched_Scheduler *scheduler, uint8_t task, uint32_t period )
{
    uint8_t succSetPeriod = FALSE;

    AppSched_Task *ptr_currentTask = (scheduler->taskPtr + (task - 1));
    /* First check if the id task is valid */
    if((task > 0) && (task <= scheduler->tasks))
    {
        if((period % (scheduler->tick)) == 0)
        {
            ptr_currentTask->period = period;
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
void AppSched_startScheduler( AppSched_Scheduler *scheduler )
{
    long tickstart = milliseconds();
    /* auxiliar pointer to the current runnig task */
    AppSched_Task *ptr_currentTask = scheduler->taskPtr;

    /* this holds the number of the times the counting timer has been reach */
    uint32_t tickCounter = 0;
    /* the time in ms that has pasesed since the scheduler started */
    uint32_t msCount = 0;

    /* Call of the Initialization Functions */
    for(scheduler->tasksCount = 0; scheduler->tasksCount < scheduler->tasks; scheduler->tasksCount++)
    {
        if (ptr_currentTask->initFunc != NULL)
        {
            ptr_currentTask->initFunc();              
        }
        else
        {
            /* Do nothing, this task hasnot init function*/
        }
    }

    /* Infinite loop */
    while (msCount < scheduler->timeout)
    {
        /* Check if the tick count has been reach */
        if( ( milliseconds() - tickstart ) >= scheduler->tick )
        {
            /* This is the total that has passed since the scheduler started, to check the timeout condition */
            tickCounter ++; /* update tick counter */
            msCount = tickCounter * scheduler->tick;
            tickstart = milliseconds();/*we get the actual ms again once we are inside the loop for the next execution */
            /* This code its been executing every ptr_currentTask->period that depends on the type of code */
            
            /* Depending on the scheduler counter we have to execute the schedule tasks */
            /* check if the tickCount has reach the period of each task and enable the start flag of each task */
    
            /* a loop to check each existing task for enable it in case of being necessary */
            for(scheduler->tasksCount = 0; scheduler->tasksCount < scheduler->tasks; scheduler->tasksCount++)
            {
                ptr_currentTask = scheduler->taskPtr + scheduler->tasksCount; /* check if its necessary to initialize this counter to cero task counter */
                /* Do nothing */
                /* we have to change the pointer current task to point always to the new direction of task */
                
                /* Check if the period of the current pointing task has been reach to execute this task */
                if(( msCount % ptr_currentTask->period) == 0)
                {
                    /* After increasing the taskcount we can enable the next task, because the id now is the same as the 
                    next task to execute */
                    /* Are the Start and Stop some kind of flags created to create an atomic condition? */
                    
                    if (AppSched_startTask(scheduler,scheduler->tasksCount+1) == TRUE)
                    {
                        ptr_currentTask->taskFunc();
                        /* Stop the run task after the complete code execution */
                        AppSched_stopTask(scheduler,scheduler->tasksCount+1);
                    }
                    else
                    {
                        /* To do Implement a Function to handle errors? */
                    }
                }
                else
                {
                    /* Do nothing */
                }
                
            }

        }
        else
        {
            /* Do nothing */
        }
    }
}