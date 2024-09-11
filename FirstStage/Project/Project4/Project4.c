/**
 * @file    <Project4.c>
 * @brief   **This File contains the implementation of the RTCC-Scheduler Drivers to simulate a Clock-Alarm**
 *
 * Combining the features of the Scheduler with the RTCC, this file contains a simulated Clock-Alarm implementation
 * where the AppRtcc_periodicTask is registered as a periodic 1000ms task for the scheduler. Including an Initialization
 * routine to Setup the RTCC Clock.
 * 
 *      Sche.timeout represents the total time that the Clock will be working
 *
 * @note    The "Phase1.h" contains auxiliar functions to handle date and time to print
 */
#include <stdio.h>
#include <stdint.h>
#include "Drivers/Phase1.h"
#include "Drivers/Scheduler.h"
#include "Drivers/RTCC.h"

/** 
  * @defgroup <Scheduler_Param> Setting Scheduler parameter 
  @{ */
#define TASKS_N     4		/*!< Max number of task to define */
#define N_TIMERS   2        /*!< Max number if timers to define */
#define TICK_VAL    100     /*!< Tick Count 100ms */
/**
  @} */

/**
 * @brief  Array of Structs Task, each element has the cnfg parameters for every task
 */
static AppSched_Task tasks[ TASKS_N ];
/**
 * @brief  Array of Structs Timers, each element has the cnfg parameters for every timer
 */
static AppSched_Timer timers[ N_TIMERS ];
/**
 * @brief  AppSched_Scheduler
 */
static AppSched_Scheduler Sche;

/**
 * @brief  AppRtcc_Ctrl Control Register Structure for RTC
 */
AppRtcc_Ctrl AppRtcc_Ctrl_struct;

/**
  * @brief  AppRtcc_Rtcc Configuration parameters Structure for RTCC
 */
AppRtcc_Rtcc RTCC_struct;

void Init_1000ms(void);
void Callback(void);

int main(void)
{
	unsigned char TaskID1;
    /*init the scheduler with two tasks and a tick time of 100ms and run for 10 seconds only*/
    Sche.tick = TICK_VAL;
    Sche.tasks = TASKS_N;
    Sche.timeout = 120000;
    Sche.taskPtr = tasks;
	Sche.timers = N_TIMERS;
    Sche.timerPtr = timers;

	/* Struct element size */

    AppSched_initScheduler( &Sche );
    /* register two task with thier corresponding init fucntions and their periodicity, 1000ms */
    TaskID1 = AppSched_registerTask( &Sche, Init_1000ms, Callback, 1000 );

	AppSched_startScheduler(&Sche);

    /* This is to avoid the warning because the variable is not used */
    (void)TaskID1;
}

/**
 * @brief   ** Initialization Function for the 1000ms peridic task**
 *
 * Provides the proper Initialization of the RTCC Driver executing the functions:
 *      ClockInit
 *      setDate
 *      setTime
 *      setAlarm
 *
 * @retval  None
 *
 * @note This task is called by the scheduler only once. Before the count starts.
 */
void Init_1000ms(void)
{
    printf("Initialization\n");
    AppRtcc_clockInit(&RTCC_struct);
    AppRtcc_setDate(&RTCC_struct, 29, 2, 2024);
    AppRtcc_setTime(&RTCC_struct, 21, 55, 00);
    AppRtcc_setAlarm(&RTCC_struct, 00, 01);
    printf("Date %d/%d/%d\n", RTCC_struct.tm_mon,RTCC_struct.tm_mday,RTCC_struct.tm_year);
    printf("Time %d:%d\n", RTCC_struct.al_hour,RTCC_struct.al_min);
    printf("Time %d:%d:%d\n", RTCC_struct.tm_hour,RTCC_struct.tm_min,RTCC_struct.tm_sec);
}

/**
 * @brief   **Main RTCC function that is called every 1000ms**
 *
 * Refersh the count of:
 *      seconds
 *      minutes
 *      hours
 *      days
 *      months
 *      years
 * Also check if the set alarm has reach the time criteria to active the alarm.
 *
 *
 * @retval  None
 *
 * @note This callback function is called every 1000ms by the scheduler
 */
void Callback(void)
{
    int8_t tm_string[9];
    uint8_t tm_hr = 0;
    uint8_t tm_min = 0;
    uint8_t tm_sec = 0;

    int8_t dt_string[30];
    uint8_t tm_day = 0;
    uint8_t tm_month = 0;
    uint16_t tm_year = 0;
    uint8_t tm_wday = 0;

    int8_t al_string[12];
    uint8_t al_hour = 0;
    uint8_t al_min = 0;

    /* update time, date and check if alarm condition has been reach */
    AppRtcc_periodicTask(&RTCC_struct);

    /* Create the string to print the current time hour, minutes and seconds*/
    AppRtcc_getTime(&RTCC_struct, &tm_hr, &tm_min, &tm_sec);
    convert_timeToString(tm_string, tm_hr, tm_min, tm_sec);

    /* Create the string to print the current Date Month, Day, Year, Weekday */
    AppRtcc_getDate(&RTCC_struct, &tm_day, &tm_month, &tm_year, &tm_wday);
    set_dateString(dt_string, tm_month, tm_day, tm_year, tm_wday);

    /* Create the string to print the ALARM cnfg. */
    AppRtcc_getAlarm(&RTCC_struct, &al_hour, &al_min);
    set_alarmString(al_string, al_hour, al_min);

    printf("%s\n", dt_string);
    printf("%s\n", al_string);
    printf("Time %s\n", tm_string);
}