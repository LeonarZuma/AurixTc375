
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


AppQue_Queue can2ssm_queue;

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

static void Serial_State_Machine(App_Pdu *data);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/


void AppSerial_initTask( void )
{
    CAN_Init();
    Queue_CAN2SSM_Init();
}

void AppSerial_periodicTask( void )
{
    /* create a queue message container */
    App_Pdu data2Read;
    /* while the queue is not empty, read and execute all message in queue */
    /* Todo: implement a secondary escape method from the while to avoid the risk of being stuck in a infinite loop */
    while (AppQueue_readDataIsr(&can2ssm_queue, &data2Read) == TRUE)
    {
        Serial_State_Machine(&data2Read);
    }
}

IFX_INTERRUPT( CanIsr_RxHandler, 0, ISR_PRIORITY_CAN_RX )
{
    App_Pdu data2Write;

    /*!< Clear the "Rx FIFO New message" interrupt flag */
    IfxCan_Node_clearInterruptFlag(Can_Node.node, IfxCan_Interrupt_rxFifo0NewMessage);

    /*!< Read the received CAN message */
    IfxCan_Can_readMessage(&Can_Node, &Rx_Message, (uint32*)&data2Write.sdu);

    data2Write.pci = Rx_Message.messageId;

    /* The function extracts the payload and the id from the receive message. Putting the information inside a queue message to send */
    Serial_singleFrameRx( &data2Write.sdu, &data2Write.pci);
    
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
    
}
    
static uint8_t Serial_singleFrameRx( uint8_t *data, uint8_t *size )
{
    uint8_t local_validation = 0;
    return local_validation;
}

static uint8_t Serial_validateTime( uint8_t hour, uint8_t minutes, uint8_t seconds )
{
    uint8_t local_validation = 0;
    return local_validation;
}

static uint8_t Serial_validateDate( uint8_t days, uint8_t month, uint16_t year )
{
    uint8_t local_validation = 0;
    return local_validation;
}

static uint8_t Serial_validateLeapYear( uint32_t year )
{
    uint8_t local_validation = 0;
    return local_validation;
}

static uint8_t Serial_getWeekDay( uint8_t days, uint8_t month, uint16_t year )
{
    uint8_t local_validation = 0;
    return local_validation;
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

    /* initialize the source CAN node with the modified configuration*/
    IfxCan_Can_initNode( &Can_Node, &Can_Node_Config );

    for(uint8_t index = 0; index < TX_MSG_NO; index++)
    {
        /* Initialization of the TX message with the default configuration */
        IfxCan_Can_initMessage( &Tx_Message[index] );
        
        /*Configure the can frame to send*/
        Tx_Message[index].messageId        = 0x001 + index;                            /*ID*/            
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
    App_Pdu buffer[QUEUE_BUFFER_SIZE];
    /* Set the buffer for the Queue */
    can2ssm_queue.buffer = (void*)buffer;
    /* Queue lenght must be the same or less than the buffer size */
    can2ssm_queue.elements = QUEUE_BUFFER_SIZE;
    /* The size of a single element */
    can2ssm_queue.size = sizeof(App_Pdu);

    /* Init queue Function call */
    AppQueue_initQueue(&can2ssm_queue);
}

static void Serial_State_Machine(App_Pdu *data)
{
    /* define the init SSM state */
    SSM_States current_state = IDLE;

    /* to check the queue current state */
    uint8_t message_in_queue = FALSE;

    /* create a queue message container for the Tx queue that is sharing the message time configurationn */
    
    /* if data in queue, keep reading until queue buffer is empty */
    do
    {
        /* execute the complete state machine from begining to end for every message in buffer */
        /* switch case */
        switch (current_state)
        {
            case IDLE:
                message_in_queue = AppQueue_isQueueEmpty(&can2ssm_queue);
                if( message_in_queue == FALSE)
                {
                    current_state = MESSAGE;
                    /* check the queue if there is a message already available */
                }
                else
                {
                    /* the state reamains as IDLE and we reach the end of loop */
                }
            case MESSAGE:

            case TIME:

            case DATE:

            case ALARM:

            case ERROR:
                break;

            case OK:
                break;

            default:
                break;
        }
        /* this while loop check two things if there are already available messages and if so complete the whole loop (IDLE->MESSAGE->)*/
    }while((message_in_queue == FALSE) && (current_state != IDLE));
}