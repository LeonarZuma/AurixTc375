/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "IfxStm.h"
#include "AppClock.h"
#include "bsp.h"
#include "RTCC.h"
#include "Can_Driver.h"

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

static void AppClock_StateMachine(appclock_ssm2rtcc_data_t queue_content);

static void AppClock_ReadAllQueue(appclock_ssm2rtcc_data_t queue_content);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void AppClock_initTask( void )
{
    /* Set the the corresponding Node Request for GPSR0 SR0 to service provider CPU0 with a priority of 10 */
    /* this is part of the alarm set up */

    AppRtcc_clockInit(&RTCC_struct);
    AppRtcc_setDate(&RTCC_struct, 29, 2, 2024);
    AppRtcc_setTime(&RTCC_struct, 23, 59, 00);
    AppRtcc_setAlarm(&RTCC_struct, 00, 00);

    /* initialize the alarm*/

    /* Init Can for CSM */
    AppClock_CAN_Init();
}

void AppClock_periodicTask( void )
{
    // /* Create the string to print the current time hour, minutes and seconds*/
    // AppRtcc_getTime(&RTCC_struct, &tm_hr, &tm_min, &tm_sec);
    // convert_timeToString(tm_string, tm_hr, tm_min, tm_sec);

    // /* Create the string to print the current Date Month, Day, Year, Weekday */
    // AppRtcc_getDate(&RTCC_struct, &tm_day, &tm_month, &tm_year, &tm_wday);
    // set_dateString(dt_string, tm_month, tm_day, tm_year, tm_wday);

    // /* Create the string to print the ALARM cnfg. */
    // AppRtcc_getAlarm(&RTCC_struct, &al_hour, &al_min);
    // set_alarmString(al_string, al_hour, al_min);

    /* Create data struct type to contain the queue information */
    appclock_ssm2rtcc_data_t ssm2rtcc_queue_content = {
        .size = 0,
        .state = FALSE
    };

    AppClock_ReadAllQueue(ssm2rtcc_queue_content);
    AppClock_StateMachine(ssm2rtcc_queue_content);
}

void AppClock_RTCCUpdate_Callback()
{
    AppRtcc_periodicTask(&RTCC_struct);
}


/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/

static void AppClock_StateMachine(appclock_ssm2rtcc_data_t queue_content)
{
    /* create a queue message container to write for the rtcc queue */
    App_Message data2Read;
    
    /* define the init CSM state */
    CSM_states current_state = CLOCK_IDLE;

    /* Defien the data array */
    uint8_t can_datatx[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    do
    {
        switch (current_state)
        {
            case CLOCK_IDLE:
                if(queue_content.size > 0)
                {
                    queue_content.size --;
                    /* detach an elemnt from the queue to place process it */
                    data2Read = queue_content.data[queue_content.size];
                    /* Assign the current receive message type to change CSM current state */
                    current_state = CLOCK_MESSAGE;
                }
                else
                {
                    /* do nothing the current state is keep */
                }
                break;
            case CLOCK_MESSAGE:
                /* perform message filtering */
                switch(data2Read.msg)
                {
                    case SERIAL_MSG_TIME:
                        current_state = CNFG_TIME;
                        break;
                    case SERIAL_MSG_DATE:
                        current_state = CNFG_DATE;
                        break;
                    case SERIAL_MSG_ALARM:
                        current_state = CNFG_ALARM;
                        break;
                    default:
                        current_state = CLOCK_IDLE;
                        break;
                }
                break;
            case CNFG_TIME:
                AppRtcc_setTime(&RTCC_struct, data2Read.tm.tm_hour, data2Read.tm.tm_min, data2Read.tm.tm_sec);
                current_state = CLOCK_IDLE;
                break;
            case CNFG_DATE:
                AppRtcc_setDate(&RTCC_struct, data2Read.tm.tm_mday, data2Read.tm.tm_mon, data2Read.tm.tm_year);
                current_state = CLOCK_IDLE;
                break;
            case CNFG_ALARM:
                AppRtcc_setAlarm(&RTCC_struct, data2Read.tm.tm_hour, data2Read.tm.tm_min);
                current_state = CLOCK_IDLE;
                break;
            case SENT_TIME:
                /* get time and send it to a queue to be */
                current_state = CLOCK_IDLE;
                break;
            case SENT_DATE:
                break;
            default:
                break;
        }
    } while (current_state != CLOCK_IDLE);
}

static void AppClock_ReadAllQueue(appclock_ssm2rtcc_data_t queue_content)
{
    while (AppQueue_isQueueEmpty(&ssm2rtcc_queue) == FALSE)
    {
        queue_content.state &= ~(0b1);  /* Set this variable as TRUE to indicate a reading has been perfomed */     
        AppQueue_readDataIsr(&ssm2rtcc_queue, &queue_content.data[queue_content.size]);
        queue_content.size ++;
    }
}