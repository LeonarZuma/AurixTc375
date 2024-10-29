#ifndef SERIAL_H_
#define SERIAL_H_
/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "Can/Can/IfxCan_Can.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define TX_MSG_NO               (2U)
#define MSG_PDU_BYTES           (8U)
#define ISR_PRIORITY_CAN_RX     (1)

/** 
  * @defgroup <Time Bouds> Time count boundaries
  @{ */
#define APPSERIAL_MAX_SEC           (60)       /*!< MAX seconds count */
#define APPSERIAL_MAX_MIN           (60)       /*!< MAX minutes count */
#define APPSERIAL_MAX_HRS           (24)       /*!< MAX hours count */
#define APPSERIAL_MAX_MOS           (12)       /*!< MAX months count */
#define APPSERIAL_MAX_YEAR          (2100)     /*!< MAX years count */
#define APPSERIAL_MIN_YEAR          (1900)     /*!< MIN years count */

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
/*                       Declaration of global functions                      */
/*----------------------------------------------------------------------------*/

void AppSerial_initTask( void );

void AppSerial_periodicTask( void );

#endif