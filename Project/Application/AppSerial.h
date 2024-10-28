#ifndef SERIAL_H_
#define SERIAL_H_
/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "Can/Can/IfxCan_Can.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define TX_MSG_NO               (3U)
#define MSG_PDU_BYTES           (8U)
#define ISR_PRIORITY_CAN_RX     (1)
#define QUEUE_BUFFER_SIZE       (8U)
//#define HEX_1900_TO_DEC         (DEC)
/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/
typedef struct _App_Pdu // Protocol Data Unit
{
    uint32 pci;     // Protocol Control Information
    uint8  sdu[8];  // Service Data Unit
} App_Pdu;

typedef enum
{
    IDLE = 0,
    MESSAGE,
    TIME,
    DATE,
    ALARM,
    ERROR,
    OK
} SSM_States;

typedef enum
{
    HR = 0,
    MIN,
    SEC
} Time_Payload;

typedef enum
{
    DAY = 0,
    MO,
    YR1,
    YR0
} DateYear_Payload;
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
/*                       Declaration of global functions                       */
/*----------------------------------------------------------------------------*/

void AppSerial_initTask( void );

void AppSerial_periodicTask( void );

#endif