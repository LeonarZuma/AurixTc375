#ifndef CAN_H_
#define CAN_H_

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/

#include "IfxCan_Can.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/

#define TX_MSG_NO                   (2U)

typedef struct
{
    IfxCan_Can Can;                                             /* CAN module handle                                 */
    IfxCan_Can_Config Can_Config;                                /* CAN module configuration structure                */
    IfxCan_Can_Node Can_Node;                                   /* CAN source node handle data structure              */
    IfxCan_Can_NodeConfig Can_Node_Config;                      /* CAN node configuration structure                  */
    IfxCan_Filter Can_Dst_Filter;                               /* CAN filter configuration structure                */
    IfxCan_Message Tx_Message[TX_MSG_NO];                       /* Transmitted CAN message structure                 */
    IfxCan_Message Rx_Message;                                  /* Received CAN message structure                    */
} mcmcanType;

typedef struct
{
    uint16_t txmessage_idx;
    IfxCan_Can_Node* Can_Node;
    IfxCan_Message* Tx_Message;
} Can_Txmsg_Config;

/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of global functions                      */
/*----------------------------------------------------------------------------*/

void AppClock_CAN_Init(void);

void AppSerial_CAN_Init(void);

void Can_Send_Message(uint16_t txmessage_idx, uint8_t *data);

uint8_t AppClock_Can_Decimal2BCD(uint8_t data);

#endif