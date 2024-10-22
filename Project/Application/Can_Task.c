#include <stdint.h>
#include "Can/Can/IfxCan_Can.h"

#include "App_bsp.h"
#include "Can_Task.h"

static uint8_t CheckFilter(uint8_t *message_data, uint8_t *message_filter, uint8_t data_size);

/*Can configuration structures*/
IfxCan_Can Can;
IfxCan_Can_Config Can_Config;
IfxCan_Can_Node Can_Node;
IfxCan_Can_NodeConfig Can_Node_Config;
IfxCan_Filter Can_Dst_Filter;
IfxCan_Message Tx_Message[TX_MSG_NO];
IfxCan_Message Rx_Message;
uint8 Rx_Data[3u][ 8u ];
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

uint8 Tx_Data[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

uint8 Rx_Filters[3][8] = {
    {0x4C, 0x45, 0x44, 0x31, 0x00, 0x00, 0x00, 0x00},
    {0x4C, 0x45, 0x44, 0x32, 0x00, 0x00, 0x00, 0x00},
    {0x4C, 0x45, 0x44, 0x33, 0x00, 0x00, 0x00, 0x00}
};

void InitCanTask_Core0(void)
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
    
    Can_Node_Config.interruptConfig.rxFifo0FullEnabled                      = TRUE; //once the message is stored in the dedicated RX buffer, raise the interrupt
    Can_Node_Config.interruptConfig.rxf0f.priority                          = ISR_PRIORITY_CAN_RX;           //define the transmission complete interrupt priority
    Can_Node_Config.interruptConfig.rxf0f.interruptLine                     = IfxCan_InterruptLine_1;   //assign the interrupt line 1 to the receive interrupt
    Can_Node_Config.interruptConfig.rxf0f.typeOfService                     = IfxSrc_Tos_cpu0;          //receive interrupt service routine should be serviced by the CPU0

    Can_Node_Config.rxConfig.rxMode                                         = IfxCan_RxMode_fifo0;          /*!< Setting the Rx mode as FIFO 1  */
    Can_Node_Config.rxConfig.rxFifo0DataFieldSize                           = IfxCan_DataFieldSize_8;       /*!< Datafield 8 */
    Can_Node_Config.rxConfig.rxFifo0Size                                    = 3u;                          /*!< FIFO with 3 elements */
    Can_Node_Config.rxConfig.rxFifo0OperatingMode                           = IfxCan_RxFifoMode_blocking;  /*! FIFO set as blocking */

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

    /*Configure the reception filter to accept only 0x177 IDs*/
    Can_Dst_Filter.number               = 0u;
    Can_Dst_Filter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxBuffer;
    Can_Dst_Filter.id1                  = 0x177;
    Can_Dst_Filter.rxBufferOffset       = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter( &Can_Node, &Can_Dst_Filter );
}

void PeriodicCanTask_Core0(void)
{
    uint32 msg_rx_no = 0;
    AppMsg_Message data2Write;

    /*echo the message received*/
    if( messageFlag == 1u )
    {
        messageFlag = 0u;

        msg_rx_no = IfxCan_Node_getRxFifo0FillLevel(Can_Node.node);

        while ( msg_rx_no > 0)
        {
            IfxCan_Can_readMessage( &Can_Node, &Rx_Message, (uint32*)&Rx_Data[--msg_rx_no]);
        }
        
        if (CheckFilter(&Rx_Data, &Rx_Filters[0], 8) == TRUE)
        {
            // Rx_Data[ 0u ]++;
            // IfxCan_Can_sendMessage( &Can_Node, &Tx_Message, (uint32*)&Rx_Data[ 0u ] );

            /* Send Message to turn on the leds */
            data2Write.button = 0;
            data2Write.click = SINGLE_PRESS;
            AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
        }        
        else if(CheckFilter(&Rx_Data, &Rx_Filters[1], 8) == TRUE)
        {
            /* Send Message to turn on the leds */
            data2Write.button = 1;
            data2Write.click = SINGLE_PRESS;
            AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
        }
        else if(CheckFilter(&Rx_Data, &Rx_Filters[2], 8) == TRUE)
        {
            /* Send Message to turn on the leds */
            data2Write.button = 2;
            data2Write.click = SINGLE_PRESS;
            AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
        }
        else
        {
            /* turning off all leds if no message is receive */
            for (uint8_t index = 0; index < TX_MSG_NO; index++)
            {
                /* Send Message to turn on the leds */
                data2Write.button = index;
                data2Write.click = IDLE;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
        }
    }
}

/*Program will jump here every time a message is received, we can read the message using the function
 * IfxCan_Can_readMessage and place the payload on any array we want.
 * only valid messages with the ID of 0x177 will be take them into account due the configured filter */
IFX_INTERRUPT( CanIsr_RxHandler, 0, ISR_PRIORITY_CAN_RX )
{
    uint32 index = 0;
    /* Clear the "Message stored to Dedicated RX Buffer" interrupt flag */
    IfxCan_Node_clearInterruptFlag(Can_Node.node, IfxCan_Interrupt_rxFifo0Full);
    
    /*set a breakpoint after the function  and see the message received using the debugger*/
    messageFlag = 1u;
}

static uint8_t CheckFilter(uint8_t *message_data, uint8_t *message_filter, uint8_t data_size)
{
    uint8_t approved = FALSE;
    for (uint8_t index = 0; index < data_size; index++)
    {
        if(message_data[index] != message_filter[index])
        {
            approved = FALSE;
            index = data_size;
        }
        else
        {
            approved = TRUE;
        }
    }
    return approved;
}