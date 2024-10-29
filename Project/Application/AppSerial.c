
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "AppSerial.h"

#include "bsp.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*Can configuration structures*/
IfxCan_Can Can;
IfxCan_Can_Config Can_Config;
IfxCan_Can_Node Can_Node;
IfxCan_Can_NodeConfig Can_Node_Config;
IfxCan_Filter Can_Dst_Filter;
IfxCan_Message Tx_Message[TX_MSG_NO];
IfxCan_Message Rx_Message;
uint8 Rx_Data[3u][MSG_PDU_BYTES];
uint8 messageFlag;

/*Define a structure that contains the pins to be configured as CAN pins*/
IFX_CONST IfxCan_Can_Pins Can_Pins =
{
    .txPin      = &IfxCan_TXD10_P00_0_OUT,
    .txPinMode  = IfxPort_OutputMode_pushPull,
    .rxPin      = &IfxCan_RXD10C_P23_0_IN,
    .rxPinMode  = IfxPort_InputMode_pullUp,
    .padDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed4
};

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

static void CAN_Init(void);

static void Queue_CAN2SSM_Init(void);

static void Queue_SSM2RTCC_Init(void);

static uint16_t YearPdu_ToAppMessage(uint8_t* year);

static void Serial_State_Machine(void);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/


void AppSerial_initTask( void )
{
    CAN_Init();
    Queue_CAN2SSM_Init();
    Queue_SSM2RTCC_Init();
}

void AppSerial_periodicTask( void )
{
    
    Serial_State_Machine();
    
}

IFX_INTERRUPT( CanIsr_RxHandler, 0, ISR_PRIORITY_CAN_RX )
{
    App_Pdu data2Write;
    /* local size container to take the number of receive bytes */
    uint8_t size = 0;

    /*!< Clear the "Rx FIFO New message" interrupt flag */
    IfxCan_Node_clearInterruptFlag(Can_Node.node, IfxCan_Interrupt_rxFifo0NewMessage);

    /*!< Read the received CAN message */
    IfxCan_Can_readMessage(&Can_Node, &Rx_Message, (uint32*)&data2Write.sdu);

    data2Write.pci = Rx_Message.messageId;

    /* The function extracts the payload and the id from the receive message. Putting the information inside a queue message to send */
    Serial_singleFrameRx( &data2Write.sdu, &size);
    
    /*!< set a breakpoint after the function  and see the message received using the debugger */
    messageFlag = 1u;

    /* Send message to queue*/
    AppQueue_writeDataIsr(&can2ssm_queue, &data2Write);
}

/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
static void Serial_singleFrameTx( uint8_t *data, uint8_t size )
{
    const uint8_t can_frame_size = 8;
    uint8_t local_data[can_frame_size];
    
    /* move to shift one position right the array elements */
    arrayCopy(data, local_data,can_frame_size, 1);
    arrayCopy(local_data, data, can_frame_size, 0);

    /* Insert the first data element */
    /* Set the MSN will always be zero */
    /* Set the LSN to the number of */
    if (size > 7)
    {
        size = 7;
    }
    else
    {
        /* Do nothing */
    }
    *data = size & (~0xFFF8);
}
    
static uint8_t Serial_singleFrameRx( uint8_t *data, uint8_t *size )
{
    const uint8_t can_frame_size = 8;
    uint8_t local_data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t local_validation = CAN_SING_FRAME_INVALID;
    /* We are taking out the value of size from the CAN frame */
    *size = *data;
    if(*data <= 0x07)
    {
        *data = 0;
        local_validation = CAN_SING_FRAME_VALID;
        arrayCopy(data, local_data, can_frame_size, -1);
        arrayCopy(local_data, data, can_frame_size, 0);
    }
    else
    {
        /* Do nothing */
    }
    return local_validation;
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
    uint8_t days_by_month[12] = {31, (28 + ((year % 4) == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if((1 <= days && days <= days_by_month[month]) &&
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

static void CAN_Init(void)
{
    /*load default CAN module configuration into configuration structure*/
    IfxCan_Can_initModuleConfig( &Can_Config, &MODULE_CAN1 );

    /*initialize CAN module with the default configuration*/
    IfxCan_Can_initModule( &Can, &Can_Config );

    /*load default CAN node configuration into configuration structure*/
    IfxCan_Can_initNodeConfig( &Can_Node_Config, &Can );

    /*Set can configuration for node 0, baudrate, frame mode, etc..*/
    Can_Node_Config.pins              = &Can_Pins;
    Can_Node_Config.baudRate.baudrate = 100000u;
    Can_Node_Config.nodeId            = IfxCan_NodeId_0;              //Assign source CAN node to CAN node 1
    Can_Node_Config.frame.mode        = IfxCan_FrameMode_fdLong;//Classic mode, 8 bytes frames
    Can_Node_Config.frame.type        = IfxCan_FrameType_transmitAndReceive;//define the frame to be the transmitting one
    
    Can_Node_Config.interruptConfig.rxFifo0NewMessageEnabled                = TRUE;                         /*!< Once the message is stored in the FIFO RX buffer, raise the interrupt */
    Can_Node_Config.interruptConfig.rxf0n.priority                          = ISR_PRIORITY_CAN_RX;           //define the transmission complete interrupt priority
    Can_Node_Config.interruptConfig.rxf0n.interruptLine                     = IfxCan_InterruptLine_1;   //assign the interrupt line 1 to the receive interrupt
    Can_Node_Config.interruptConfig.rxf0n.typeOfService                     = IfxSrc_Tos_cpu0;          //receive interrupt service routine should be serviced by the CPU0

    Can_Node_Config.rxConfig.rxMode                                         = IfxCan_RxMode_fifo0;          /*!< Setting the Rx mode as FIFO 1  */
    Can_Node_Config.rxConfig.rxFifo0DataFieldSize                           = IfxCan_DataFieldSize_8;       /*!< Datafield 8 */
    Can_Node_Config.rxConfig.rxFifo0Size                                    = 3u;                          /*!< FIFO with 3 elements */
    Can_Node_Config.rxConfig.rxFifo0OperatingMode                           = IfxCan_RxFifoMode_overwrite;  /*! FIFO set as overwriting */

    /* Configure global filtering */
    Can_Node_Config.filterConfig.standardFilterForNonMatchingFrames = IfxCan_NonMatchingFrame_reject;

    /* Configure Tx buffer for transmision */
    Can_Node_Config.txConfig.txMode = IfxCan_TxMode_fifo;
    Can_Node_Config.txConfig.txFifoQueueSize = 8;
    Can_Node_Config.txConfig.txBufferDataFieldSize = 8;

    /* initialize the source CAN node with the modified configuration*/
    IfxCan_Can_initNode( &Can_Node, &Can_Node_Config );

    for(uint8_t index = 0; index < TX_MSG_NO; index++)
    {
        /* Initialization of the TX message with the default configuration */
        IfxCan_Can_initMessage( &Tx_Message[index] );
        
        /*Configure the can frame to send*/
        Tx_Message[index].messageId        = 0x201 + (index * 0x11);                            /*ID*/            
        Tx_Message[index].messageIdLength  = IfxCan_MessageIdLength_standard;  /*11 bit ID message*/
        Tx_Message[index].dataLengthCode   = IfxCan_DataLengthCode_8;          /*8 byes to send*/
        Tx_Message[index].frameMode        = IfxCan_FrameMode_fdLong;           /*classic frame*/
    }

    /* Initialization of the TX message with the default configuration */
    IfxCan_Can_initMessage( &Rx_Message );

    Rx_Message.bufferNumber     = 0u;                               /*!< Buffer number */
    Rx_Message.dataLengthCode   = IfxCan_DataLengthCode_8;          /*!< Data lenght code ofn 8 bits */
    Rx_Message.frameMode        = IfxCan_FrameMode_fdLong;        /*!< Frame mod as standard, we  can change it to FD */
    Rx_Message.readFromRxFifo0  = TRUE;                             /*!< Read from the FIFO 1 */

    /*Configure the reception filter to accept only 0x111, 0x112 and 0x113 IDs*/
    Can_Dst_Filter.number               = 0u;
    Can_Dst_Filter.type                 = IfxCan_FilterType_range;
    Can_Dst_Filter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxFifo0;
    Can_Dst_Filter.id1                  = 0x111;
    Can_Dst_Filter.id2                  = 0x113;
    Can_Dst_Filter.rxBufferOffset       = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter( &Can_Node, &Can_Dst_Filter );
}

static void Queue_CAN2SSM_Init(void)
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

static void Queue_SSM2RTCC_Init(void)
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

static uint16_t YearPdu_ToAppMessage(uint8_t* year)
{
    return ((year[0] >> 4) * 1000) + ((year[0] & 0x0F) * 100) + ((year[1] >> 4) * 10) + (year[1] & 0x0F);
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
                    case 0x111:
                        current_state = TIME;
                        break;
                    case 0x112:
                        current_state = DATE;
                        break;
                    case 0x113:
                        current_state = ALARM;
                        break;
                    default:
                        current_state = ERROR;
                        break;
                }
                break;
            case TIME:
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
                year = YearPdu_ToAppMessage(&data2Read.sdu[YR1]);
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
                Serial_singleFrameTx( &can_datatx, 1);

                /* Send NOK message via CAN */
                IfxCan_Can_sendMessage( &Can_Node, &Tx_Message[1], (uint32*)&can_datatx[ 0u ] );

                break;

            case OK:
                /* We go back to the first state after the machine logic has been complete */
                current_state = IDLE;
                
                /* Send the message from SSM To RTCC queue */
                AppQueue_writeDataMutex(&ssm2rtcc_queue, &data2Write, 10);
                
                /* Packing bytes to send via CAN*/
                can_datatx[0] = 0x55;
                Serial_singleFrameTx( &can_datatx, 1);

                /* Send OK message via CAN */
                IfxCan_Can_sendMessage( &Can_Node, &Tx_Message, (uint32*)&can_datatx[ 0u ] );

                break;

            default:
                break;
        }
        /* this while loop check two things if there are already available messages and if so complete the whole loop (IDLE->MESSAGE->)*/
    }while((message_in_queue == FALSE) || (current_state != IDLE));
}