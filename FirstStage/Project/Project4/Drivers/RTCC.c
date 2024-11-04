/**
 * @file    <RTCC.c>
 * @brief   **A simple clock and calendar implementing real time counting**
 *
 * This driver contains the main structure and logic to simulate a REAL clock or Timer counting including:
 *      Seconds
 *      Minutes
 *      Hours       (24 Hours format)
 *      Days
 *      Months
 *      Years
 * Also includes an Alarm functionality setting a certain hh-mm.
 * 
 * Steps to configure and use correctly the RTCC driver. 
 *      Before executing periodically the "AppRtcc_periodicTask", we have to call once this functions following the
 *      same order:
 *          AppRtcc_clockInit   Set/Reset the deafult cnfg for the driver
 *          AppRtcc_setDate     Set the Date 
 *          AppRtcc_setTime     Set the time
 *          AppRtcc_setAlarm    Set the alarm (if is requiered)
 * 
 *      After the RTCC initialization The following functions must been called periodically with a recurrence of 1000ms
 *      to keep a constant refresh of the time count. 
 *          AppRtcc_periodicTask      To update time, date and check if alarm condition has been reach
 *              AppRtcc_getTime           To get the current time hour, minutes and seconds
 *              AppRtcc_getDate           To get the current Date Month, Day, Year, Weekday
 *              AppRtcc_getAlarm          To get the alarm cnfg time (if is necessary)
 * 
 * The static functions are just auxiliar functions to make the code more readable. This can't be called externally.
 *
 * @note    The driver can't count down by itself, it has to be called externally from a certain scheduler or counting
 * method to perform the "AppRtcc_periodicTask".
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Phase1.h"
#include "RTCC.h"

/**
 * @brief   ** Update the current time every second **
 *
 * This function updates the current time and is called every second, changing, seconds, minutes and hours. Using a 
 * 24 Hours foramt.
 *
 * @param[in]   rtcc  RTCC control structure with the day, month and year
 *
 * @retval  None
 */
static void AppRtcc_updTime(AppRtcc_Rtcc *rtcc)
{
        /* update seconds */
    rtcc->tm_sec = ((rtcc->tm_sec + 1)% VAL_SECONDS);

    if((rtcc->tm_sec) == 0)
    {
            /* update minutes */
        rtcc->tm_min = ((rtcc->tm_min + 1)% VAL_MINUTES);
        if((rtcc->tm_min) == 0)
        {
            /* update hours */
            rtcc->tm_hour = ((rtcc->tm_hour + 1)% VAL_HOURS);
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
}

/**
 * @brief   ** Check if a given value is inside certaint boudaries **
 *
 * Check if a given values is lower than supLim and higher than infLim.
 *
 * @param[in]   infLim  Comparation Lower Limit
 * @param[in]   value  Value to check if it's in range
 * @param[in]   supLim  comparation Upper Limit
 *
 * @retval  <valInRange> The enter value is inside the range TRUE, otherwise FALSE
 *
 */
static uint8_t AppRtcc_valInRange(uint8_t infLim, uint16_t value, uint16_t supLim)
{
    uint8_t valInRange = FALSE;
    
    if((value <= supLim) && (value >= infLim))
    {
        valInRange = TRUE;
    }
    else
    {
        /* Do nothing the default value is take */
    }

    return valInRange;
}

/**
 * @brief   ** Check if the set alarm has been reach **
 *
 * Periodically check if the time has reach the set alarm to perform the alarm activation
 *
 * @param[in]   rtcc  RTCC control structure with the day, month and year
 *
 * @retval  None
 * 
 */
static void AppRtcc_updAlmAct(AppRtcc_Rtcc *rtcc)
{
    /* variables for the alarm */
    uint8_t minAlarm = 0;
    uint8_t hrAlarm = 0;
    uint8_t alSet = AppRtcc_getAlarm(rtcc, &hrAlarm, &minAlarm);

    /* check if alarm is set */    
    if((alSet == TRUE) && (rtcc->tm_hour == hrAlarm) && (rtcc->tm_min == minAlarm) && (rtcc->tm_sec == 0))
    {
        /* Activate alarm */
        rtcc->ctrl.bits.al_active = TRUE;
        //rtcc->ctrl.bits.al_set = FALSE;
    }
    else
    {
        rtcc->ctrl.bits.al_active = FALSE;
        /* Do nothing the alarm time has not been reahc yet */
    }
}

/**
 * @brief   ** Check if the given date dd-mm-yyyy its a valid data **
 *
 * Entering a date dd-mm-yyyy, the function check if its a valid date. 
 *
 * @param[in]   day  The set day
 * @param[in]   month  The set month
 * @param[in]   year  The set year
 * @param[in]   mt_days  The number of days in a given month
 *
 * @retval  <valDate> The enter data is valid value TRUE, otherwise FALSE
 *
 */
static uint8_t AppRtcc_valDate(uint8_t day, uint8_t month, uint16_t year, uint8_t mt_days)
{
    uint8_t valDate = FALSE;

    /*  Still missing hoy to comprobate if february has 28 or 29 days */
    if (AppRtcc_valInRange(0, day, mt_days) && AppRtcc_valInRange(0, month, MONTHS_YEAR) && AppRtcc_valInRange(MIN_YEAR, year, MAX_YEAR))
    {
        valDate = TRUE;
    }
    else
    {
        /* Do nothing */
    }

    return valDate;
}

/**
 * @brief   ** Calculate the day of week for a given date dd-mm-yyyy **
 *
 * This functions receives a date and calculates the corresponding weekday for it (0 - 6), an returns this result as a uint8_t. It's a 
 * simple function suggested by Sakamoto, Lachman, Keith and Craver to calculate weekday.
 *
 * @param[in]   rtcc  RTCC control structure with the day, month and year
 *
 * @retval  <weekday> The result weekday, from 0 - 6 (Sunday - Saturday) for a giving date
 *
 */
static uint8_t AppRtcc_calWeekday(AppRtcc_Rtcc *rtcc)
{
    uint16_t constVal = rtcc->tm_year;
    uint8_t weekday = 0;
    uint8_t lutTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    /* This numbers can be consider magic numbers, because they dont have an specific */
    constVal -= (rtcc->tm_mon < 3);
    weekday = ((constVal + (constVal / 4) - (constVal / 100) + (constVal / 400) + lutTable[rtcc->tm_mon - 1] + rtcc->tm_mday) % 7);
    
    return weekday;
}

/**
 * @brief   ** Update the Date mm-dd-yyyy **
 *
 * by a giving time it updates the current date
 *
 * @param[in]   rtcc  RTCC control structure with the day, month and year
 * 
 * @retval  None
 *
 */
static void AppRtcc_updDate(AppRtcc_Rtcc *rtcc)
{
    /* update the number of days in february */
    /* This could be optimized to run only once */
    rtcc->mt_days[1] = (28 + ((rtcc->tm_year % 4) == 0));

    /* Check end of day condition */
    if(rtcc->tm_hour + rtcc->tm_min + rtcc->tm_sec == 0)
    {
        /* update day */
        rtcc->tm_mday ++;
        rtcc->tm_wday = AppRtcc_calWeekday(rtcc);
            /* update month */
        if(rtcc->tm_mday > rtcc->mt_days[rtcc->tm_mon - 1])
        {
            rtcc->tm_mon++;
            rtcc->tm_mday = 1;
                /* update year */
            if(rtcc->tm_mon > MONTHS_YEAR)
            {
                rtcc->tm_mday = 1;
                rtcc->tm_mon = 1;
                rtcc->tm_year++;
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
    }
    else
    {
        /* Do nothing */
    }

}

/**
 * @brief   ** Initialize the internal clock structure **
 *
 * The function shall initialize  all the clock control structure to valid values, such values should be the hour
 * set to 00:00:00 and the valid date to January 1, 1900, enable the clock bit and disable the alarm control, bits
 *
 * @param[in]   rtcc  RTCC control structure
 *
 * @retval  None
 *
 */
void AppRtcc_clockInit(AppRtcc_Rtcc *rtcc)
{
    uint8_t qntyDayMonth[] = {31, (28 + ((rtcc->tm_year % 4) == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    rtcc->tm_sec = 00;
    rtcc->tm_min = 00;
    rtcc->tm_hour = 00;
    rtcc->tm_mday = 1;
    rtcc->tm_mon = 1;
    rtcc->tm_year = MIN_YEAR;
    rtcc->tm_wday = 1;
    arrayCopy(qntyDayMonth, rtcc->mt_days, MONTHS_YEAR, 0);
}

/**
 * @brief   ** Interface to set a new time **
 *
 * The function will receive the hour, minutes and seconds in 24 hour format, the values should be validated id
 * they make a valid hour, in case true the new values shall be assigned to the corresponding internal clock 
 * structure, Function shall return a TRUE is the new time could be set otherwise returns FALSE
 *
 * @param[in]   rtcc  RTCC control structure
 * @param[in]   hour  The set Hour
 * @param[in]   seconds  The set seconds
 * @param[in]   minutes  The set minutes
 *
 * @retval  <setTime> Function shall return a TRUE is the new time could be set otherwise returns FALSE
 *
 */
uint8_t AppRtcc_setTime(AppRtcc_Rtcc *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds)
{
    uint8_t setTime = FALSE;
    /* Validate if the time is acceptable */
    if (AppRtcc_valInRange(0, hour, VAL_HOURS) && AppRtcc_valInRange(0, minutes, VAL_MINUTES) && AppRtcc_valInRange(0, seconds, VAL_SECONDS))
    {
        rtcc->tm_sec = seconds;
        rtcc->tm_min = minutes;
        rtcc->tm_hour = hour;

        setTime = TRUE;
    }
    else
    {
        /* Do nothing, no valid data time */
    }
    return setTime;
}

/**
 * @brief   ** Interface to set a new date **
 *
 * The function will receive the day of the month, month of the year and the years in four digits, the values 
 * should be validated if they make a valid date, in case true the new values shall be assigned to the 
 * corresponding internal clock structure, plus, the function shall calculate the day of the week and assigned to 
 * the corresponding clock structure element. Function shall return a TRUE is the new time could be set otherwise 
 * returns FALSE
 *
 * @param[in]   rtcc  RTCC control structure
 * @param[in]   day  The set day
 * @param[in]   month  The set month
 * @param[in]   year  The set year
 *
 * @retval  <setDate> Function shall return a TRUE is the new time could be set otherwise returns FALSE
 *
 */
uint8_t AppRtcc_setDate(AppRtcc_Rtcc *rtcc, uint8_t day, uint8_t month, uint16_t year)
{
    uint8_t setDate = FALSE;

    /* This could be optimized to run only once */
    rtcc->mt_days[1] = (28 + ((rtcc->tm_year % 4) == 0));
    
    if(AppRtcc_valDate(day, month, year, rtcc->mt_days[month - 1]) == TRUE)
    {
        rtcc->tm_year = year;
        rtcc->tm_mon = month;
        rtcc->tm_mday = day;

        rtcc->tm_wday = AppRtcc_calWeekday(rtcc);

        setDate = TRUE;
    }
    else
    {
        /* No valid data to perform a setDate*/
    }

    return setDate;
}

/**
 * @brief   ** Interface to set a new alarm value **
 *
 * The function will receive the hour and minutes in 24 hour format, the values should be validated if they make a valid time, in case true
 * the new values shall be assigned to the corresponding alarm internal clock structure, and set the flag  al_set which indicate a alarm 
 * will be activated as soon as the time match the alarm value. Function shall return a TRUE is the new time could be set otherwise returns
 * FALSE
 *
 * @param[in]   rtcc  RTCC control structure
 * @param[in]   hour  The set Hour
 * @param[in]   minutes  The set minutes
 *
 * @retval  <setAlarm> Function shall return a TRUE is the new time could be set otherwise returns FALSE *
 * 
 */
uint8_t AppRtcc_setAlarm(AppRtcc_Rtcc *rtcc, uint8_t hour, uint8_t minutes)
{
    uint8_t setAlarm = FALSE;
    if (AppRtcc_valInRange(0, hour, VAL_HOURS) && AppRtcc_valInRange(0, minutes, VAL_MINUTES))
    {
        rtcc->al_hour = hour;
        rtcc->al_min = minutes;
        rtcc->ctrl.bits.al_set = TRUE;
        setAlarm = TRUE;
    }
    else
    {

    }

    return setAlarm;
}

/**
 * @brief   ** Interface to read the current time **
 *
 * The function returns by reference the current time values, hour, minutes and seconds, all the values will be taken
 * from the clock control structure
 *
 * @param[in]    rtcc  RTCC control structure
 * @param[out]   hour  Get current Hour
 * @param[out]   minutes  Get current Minutes
 * @param[out]   seconds  Get current seconds
 *
 * @retval  None
 */
void AppRtcc_getTime(AppRtcc_Rtcc *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds)
{
    *hour = rtcc->tm_hour;
    *minutes = rtcc->tm_min;
    *seconds = rtcc->tm_sec;
}

/**
 * @brief   ** Interface to read the current date **
 *
 * The function returns by reference the current date values, day of the month, month, year and day of the week, all 
 * the values will be taken from the clock control structure
 *
 * @param[in]    rtcc  RTCC control structure
 * @param[out]   day  Get the current day
 * @param[out]   month  Get the current month
 * @param[out]   year  Get the current year
 * @param[out]   weekDay  Get the current weekDay
 *
 * @retval  None 
 */
void AppRtcc_getDate(AppRtcc_Rtcc *rtcc, uint8_t *day, uint8_t *month, uint16_t *year, uint8_t *weekDay)
{
    *weekDay = rtcc->tm_wday;
    *year = rtcc->tm_year;
    *day = rtcc->tm_mday;
    *month = rtcc->tm_mon;
}

/**
 *
 *  @brief   ** Interface to read the current alarm**
 *
 * The function returns by reference the current alarm values, hour and minutes, plus the the status of the set bit 
 * which indicates if the alarm is currently ready for activation. All the values will be taken from the clock 
 * control structure
 *
 * @param[in]    rtcc  RTCC control structure
 * @param[out]   hour  Get Hour Alarm
 * @param[out]   minutes  Get minutes alarm
 *
 * @retval  <alarm set status> This alarm set status flag
 */
uint8_t AppRtcc_getAlarm(AppRtcc_Rtcc *rtcc, uint8_t *hour, uint8_t *minutes)
{
    *hour = rtcc->al_hour;
    *minutes = rtcc->al_min;

    return rtcc->ctrl.bits.al_set;
}

/**
 *
 *  @brief   ** Interface  to clear an active current alarm **
 *
 * Once the alarm is active (time and alarm values are the same) this function will be use to clear the active flag 
 * and also will disable the alarm, been necessary to call the AppClk_setAlarm function again to set the alarm
 *
 * @param[in]   rtcc  RTCC control structure
 * 
 * @retval  None
 * 
 */
void AppRtcc_clearAlarm(AppRtcc_Rtcc *rtcc)
{
    rtcc->ctrl.bits.al_set = FALSE;
    rtcc->ctrl.bits.al_active = FALSE;
}

/**
 *
 *  @brief   ** Interface to get the flag that indicates if the alarm is active **
 *
 * The function will return the alarm active bit
 * 
 * @param[in]  rtcc  RTCC control structure
 *
 * @retval   <rtcc->ctrl.bits.al_active> The alarm active bit
 * 
 */
uint8_t AppRtcc_getAlarmFlag(AppRtcc_Rtcc *rtcc)
{
    return rtcc->ctrl.bits.al_active;
}

/**
 *
 *  @brief   ** Clock Periodic function **
 *
 * This is the main function in charge of increment the time and date values based on any regular clock 
 * functionality, besides of incrementing time and date it will be in charge of supervise when an alarm is set and 
 * should be activated when time and minutes match. function most take care of also handle the increment of the day 
 * of the week accordingly and the leap year when necessary. It is necessary this function been called every one 
 * second using any other external mechanism like a timer, software timer or an interrupt when available.
 *
 * @param[in]   rtcc  RTCC control structure
 *
 * @retval  None
 * 
 * */
void AppRtcc_periodicTask( AppRtcc_Rtcc *rtcc )
{
        /* update time */
    AppRtcc_updTime(rtcc);

        /* Check Alarm time match */
    AppRtcc_updAlmAct(rtcc);
    
        /* update day of week */
    AppRtcc_updDate(rtcc);
}
