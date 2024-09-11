/******************************************************************************

how do i know, how many items are stored inside the circular buffer?
	the Tail pointer must be behind the Head pointer
	the tail only could read a previous write space
	the head only could write a previous read space or empty one
	after each operation the pointer must be increment by one.

Function will determine if the queue is full with the last data written. How?
	If both pointer are in the same position after an operation (read/write). This mean that you cant perform the actual operation again.
e.g.
	If you are performing a reading and after increassing the Tail pointer direction is the same as, Head pointer, there is no new available information to read. 

Otherwise e.g.
	If you are performing a writing and after increasing the Head pointer direction is the same as Tail pointer, there is no new available space to write, the buffer is full (EMPTY = FALSE, FULL = TRUE). 


Possibilities
	head > tail	its easy to know if there is 
	tail < head


New Notes
    There is only one datatype to write. I mean if you start writng in the buffer Structs of Type Message you must
    keep writing Message data types to the buffer. You cant mixup different datatypes as sending a char, then an int
    and so on.




*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Drivers/Phase1.h"
#include "Drivers/Buffer.h"
#include "Drivers/Queue.h"
#include "Drivers/Scheduler.h"

#define TASKS_N     3
#define N_TIMERS   2
#define TICK_VAL    100

void Init_500ms(void);
void Task_500ms(void);
void Callback(void);
void Callback2(void);

static AppSched_Task tasks[ TASKS_N ];
static AppSched_Timer timers[ N_TIMERS ];
static AppSched_Scheduler Sche;
static unsigned char TimerID;
static unsigned char TimerID2;

void Init_500ms(void);
void Init_1000ms(void);
void Task_500ms(void);
void Task_1000ms(void);
void Task_2000ms(void);

int main(void)
{
	unsigned char TaskID1;
    unsigned char TaskID2;
    unsigned char TaskID3;
    /*init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only*/
    Sche.tick = TICK_VAL;
    Sche.tasks = TASKS_N;
    Sche.timeout = 10000;
    Sche.taskPtr = tasks;
	Sche.timers = N_TIMERS;
    Sche.timerPtr = timers;
	

	/* Struct element size */


    AppSched_initScheduler( &Sche );
    /*register two task with thier corresponding init fucntions and their periodicity, 100ms and 500ms*/
    TaskID1 = AppSched_registerTask( &Sche, Init_500ms, Task_500ms, 500 );
    TaskID2 = AppSched_registerTask( &Sche, Init_1000ms, Task_1000ms, 1000 );
    TaskID3 = AppSched_registerTask( &Sche, NULL, Task_2000ms, 2000 );
	TimerID = AppSched_registerTimer( &Sche, 1500u, Callback );
	TimerID2 = AppSched_registerTimer( &Sche, 3000u, Callback2 );
	AppSched_startTimer(&Sche, TimerID);
	AppSched_startTimer(&Sche, TimerID2);
	printf("timers: %d\n",Sche.timerCount);

	AppSched_startTask(&Sche, TaskID2);
	AppSched_startTask(&Sche, TaskID3);

	printf("%d\n",*(&(tasks->period)+0));
	printf("%d\n",*(&(tasks->period)+1));
	printf("%d\n",*(&(tasks->period)+2));
	printf("%d\n",*(&(tasks->period)+3));
	printf("%d\n",*(&(tasks->period)+4));
	printf("%d\n\n",TaskID1);

	printf("TimerId: %d\n",TimerID);
	printf("startFlag: %d\n",timers[0].startFlag);
	printf("TimerId: %d\n",TimerID2);
	printf("startFlag: %d\n",timers[1].startFlag);

	printf("%d\n",*(&(tasks->period)+5));
	printf("%d\n",*(&(tasks->period)+6));
	printf("%d\n",*(&(tasks->period)+7));
	printf("%d\n",*(&(tasks->period)+8));
	printf("%d\n",*(&(tasks->period)+9));
	printf("%d\n\n",TaskID2);

	AppSched_stopTask(&Sche, TaskID2);
	AppSched_periodTask(&Sche,TaskID2,1500);

	printf("%d\n",*(&(tasks->period)+5));
	printf("%d\n",*(&(tasks->period)+6));
	printf("%d\n",*(&(tasks->period)+7));
	printf("%d\n",*(&(tasks->period)+8));
	printf("%d\n",*(&(tasks->period)+9));
	printf("%d\n\n",TaskID2);

	AppSched_startScheduler(&Sche);
}

void Init_500ms(void)
{
    printf("Init task 500 millisecond\n");
}
void Init_1000ms(void)
{
    printf("Init task 1000 millisecond\n");
}
void Task_500ms(void)
{
    static int loop = 1;
    printf("This is a counter from task 500ms: %d\n", loop++);
}
void Task_1000ms(void)
{
    static int loop = 1;
    printf("This is a counter from task 1500ms: %d\n", loop++);
}
void Task_2000ms(void)
{
    static int loop = 1;
    printf("This is a counter from task 2000ms: %d\n", loop++);
}
void Callback(void)
{
    static int loop = 1;
    printf("This is a counter from timer callback: %d\n", loop++);
    AppSched_startTimer(&Sche ,TimerID);
}
void Callback2(void)
{
    static int loop = 1;
    printf("This is a counter from timer callback2: %d\n", loop++);
    //AppSched_startTimer(&Sche ,TimerID);
}