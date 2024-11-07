#ifndef CLOCK_H_
#define CLOCK_H_
/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "bsp.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define IFX_INTPRIO_GPSR0_SR0    11

#ifndef GPSR0
    /*Software interrupt group 0*/
    #define GPSR0                     0
#endif

/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/
#define CANTX_TIME_MSG_ID         (0x212)
#define CANTX_DATE_MSG_ID         (0x201)
#define CANTX_TIME_PDU_BYTES      (3)
#define CANTX_DATE_PDU_BYTES      (4)

typedef enum
{
    CLOCK_IDLE = 0,
    CLOCK_MESSAGE,
    CNFG_TIME,
    CNFG_DATE,
    CNFG_ALARM,
    CLOCK_ERROR,
    CLOCK_OK,
} CSM_states;

typedef struct
{
    uint8_t state;              /* TRUE (1) if we have read data */
    uint8_t size;               /* How many elements has been read */
    App_Message data[8];        /* Contains the read data from the queue */
}appclock_ssm2rtcc_data_t;

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/
extern AppQue_Queue ssm2rtcc_queue;

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

void AppClock_initTask(void);

void AppClock_periodicTask(void);

void AppClock_RTCCUpdate_Callback(void);

#endif