#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef struct _task
{
    uint32_t period;          /*How often the task shoud run in ms*/
    uint32_t elapsed;         /*the curent elapsed time*/
    uint8_t startFlag;        /*flag to run task*/
    void (*initFunc)(void);   /*pointer to init task function*/
    void (*taskFunc)(void);   /*pointer to task function*/
    //Add more elements if required
}AppSched_Task;

typedef struct _scheduler
{
    uint8_t tasks;         /*number of task to handle*/
    uint32_t tick;          /*the time base in ms*/
    uint32_t timeout;       /*the number of milliseconds the scheduler should run*/
    uint8_t tasksCount;    /*internal task counter*/
    AppSched_Task *taskPtr;  /*Pointer to buffer for the TCB tasks*/
    //Add more elements if required
}AppSched_Scheduler;

#define TASK_NUMBER     (3U)

void AppSched_initScheduler( AppSched_Scheduler *scheduler );

uint8_t AppSched_registerTask( AppSched_Scheduler *scheduler, void (*initPtr)(void), void (*taskPtr)(void), uint32_t period );

uint8_t AppSched_stopTask( AppSched_Scheduler *scheduler, uint8_t task );

uint8_t AppSched_startTask( AppSched_Scheduler *scheduler, uint8_t task );

uint8_t AppSched_periodTask( AppSched_Scheduler *scheduler, uint8_t task, uint32_t period );

void AppSched_startScheduler( AppSched_Scheduler *scheduler );



#endif