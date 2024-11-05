
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "AppSerial.h"
#include "Can_Driver.h"
#include "bsp.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/* Queue creation for inter component comunication */
AppQue_Queue can2ssm_queue;
AppQue_Queue ssm2rtcc_queue;

App_Pdu buffer_can2ssm[QUEUE_BUFFER_SIZE];
App_Message buffer_ssm2rtcc[QUEUE_BUFFER_SIZE];

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/
static void Serial_singleFrameTx( uint8_t *data, uint8_t size );
    
static uint8_t Serial_singleFrameRx( uint8_t *data, uint8_t *size );

static uint8_t Serial_validateTime( uint8_t hour, uint8_t minutes, uint8_t seconds ); 

static uint8_t Serial_validateDate( uint8_t days, uint8_t month, uint16_t year );

static uint8_t Serial_validateLeapYear( uint32_t year );

static uint8_t Serial_getWeekDay( uint8_t days, uint8_t month, uint16_t year );

static void Serial_Queue_CAN2SSM_Init(void);

static void Serial_Queue_SSM2RTCC_Init(void);

static uint8_t Serial_BCD2Decimal(uint8_t data);

static void Serial_CanRxData_BCD2Decimal(uint8_t *data, uint8_t size);

static void Serial_State_Machine(void);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/


void AppSerial_initTask( void )
{
    AppSerial_CAN_Init();
    Serial_Queue_CAN2SSM_Init();
    Serial_Queue_SSM2RTCC_Init();
}

void AppSerial_periodicTask( void )
{
    
    Serial_State_Machine();
    
}

void Callback_CanRx2Queue(uint8_t *datarx, uint16_t message_id)
{
    /* Container for the input message to send to the queue */
    App_Pdu data2Write;
    /* Write the id to the message to send by Queue */
    data2Write.pci = message_id;

    /* local size container to take the number of receive bytes */
    uint8_t size = 0;

    arrayCopy(datarx, data2Write.sdu, MSG_PDU_BYTES, 0);

    /* The function extracts the payload and the id from the receive message. Putting the information inside a queue message to send */
    Serial_singleFrameRx((uint8_t *)&data2Write.sdu, &size);

    /* Send message to queue*/
    AppQueue_writeDataIsr(&can2ssm_queue, &data2Write);

}
/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
static void Serial_singleFrameTx( uint8_t *data, uint8_t size )
{
    CanTp_SingleFrameTx(data, size);
}
    
static uint8_t Serial_singleFrameRx( uint8_t *data, uint8_t *size )
{
    return CanTp_SingleFrameRx(data, size);
}

static uint8_t Serial_validateTime( uint8_t hour, uint8_t minutes, uint8_t seconds )
{
    uint8_t setTime = FALSE;
    /* Validate if the time is acceptable */
    if ((0 <= hour && hour <= APPSERIAL_MAX_HRS) && 
    (0 <= minutes && minutes <= APPSERIAL_MAX_MIN) && 
    (0 <= seconds && seconds <= APPSERIAL_MAX_SEC))
    {
        setTime = TRUE;
    }
    else
    {
        /* Do nothing, no valid data time */
    }
    return setTime;
}

static uint8_t Serial_validateDate( uint8_t days, uint8_t month, uint16_t year )
{
    uint8_t local_validation = FALSE;
    uint8_t days_by_month[12] = {31, (28 + Serial_validateLeapYear(year)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if((1 <= days && days <= days_by_month[month - 1]) &&
     (1 <= month && month <= APPSERIAL_MAX_MOS) && 
     (APPSERIAL_MIN_YEAR <= year && year <= APPSERIAL_MAX_YEAR))
    {
        local_validation = TRUE;
    }
    else
    {
        /* do nothing, keep the default value for local validation */
    }
    return local_validation;
}

static uint8_t Serial_validateLeapYear( uint32_t year )
{
    /* check if the receive year is a leap year TRUE (1)*/
    return ((year % 4) == 0);
}

static uint8_t Serial_getWeekDay( uint8_t days, uint8_t month, uint16_t year )
{
    uint16_t constVal = year;
    uint8_t weekday = 0;
    uint8_t lutTable[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    /* This numbers can be consider magic numbers, because they dont have an specific */
    constVal -= (month < 3);
    weekday = ((constVal + (constVal / 4) - (constVal / 100) + (constVal / 400) + lutTable[month - 1] + days) % 7);
    
    return weekday;
}

static void Serial_Queue_CAN2SSM_Init(void)
{
    
    /* Set the buffer for the Queue */
    can2ssm_queue.buffer = (void*)buffer_can2ssm;
    /* Queue lenght must be the same or less than the buffer size */
    can2ssm_queue.elements = QUEUE_BUFFER_SIZE;
    /* The size of a single element */
    can2ssm_queue.size = sizeof(App_Pdu);

    /* Init queue Function call */
    AppQueue_initQueue(&can2ssm_queue);
}

static void Serial_Queue_SSM2RTCC_Init(void)
{
    
    /* Set the buffer for the Queue */
    ssm2rtcc_queue.buffer = (void*)buffer_ssm2rtcc;
    /* Queue lenght must be the same or less than the buffer size */
    ssm2rtcc_queue.elements = QUEUE_BUFFER_SIZE;
    /* The size of a single element */
    ssm2rtcc_queue.size = sizeof(App_Message);

    /* Init queue Function call */
    AppQueue_initQueue(&ssm2rtcc_queue);
}

static uint8_t Serial_BCD2Decimal(uint8_t data)
{
    uint8_t tens = (data >> 0x4) * (0xA);
    uint8_t units = data & 0xF;
    return (tens + units);
}

static void Serial_CanRxData_BCD2Decimal(uint8_t *data, uint8_t size)
{
    for (uint8_t index = 0; index < size; index++)
    {
        data[index] = Serial_BCD2Decimal(data[index]);
    }
}

static void Serial_State_Machine(void)
{
    /* create a queue message container to write for the rtcc queue */
    App_Message data2Write;

    /* create a queue message container */
    App_Pdu data2Read;

    /* define the init SSM state */
    SSM_States current_state = IDLE;

    /* to check the queue current state */
    uint8_t message_in_queue = FALSE;

    /* to convert 2 bytes array to a single 16 bits value */
    uint16_t year = 0;

    /* to chekc if the receive date is a valid one */
    uint8_t valid_date = 0;

    /* Can data transmission */
    uint8_t can_datatx[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    /* create a queue message container for the Tx queue that is sharing the message time configurationn */
    
    /* if data in queue, keep reading until queue buffer is empty */
    do
    {
        /* execute the complete state machine from begining to end for every message in buffer */
        /* switch case */
        switch (current_state)
        {
            case IDLE:
                /* check the queue if there is a message already available */
                message_in_queue = AppQueue_isQueueEmpty(&can2ssm_queue);
                if( message_in_queue == FALSE)
                {
                    current_state = MESSAGE;
                    AppQueue_readDataIsr(&can2ssm_queue, &data2Read);
                }
                else
                {
                    /* the state reamains as IDLE and we reach the end of loop */
                }

                break;
            case MESSAGE:
                /* Check if the receive message is valid */
                switch (data2Read.pci)
                {
                    case CANRX_TIME_MSG_ID:
                        current_state = TIME;
                        break;
                    case CANRX_DATE_MSG_ID:
                        current_state = DATE;
                        break;
                    case CANRX_ALARM_MSG_ID:
                        current_state = ALARM;
                        break;
                    default:
                        current_state = ERROR;
                        break;
                }
                break;
            case TIME:
                /* Perform conversion from BCD type to Decimal for the income data */
                Serial_CanRxData_BCD2Decimal((uint8_t *)&data2Read.sdu, ID_111_PDU_BYTES);

                /* check if the receive time in payload is valid */
                if (Serial_validateTime(data2Read.sdu[HR],data2Read.sdu[MIN],data2Read.sdu[SEC]) == TRUE)
                {
                    /* Build the message to queue for the RTCC of type TIME */
                    data2Write.tm.tm_hour = data2Read.sdu[HR];
                    data2Write.tm.tm_min = data2Read.sdu[MIN];
                    data2Write.tm.tm_sec = data2Read.sdu[SEC];
                    data2Write.msg = SERIAL_MSG_TIME;

                    /* Change state to OK */
                    current_state = OK;
                }
                else
                {
                    /* no valid time, change to ERROR state */
                    current_state = ERROR;
                }
                break;
            case DATE:
                /* Perform conversion from BCD type to Decimal for the income data */  
                Serial_CanRxData_BCD2Decimal((uint8_t *)&data2Read.sdu, ID_112_PDU_BYTES);
                year = ((data2Read.sdu[YR1] * 100) + (data2Read.sdu[YR0]));

                /* check if the receive date is a valid one */
                valid_date = Serial_validateDate(data2Read.sdu[DAY], data2Read.sdu[MO], year);
                if (valid_date == TRUE)
                {
                    /* Change state to OK */
                    current_state = OK;

                    /* Build the message to queue for the RTCC of type TIME */
                    data2Write.tm.tm_mday = data2Read.sdu[DAY];
                    data2Write.tm.tm_mon = data2Read.sdu[MO];
                    data2Write.tm.tm_year = year;
                    data2Write.msg = SERIAL_MSG_DATE;
                }
                else
                {
                    /* no valid time, change to ERROR state */
                    current_state = ERROR;
                }
                break;

            case ALARM:
                /* Perform conversion from BCD type to Decimal for the income data */
                Serial_CanRxData_BCD2Decimal((uint8_t *)&data2Read.sdu, ID_113_PDU_BYTES);

                /* check if the alarm set time is a valid value */
                if (Serial_validateTime(data2Read.sdu[HR],data2Read.sdu[MIN], 0) == TRUE)
                {
                    /* Build the message to queue for the RTCC of type ALARM */
                    data2Write.tm.tm_hour = data2Read.sdu[HR];
                    data2Write.tm.tm_min = data2Read.sdu[MIN];
                    data2Write.msg = SERIAL_MSG_ALARM;

                    /* Change state to OK */
                    current_state = OK;
                }
                else
                {
                    /* no valid time, change to ERROR state */
                    current_state = ERROR;
                }
                break;
            case ERROR:

                /* We go back to the first state after the machine logic has been complete */
                current_state = IDLE;
                /* Packing bytes to send via CAN*/
                can_datatx[0] = 0xAA;
                Serial_singleFrameTx((uint8_t *)&can_datatx, 1);

                /* Send NOK message via CAN */
                Can_Send_Message((uint16_t)CANTX_STATUS_MSG_ID, (uint8_t*)&can_datatx[ 0u ]);

                break;

            case OK:
                /* We go back to the first state after the machine logic has been complete */
                current_state = IDLE;
                
                /* Send the message from SSM To RTCC queue */
                AppQueue_writeDataMutex(&ssm2rtcc_queue, &data2Write, MUTEX_uS_WAIT);
                
                /* Packing bytes to send via CAN*/
                can_datatx[0] = 0x55;
                Serial_singleFrameTx((uint8_t *)&can_datatx, 1);

                /* Send OK message via CAN */
                Can_Send_Message((uint16_t)CANTX_STATUS_MSG_ID, (uint8_t*)&can_datatx[ 0u ]);

                break;

            default:
                break;
        }
        /* this while loop check two things if there are already available messages and if so complete the whole loop (IDLE->MESSAGE->)*/
    }while((message_in_queue == FALSE) || (current_state != IDLE));
}