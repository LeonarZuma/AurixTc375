/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "stdint.h"
#include "Phase1.h"
#include "AppClock.h"
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

static void AppClock_StateMachine(App_Message *data2Read_ptr);

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
    CAN_Init_AppClock();
}

void AppClock_periodicTask( void )
{

    App_Message data2Read;

    while (FALSE == AppQueue_isQueueEmpty(&ssm2rtcc_queue))
    {
        /* read a value from the queue and process it */
        AppQueue_readDataIsr(&ssm2rtcc_queue, &data2Read);
        /* Execute state machine with the elements of the queue that has been read */
        AppClock_StateMachine(&data2Read);
    }

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

static void AppClock_StateMachine(App_Message *data2Read_ptr)
{
    /* create a queue message container to write for the rtcc queue */
    App_Message data2Write;

    switch (data2Read_ptr->msg)
    {
        case SERIAL_MSG_TIME:
            if (TRUE == AppRtcc_setTime(&RTCC_struct, data2Read_ptr->tm.tm_hour, data2Read_ptr->tm.tm_min, data2Read_ptr->tm.tm_sec))
            {
                data2Write.msg = CLOCK_OK;
            }
            else
            {
                data2Write.msg = CLOCK_ERROR;
            }

            /* Send the message from SSM To RTCC queue */
            AppQueue_writeDataMutex(&ssm2rtcc_queue, &data2Write, MUTEX_uS_WAIT);
            break;
        case SERIAL_MSG_DATE:
            if (TRUE == AppRtcc_setDate(&RTCC_struct, data2Read_ptr->tm.tm_mday, data2Read_ptr->tm.tm_mon, data2Read_ptr->tm.tm_year))
            {
                data2Write.msg = CLOCK_OK;
            }
            else
            {
                data2Write.msg = CLOCK_ERROR;
            }

            /* Send the message from SSM To RTCC queue */
            AppQueue_writeDataMutex(&ssm2rtcc_queue, &data2Write, MUTEX_uS_WAIT);
            break;
        case SERIAL_MSG_ALARM:
            if (TRUE == AppRtcc_setAlarm(&RTCC_struct, data2Read_ptr->tm.tm_hour, data2Read_ptr->tm.tm_min))
            {
                data2Write.msg = CLOCK_OK;
            }
            else
            {
                data2Write.msg = CLOCK_ERROR;
            }

            /* Send the message from SSM To RTCC queue */
            AppQueue_writeDataMutex(&ssm2rtcc_queue, &data2Write, MUTEX_uS_WAIT);
            break;

        case CLOCK_ERROR:
            /* retry the set operation */
            /* avoiding the read of a new value from the queue */
            break;

        case CLOCK_OK:
            /* To do, lets see if we need to implement something */
            break;
            
        default:
            break;
    }
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
    CanTp_SingleFrameTx(datatx, CANTX_TIME_PDU_BYTES);

    /* Send time over CAN */
    Can_Retry_Send_Message((uint16_t)CANTX_TIME_MSG_ID, (uint8_t *)&datatx, CAN_SEND_ATTEMPS);

    datatx[0] = AppClock_Can_Decimal2BCD(data->tm_mday);
    datatx[1] = AppClock_Can_Decimal2BCD(data->tm_mon);
    datatx[2] = AppClock_Can_Decimal2BCD((uint8_t)(data->tm_year /100));
    datatx[3] = AppClock_Can_Decimal2BCD((uint8_t)(data->tm_year % 100));

    /* Pack message in CAN-TP format */
    CanTp_SingleFrameTx(datatx, CANTX_DATE_PDU_BYTES);

    /* Send date over CAN */
    Can_Send_Message((uint16_t)CANTX_DATE_MSG_ID, (uint8_t *)&datatx);
}

static void AppClock_getTimeDate(App_TmTime *data)
{
    // /* Create the string to print the current time hour, minutes and seconds*/
    AppRtcc_getTime(&RTCC_struct, &data->tm_hour, &data->tm_min, &data->tm_sec);

    // /* Create the string to print the current Date Month, Day, Year, Weekday */
    AppRtcc_getDate(&RTCC_struct, &data->tm_mday, &data->tm_mon, &data->tm_year, &data->tm_wday);
}