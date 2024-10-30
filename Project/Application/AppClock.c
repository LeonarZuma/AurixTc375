/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "IfxStm.h"
#include "AppClock.h"
#include "bsp.h"
#include "RTCC.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/
/**
  * @brief  AppRtcc_Rtcc Configuration parameters Structure for RTCC
 */
static AppRtcc_Rtcc RTCC_struct;

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/

static void Clock_State_Machine(void);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void AppClock_initTask( void )
{
    /* Set the the corresponding Node Request for GPSR0 SR0 to service provider CPU0 with a priority of 10 */
    IfxSrc_init( &MODULE_SRC.GPSR.GPSR[GPSR0].SR[SR0], IfxSrc_Tos_cpu0, IFX_INTPRIO_GPSR0_SR0);

    AppRtcc_clockInit(&RTCC_struct);
    AppRtcc_setDate(&RTCC_struct, 29, 2, 2024);
    AppRtcc_setTime(&RTCC_struct, 23, 59, 00);
    AppRtcc_setAlarm(&RTCC_struct, 00, 00);

    AppRtcc_intAlarmEnable(&RTCC_struct, SR0);

    /*configure the pin */
    IfxPort_setPinMode( &MODULE_P00, 5, IfxPort_Mode_outputPushPullGeneral );
    IfxPort_setPinPadDriver( &MODULE_P00, 5, IfxPort_PadDriver_cmosAutomotiveSpeed1 );
}

void AppClock_periodicTask( void )
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

    /* Create the string to print the current time hour, minutes and seconds*/
    AppRtcc_getTime(&RTCC_struct, &tm_hr, &tm_min, &tm_sec);
    convert_timeToString(tm_string, tm_hr, tm_min, tm_sec);

    /* Create the string to print the current Date Month, Day, Year, Weekday */
    AppRtcc_getDate(&RTCC_struct, &tm_day, &tm_month, &tm_year, &tm_wday);
    set_dateString(dt_string, tm_month, tm_day, tm_year, tm_wday);

    /* Create the string to print the ALARM cnfg. */
    AppRtcc_getAlarm(&RTCC_struct, &al_hour, &al_min);
    set_alarmString(al_string, al_hour, al_min);
}



/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/

static void Clock_State_Machine(void)
{
    /* create a queue message container to write for the rtcc queue */
    App_Message data2Read;
    
    /* define the init CSM state */
    App_Messages message_receive = SERIAL_MSG_NONE;

    do
    {
        switch (message_receive)
        {
            case SERIAL_MSG_NONE:
                if(AppQueue_isQueueEmpty(&ssm2rtcc_queue) == TRUE)
                {
                    /* Read message from queue */
                    AppQueue_readDataIsr(&ssm2rtcc_queue, &data2Read);
                    /* Assign the current receive message type to change CSM current state */
                    message_receive = data2Read.msg;
                }
                else
                {
                    /* do nothing */
                }
                break;
            case SERIAL_MSG_TIME:
                AppRtcc_setTime(&RTCC_struct, data2Read.tm.tm_hour, data2Read.tm.tm_min, data2Read.tm.tm_sec);
                message_receive = SERIAL_MSG_NONE;
                break;
            case SERIAL_MSG_DATE:
                AppRtcc_setDate(&RTCC_struct, data2Read.tm.tm_mday, data2Read.tm.tm_mon, data2Read.tm.tm_year);
                message_receive = SERIAL_MSG_NONE;
                break;
            case SERIAL_MSG_ALARM:
                AppRtcc_setAlarm(&RTCC_struct, data2Read.tm.tm_hour, data2Read.tm.tm_min);
                message_receive = SERIAL_MSG_NONE;
                break;
            default:
                break;
        }
    } while (message_receive != SERIAL_MSG_NONE);
    
    
}