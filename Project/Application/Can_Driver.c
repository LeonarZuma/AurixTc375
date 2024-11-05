/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "stdint.h"
#include "bsp.h"

#include "Can_Driver.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*Can configuration structures*/
static mcmcanType mcmcan_node0;
static mcmcanType mcmcan_node1;

/*Define a structure that contains the pins to be configured as CAN pins*/
static IFX_CONST IfxCan_Can_Pins Can_Pins_node1 =
{
    .txPin      = &IfxCan_TXD13_P33_4_OUT,
    .txPinMode  = IfxPort_OutputMode_pushPull,
    .rxPin      = &IfxCan_RXD13B_P33_5_IN,
    .rxPinMode  = IfxPort_InputMode_pullUp,
    .padDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed4
};

static Can_Txmsg_Config txmessages_cfg[]=
{
    {0x122, &mcmcan_node0.Can_Node, &mcmcan_node0.Tx_Message[0]},
    {0x201, &mcmcan_node1.Can_Node, &mcmcan_node1.Tx_Message[0]},
    {0x212, &mcmcan_node1.Can_Node, &mcmcan_node1.Tx_Message[1]}
};

IFX_CONST IfxCan_Can_Pins Can_Pins_node0 =
{
    .txPin      = &IfxCan_TXD10_P00_0_OUT,
    .txPinMode  = IfxPort_OutputMode_pushPull,
    .rxPin      = &IfxCan_RXD10C_P23_0_IN,
    .rxPinMode  = IfxPort_InputMode_pullUp,
    .padDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed4
};

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/
static Can_Txmsg_Config Can_HashTable(uint16_t id);

/*----------------------------------------------------------------------------*/
/*                         Implementation of global functions                 */
/*----------------------------------------------------------------------------*/
void CAN_Init_AppClock(void)
{
    /*load default CAN module configuration into configuration structure*/
    IfxCan_Can_initModuleConfig( &mcmcan_node1.Can_Config, &MODULE_CAN1 );

    /*initialize CAN module with the default configuration*/
    IfxCan_Can_initModule( &mcmcan_node1.Can, &mcmcan_node1.Can_Config );

    /*load default CAN node configuration into configuration structure*/
    IfxCan_Can_initNodeConfig( &mcmcan_node1.Can_Node_Config, &mcmcan_node1.Can );

    /*Set can configuration for node 0, baudrate, frame mode, etc..*/
    mcmcan_node1.Can_Node_Config.pins              = &Can_Pins_node1;
    mcmcan_node1.Can_Node_Config.baudRate.baudrate = 100000u;
    mcmcan_node1.Can_Node_Config.nodeId            = IfxCan_NodeId_3;              //Assign source CAN node to CAN node 1
    mcmcan_node1.Can_Node_Config.frame.mode        = IfxCan_FrameMode_fdLong;//Classic mode, 8 bytes frames
    mcmcan_node1.Can_Node_Config.frame.type        = IfxCan_FrameType_transmit;//define the frame to be the transmitting one


    /* Configure Tx buffer for transmision */
    mcmcan_node1.Can_Node_Config.txConfig.txMode = IfxCan_TxMode_fifo;
    mcmcan_node1.Can_Node_Config.txConfig.txFifoQueueSize = MSG_PDU_BYTES;

    /* initialize the source CAN node with the modified configuration*/
    IfxCan_Can_initNode( &mcmcan_node1.Can_Node, &mcmcan_node1.Can_Node_Config );

    for(uint8_t index = 0; index < TX_MSG_NO; index++)
    {
        /* Initialization of the TX message with the default configuration */
        IfxCan_Can_initMessage( &mcmcan_node1.Tx_Message[index] );
        
        /*Configure the can frame to send*/
        mcmcan_node1.Tx_Message[index].messageId        = 0x201 + (index * 0x11);                            /*ID*/            
        mcmcan_node1.Tx_Message[index].messageIdLength  = IfxCan_MessageIdLength_standard;  /*11 bit ID message*/
        mcmcan_node1.Tx_Message[index].dataLengthCode   = IfxCan_DataLengthCode_8;          /*8 byes to send*/
        mcmcan_node1.Tx_Message[index].frameMode        = IfxCan_FrameMode_fdLong;           /*classic frame*/
        mcmcan_node1.Tx_Message[index].storeInTxFifoQueue   = TRUE;           /*classic frame*/

    }
}

void CAN_Init_AppSerial(void)
{
    /*load default CAN module configuration into configuration structure*/
    IfxCan_Can_initModuleConfig( &mcmcan_node0.Can_Config, &MODULE_CAN1 );

    /*initialize CAN module with the default configuration*/
    IfxCan_Can_initModule( &mcmcan_node0.Can, &mcmcan_node0.Can_Config );

    /*load default CAN node configuration into configuration structure*/
    IfxCan_Can_initNodeConfig( &mcmcan_node0.Can_Node_Config, &mcmcan_node0.Can );

    /*Set can configuration for node 0, baudrate, frame mode, etc..*/
    mcmcan_node0.Can_Node_Config.pins              = &Can_Pins_node0;
    mcmcan_node0.Can_Node_Config.baudRate.baudrate = 100000u;
    mcmcan_node0.Can_Node_Config.nodeId            = IfxCan_NodeId_0;              //Assign source CAN node to CAN node 1
    mcmcan_node0.Can_Node_Config.frame.mode        = IfxCan_FrameMode_fdLong;//Classic mode, 8 bytes frames
    mcmcan_node0.Can_Node_Config.frame.type        = IfxCan_FrameType_transmitAndReceive;//define the frame to be the transmitting one
    
    mcmcan_node0.Can_Node_Config.interruptConfig.rxFifo0NewMessageEnabled                = TRUE;                         /*!< Once the message is stored in the FIFO RX buffer, raise the interrupt */
    mcmcan_node0.Can_Node_Config.interruptConfig.rxf0n.priority                          = ISR_PRIORITY_CAN_RX;           //define the transmission complete interrupt priority
    mcmcan_node0.Can_Node_Config.interruptConfig.rxf0n.interruptLine                     = IfxCan_InterruptLine_1;   //assign the interrupt line 1 to the receive interrupt
    mcmcan_node0.Can_Node_Config.interruptConfig.rxf0n.typeOfService                     = IfxSrc_Tos_cpu0;          //receive interrupt service routine should be serviced by the CPU0

    mcmcan_node0.Can_Node_Config.rxConfig.rxMode                                         = IfxCan_RxMode_fifo0;          /*!< Setting the Rx mode as FIFO 1  */
    mcmcan_node0.Can_Node_Config.rxConfig.rxFifo0DataFieldSize                           = IfxCan_DataFieldSize_8;       /*!< Datafield 8 */
    mcmcan_node0.Can_Node_Config.rxConfig.rxFifo0Size                                    = 3u;                          /*!< FIFO with 3 elements */
    mcmcan_node0.Can_Node_Config.rxConfig.rxFifo0OperatingMode                           = IfxCan_RxFifoMode_overwrite;  /*! FIFO set as overwriting */

    /* Configure global filtering */
    mcmcan_node0.Can_Node_Config.filterConfig.standardFilterForNonMatchingFrames = IfxCan_NonMatchingFrame_reject;

    /* Configure Tx buffer for transmision */
    mcmcan_node0.Can_Node_Config.txConfig.txMode = IfxCan_TxMode_fifo;
    mcmcan_node0.Can_Node_Config.txConfig.txFifoQueueSize = 8;
    mcmcan_node0.Can_Node_Config.txConfig.txBufferDataFieldSize = MSG_PDU_BYTES;

    /* initialize the source CAN node with the modified configuration*/
    IfxCan_Can_initNode( &mcmcan_node0.Can_Node, &mcmcan_node0.Can_Node_Config );


    /* Initialization of the TX message with the default configuration */
    IfxCan_Can_initMessage( &mcmcan_node0.Tx_Message[0] );
    
    /*Configure the can frame to send*/
    mcmcan_node0.Tx_Message[0].messageId        = 0x122;                            /*ID*/            
    mcmcan_node0.Tx_Message[0].messageIdLength  = IfxCan_MessageIdLength_standard;  /*11 bit ID message*/
    mcmcan_node0.Tx_Message[0].dataLengthCode   = IfxCan_DataLengthCode_8;          /*8 byes to send*/
    mcmcan_node0.Tx_Message[0].frameMode        = IfxCan_FrameMode_fdLong;           /*classic frame*/

    /* Initialization of the TX message with the default configuration */
    IfxCan_Can_initMessage( &mcmcan_node0.Rx_Message );

    mcmcan_node0.Rx_Message.bufferNumber     = 0u;                               /*!< Buffer number */
    mcmcan_node0.Rx_Message.dataLengthCode   = IfxCan_DataLengthCode_8;          /*!< Data lenght code ofn 8 bits */
    mcmcan_node0.Rx_Message.frameMode        = IfxCan_FrameMode_fdLong;        /*!< Frame mod as standard, we  can change it to FD */
    mcmcan_node0.Rx_Message.readFromRxFifo0  = TRUE;                             /*!< Read from the FIFO 0 */

    /*Configure the reception filter to accept only 0x111, 0x112 and 0x113 IDs*/
    mcmcan_node0.Can_Dst_Filter.number               = 0u;
    mcmcan_node0.Can_Dst_Filter.type                 = IfxCan_FilterType_range;
    mcmcan_node0.Can_Dst_Filter.elementConfiguration = IfxCan_FilterElementConfiguration_storeInRxFifo0;
    mcmcan_node0.Can_Dst_Filter.id1                  = 0x111;
    mcmcan_node0.Can_Dst_Filter.id2                  = 0x113;
    mcmcan_node0.Can_Dst_Filter.rxBufferOffset       = IfxCan_RxBufferId_0;
    IfxCan_Can_setStandardFilter( &mcmcan_node0.Can_Node, &mcmcan_node0.Can_Dst_Filter );
}

void Can_Send_Message(uint16_t txmessage_idx, uint8_t *data)
{
    /* container to save the matching value from the hash table */
    Can_Txmsg_Config local_value;
    /* look using the hash table the corresponding data structure for a given message id */
    local_value = Can_HashTable(txmessage_idx);

    IfxCan_Can_sendMessage( local_value.Can_Node, local_value.Tx_Message, (uint32*)&data[ 0u ] );
}

uint8_t AppClock_Can_Decimal2BCD (uint8_t data)
{
    uint8_t tens = (data / 0xA) * 0x10;
    uint8_t units = data % 0xA;
    return (tens + units);
}

IFX_INTERRUPT( CanIsr_RxHandler, 0, ISR_PRIORITY_CAN_RX )
{
    /* Received CAN data matrix                */
    uint8 Rx_Data[MSG_PDU_BYTES];                           

    /*!< Clear the "Rx FIFO New message" interrupt flag */
    IfxCan_Node_clearInterruptFlag(mcmcan_node0.Can_Node.node, IfxCan_Interrupt_rxFifo0NewMessage);

    /*!< Read the received CAN message */
    IfxCan_Can_readMessage(&mcmcan_node0.Can_Node, &mcmcan_node0.Rx_Message, (uint32_t*)&Rx_Data);

    /* Used of callback function to avoid the usage of many resources from the AppSerial */
    /* This line performs a send to queue the receive data */
    AppSerial_Callback_CanRx2Queue((uint8_t*)&Rx_Data, mcmcan_node0.Rx_Message.messageId);
}

/*----------------------------------------------------------------------------*/
/*                         Implementation of private functions                */
/*----------------------------------------------------------------------------*/
static Can_Txmsg_Config Can_HashTable(uint16_t id)
{
    /* container to save the matching value from the hash table */
    Can_Txmsg_Config local_value = {0, NULL, NULL};
    /* flag to perform an early escape from the for loop */
    uint8_t flag = FALSE;

    for(uint8_t index = 0; index < CAN_TX_MESSAGES && !flag; index++)
    {
        if(txmessages_cfg[index].txmessage_idx == id)
        {
            local_value.txmessage_idx = txmessages_cfg[index].txmessage_idx;
            local_value.Can_Node = txmessages_cfg[index].Can_Node;
            local_value.Tx_Message = txmessages_cfg[index].Tx_Message;

            /* Changing the flag state to perform an early escape from the for loop */
            flag = TRUE;
        }
        else
        {
            /* do nothing */
        }
    }

    return local_value;
}
