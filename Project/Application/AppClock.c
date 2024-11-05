/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
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

static void AppClock_ReadAllQueue(appclock_ssm2rtcc_data_t *queue_content);

static void AppClock_CanTx_DateTime(App_TmTime *data);

static void AppClock_getTimeDate(App_TmTime *data);

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
    /* Create data struct type to contain the queue information */
    appclock_ssm2rtcc_data_t ssm2rtcc_queue_content = {
        .size = 0,
        .state = FALSE
    };

    /* Read all the queue elements from the ss2rtcc */
    AppClock_ReadAllQueue(&ssm2rtcc_queue_content);

    /* Execute state machine with the elements of the queue that has been read */
    AppClock_StateMachine(ssm2rtcc_queue_content);
}

void AppClock_RTCCUpdate_Callback()
{
    App_TmTime datetime_data;
    
    /* update Rtcc time*/
    AppRtcc_periodicTask(&RTCC_struct);

    /* get time and date */
    AppClock_getTimeDate(&datetime_data);

    /* send time and data over can bus */
    AppClock_CanTx_DateTime(&datetime_data);
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
            default:
                break;
        }
    } while (current_state != CLOCK_IDLE || queue_content.size > 0);
}

static void AppClock_ReadAllQueue(appclock_ssm2rtcc_data_t *queue_content)
{
    while (AppQueue_isQueueEmpty(&ssm2rtcc_queue) == FALSE)
    {
        queue_content->state |= (0b1);  /* Set this variable as TRUE to indicate a reading has been perfomed */     
        AppQueue_readDataIsr(&ssm2rtcc_queue, &queue_content->data[queue_content->size]);
        queue_content->size ++;
    }
}

static void AppClock_CanTx_DateTime(App_TmTime *data)
{
    /* Defien the data array */
    uint8_t datatx[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    datatx[0] = AppClock_Can_Decimal2BCD(data->tm_hour);
    datatx[1] = AppClock_Can_Decimal2BCD(data->tm_min);
    datatx[2] = AppClock_Can_Decimal2BCD(data->tm_sec);

    /* Pack message in CAN-TP format */    
    CanTp_SingleFrameTx(datatx, 3);

    /* Send time over CAN */
    Can_Send_Message((uint16_t)0x212, (uint8_t *)&datatx);

    datatx[0] = AppClock_Can_Decimal2BCD(data->tm_mday);
    datatx[1] = AppClock_Can_Decimal2BCD(data->tm_mon);
    datatx[2] = AppClock_Can_Decimal2BCD((uint8_t)(data->tm_year /100));
    datatx[3] = AppClock_Can_Decimal2BCD((uint8_t)(data->tm_year % 100));

    /* Pack message in CAN-TP format */
    CanTp_SingleFrameTx(datatx, 4);

    /* Send date over CAN */
    Can_Send_Message((uint16_t)0x201, (uint8_t *)&datatx);
}

static void AppClock_getTimeDate(App_TmTime *data)
{
    // /* Create the string to print the current time hour, minutes and seconds*/
    AppRtcc_getTime(&RTCC_struct, &data->tm_hour, &data->tm_min, &data->tm_sec);

    // /* Create the string to print the current Date Month, Day, Year, Weekday */
    AppRtcc_getDate(&RTCC_struct, &data->tm_mday, &data->tm_mon, &data->tm_year, &data->tm_wday);
}