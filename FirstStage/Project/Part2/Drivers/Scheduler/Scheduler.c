#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "Phase1.h"
#include "Buffer.h"
#include "Queue.h"
#include "Scheduler.h"

static long milliseconds( void )
{
    return clock() / ( CLOCKS_PER_SEC / 1000 );
}

/* The function should initialize the hscheduler structure with the values passed as parameters, the number of tasks to use, the tick value use a base time, the address of the array of task TCBs,and the amount of time the scheduler should run. */