/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include <stdint.h>
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "IfxPort.h"
#include "IfxPort_Io.h"
#include "IfxStm.h"

#include "Queue.h"
#include "Scheduler.h"

#include "bsp.h"
#include "AppSerial.h"
#include "AppClock.h"

#define TASKS_N             (3U)
#define N_TIMERS            (3U)
#define TICK_VAL            (5U)            /* Tick Val 5ms */
#define TASK1_VAL           (2U)            /* 2 times TickVal */
#define TASK2_VAL           (10U)           /* 10 times TickVal */
#define TASK3_VAL           (200U)          /* 200 times TickVal */

/*STM0 module*/
#define STM0                     0

/* Global variables */
static AppSched_Task tasks[ TASKS_N ];
static AppSched_Timer timers[ N_TIMERS ];
static AppSched_Scheduler Sche_core0;

/* External variables shared beetwen cores */
IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;
IFX_ALIGN(4) AppQue_Queue shared_queue;

void core0_main(void)
{
    App_Message buffer[QUEUE_BUFFER_SIZE];
    /* Set the buffer for the Queue */
    shared_queue.buffer = (void*)buffer;
    /* Queue lenght must be the same or less than the buffer size */
    shared_queue.elements = QUEUE_BUFFER_SIZE;
    /* The size of a single element */
    shared_queue.size = sizeof(App_Message);

    /* Init queue Function call */
    AppQueue_initQueue(&shared_queue);

    uint64 Timeout_10ms;
    uint64 Timeout_50ms;
    uint64 Timeout_1000ms;

    /* Task ID creation */
    Sche_core0.tick = (uint64)IfxStm_getTicksFromMilliseconds(&MODULE_STM0, TICK_VAL);
    Sche_core0.tasks = TASKS_N;
    Sche_core0.taskPtr = tasks;
	Sche_core0.timers = N_TIMERS;
    Sche_core0.timerPtr = timers;
    Sche_core0.moduleStm = &MODULE_STM0;
    Sche_core0.stm = STM0;

    AppSched_initScheduler(&Sche_core0);

    /*get the number of ticks corresponding to 10ms */
    Timeout_10ms = (uint64)IfxStm_getTicksFromMilliseconds(&MODULE_STM0, (TICK_VAL * TASK1_VAL));
    Timeout_50ms = (uint64)IfxStm_getTicksFromMilliseconds(&MODULE_STM0, (TICK_VAL * TASK2_VAL));
    Timeout_1000ms = (uint64)IfxStm_getTicksFromMilliseconds(&MODULE_STM0, (TICK_VAL * TASK3_VAL));

    AppSched_registerTask(&Sche_core0, AppSerial_initTask, AppSerial_periodicTask, Timeout_10ms);
    AppSched_registerTask(&Sche_core0, AppClock_initTask, AppClock_periodicTask, Timeout_50ms);
    AppSched_registerTask(&Sche_core0, NULL, AppClock_RTCCUpdate_Callback, Timeout_1000ms);

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    IfxCpu_enableInterrupts();

    AppSched_startScheduler(&Sche_core0);
}