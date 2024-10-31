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
static IfxCan_Can Can;
static IfxCan_Can_Config Can_Config;
static IfxCan_Can_Node Can_Node;
static IfxCan_Can_NodeConfig Can_Node_Config;
static IfxCan_Filter Can_Dst_Filter;
static IfxCan_Message Tx_Message[TX_MSG_NO];
static uint8 messageFlag;

/*Define a structure that contains the pins to be configured as CAN pins*/
static IFX_CONST IfxCan_Can_Pins Can_Pins =
{
    .txPin      = &IfxCan_TXD13_P33_4_OUT,
    .txPinMode  = IfxPort_OutputMode_pushPull,
    .rxPin      = &IfxCan_RXD13B_P33_5_IN,
    .rxPinMode  = IfxPort_InputMode_pullUp,
    .padDriver  = IfxPort_PadDriver_cmosAutomotiveSpeed4
};

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
void AppClock_CAN_Init(void)
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
    Can_Node_Config.nodeId            = IfxCan_NodeId_3;              //Assign source CAN node to CAN node 1
    Can_Node_Config.frame.mode        = IfxCan_FrameMode_standard;//Classic mode, 8 bytes frames
    Can_Node_Config.frame.type        = IfxCan_FrameType_transmit;//define the frame to be the transmitting one


    /* Configure Tx buffer for transmision */
    Can_Node_Config.txConfig.txMode = IfxCan_TxMode_fifo;
    Can_Node_Config.txConfig.txFifoQueueSize = 8;

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
        Tx_Message[index].frameMode        = IfxCan_FrameMode_standard;           /*classic frame*/
        Tx_Message[index].storeInTxFifoQueue   = TRUE;           /*classic frame*/

    }
}

void AppClock_Can_SendTime(uint8_t *data)
{
    IfxCan_Can_sendMessage( &Can_Node, &Tx_Message[0], (uint32*)&data[ 0u ] );
}