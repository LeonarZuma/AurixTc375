/**
 * @file    <RTCC.h>
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

#ifndef RTCC_H_
#define RTCC_H_

/** 
  * @defgroup <Time Bouds> Time count boundaries
  @{ */
#define VAL_SECONDS     (60U)       /*!< MAX seconds count */
#define VAL_MINUTES     (60U)       /*!< MAX minutes count */
#define VAL_HOURS       (24U)       /*!< MAX hours count */
#define MONTHS_YEAR     (12U)       /*!< MAX months count */
#define MAX_YEAR        (2100U)     /*!< MAX years count */
#define MIN_YEAR        (1900U)     /*!< MIN years count */
/**
  @} */

/**
  * @brief   Control Register Structure for RTC
  */
typedef union _AppRtcc_Ctrl
{
    uint8_t Register;           /*!<To edit the complete register >*/
  /**
  * @brief   Struct To edit the register by bit field
  */
    struct _bits               
    {
        uint8_t clk_en : 1;     /*!< clock enable flag      */
        uint8_t al_set : 1;     /*!< alarm set flag         */
        uint8_t al_active : 1;  /*!< alarm active flag      */
        uint8_t none : 4;       /*!< empty space not implemented  */
    } bits;                     /*!< to edit register by bit field  */
} AppRtcc_Ctrl;


/**
  * @brief   Configuration parameters Structure for RTCC
  */
typedef struct _AppRtcc_Clock 
{
    uint8_t tm_sec;         /*!< seconds,  range 0 to 59          */
    uint8_t tm_min;         /*!< minutes, range 0 to 59           */
    uint8_t tm_hour;        /*!< hours, range 0 to 23             */
    uint8_t tm_mday;        /*!< day of the month, range 1 to 31  */
    uint8_t tm_mon;         /*!< month, range 1 to 12             */
    uint16_t tm_year;       /*!< years in rage 1900 2100          */
    uint8_t tm_wday;        /*!< day of the week, range 0 to 6    */
    uint8_t al_min;         /*!< alarm minutes, range 0 to 59     */
    uint8_t al_hour;        /*!< alarm hours, range 0 to 23       */
    uint8_t mt_days[13u];   /*!< max days on each month */
    AppRtcc_Ctrl ctrl;      /*!< clock control bits */
} AppRtcc_Rtcc;

void AppRtcc_clockInit( AppRtcc_Rtcc *rtcc );

uint8_t AppRtcc_setTime( AppRtcc_Rtcc *rtcc, uint8_t hour, uint8_t minutes, uint8_t seconds );

uint8_t AppRtcc_setDate( AppRtcc_Rtcc *rtcc, uint8_t day, uint8_t month, uint16_t year );

uint8_t AppRtcc_setAlarm( AppRtcc_Rtcc *rtcc, uint8_t hour, uint8_t minutes );

void AppRtcc_getTime( AppRtcc_Rtcc *rtcc, uint8_t *hour, uint8_t *minutes, uint8_t *seconds );

void AppRtcc_getDate( AppRtcc_Rtcc *rtcc, uint8_t *day, uint8_t *month, uint16_t *year, uint8_t *weekDay );

uint8_t AppRtcc_getAlarm( AppRtcc_Rtcc *rtcc, uint8_t *hour, uint8_t *minutes );

void AppRtcc_clearAlarm( AppRtcc_Rtcc *rtcc );

uint8_t AppRtcc_getAlarmFlag( AppRtcc_Rtcc *rtcc );

void AppRtcc_periodicTask( AppRtcc_Rtcc *rtcc );

#endif