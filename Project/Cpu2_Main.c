/**********************************************************************************************************************
 * \file Cpu2_Main.c
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
#include "Phase1.h"
#include "Scheduler.h"
#include "RTCC.h"
#include "Button.h"

#define TASKS_N             (3U)
#define N_TIMERS            (3U)
#define TICK_VAL            (10U)       /* Tick Val 10ms */
#define TASK1_VAL           (10U)        /* 5 times TickVal */

/*interrupt priority number for STM0 comparator 0*/

/*interrupt priority number for software interrupt group 0 SR 0*/
#define IFX_INTPRIO_GPSR0_SR0    11

#ifndef GPSR0
    /*Software interrupt group 0*/
    #define GPSR0                     0
    /*Software request node 0*/
    #define SR0                       0
#endif

/*STM0 module*/
#define STM2                     2
/*STM comparator 0*/
#define CMP0                     0

/* Global variables */
Btn_Config btn_cnfg7;

static AppSched_Task tasks[ TASKS_N ];
static AppSched_Timer timers[ N_TIMERS ];
static AppSched_Scheduler Sche_core2;

/* Functions */
void Core2_Init_Task_100ms(void);
void Core2_Task_100ms(void);
void Func_Btn7(void);

extern IfxCpu_syncEvent g_cpuSyncEvent;

void core2_main(void)
{
    uint64 Timeout_100ms;

    /* Task ID creation */
    Sche_core2.tick = (uint64)IfxStm_getTicksFromMilliseconds( &MODULE_STM2, TICK_VAL );
    Sche_core2.tasks = TASKS_N;
    Sche_core2.taskPtr = tasks;
	Sche_core2.timers = N_TIMERS;
    Sche_core2.timerPtr = timers;
    Sche_core2.moduleStm = &MODULE_STM2;
    Sche_core2.stm = STM2;
    

    AppSched_initScheduler(&Sche_core2);

    /*get the number of ticks corresponding to 1000ms*/
    Timeout_100ms = (uint64)IfxStm_getTicksFromMilliseconds( &MODULE_STM2, (TICK_VAL * TASK1_VAL));

    //AppSched_registerTask( &Sche_core2, Core2_Init_Task_100ms, Core2_Task_100ms, Timeout_100ms );

    /* no ponerle nombre de task a las funciones auxiliares de las tareas */

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required */
    IfxScuWdt_disableCpuWatchdog( IfxScuWdt_getCpuWatchdogPassword() );
    IfxScuWdt_disableSafetyWatchdog( IfxScuWdt_getSafetyWatchdogPassword() );
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent( &g_cpuSyncEvent );
    IfxCpu_waitEvent( &g_cpuSyncEvent, 1 );

    /* Set the the corresponding Node Request for GPSR0 SR0 to service provider CPU0 with a
    priority of 10 */

    IfxCpu_enableInterrupts();

    
    AppSched_startScheduler(&Sche_core2);
}

void Core2_Init_Task_100ms(void)
{
    /*configure the pin */
    IfxPort_setPinMode( &MODULE_P00, 9, IfxPort_Mode_outputPushPullGeneral );
    IfxPort_setPinPadDriver( &MODULE_P00, 9, IfxPort_PadDriver_cmosAutomotiveSpeed1 );

    Button_Init(&btn_cnfg7, &MODULE_P21, 5, Func_Btn7);
}

void Core2_Task_100ms(void)
{
    Button_pressedAndReleased(&btn_cnfg7);
}

void Func_Btn7(void)
{
    IfxPort_togglePin( &MODULE_P00, 9 );
}