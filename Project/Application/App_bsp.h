#ifndef _BSP_H_
#define _BSP_H_

#include <stdint.h>
#include "IfxStm.h"
#include "IfxPort.h"
#include "IfxPort_Io.h"

#include "Button.h"
#include "Scheduler.h"
#include "Queue.h"

#define IDLE                (0U)        /*!<State machine IDLE state>*/
#define SINGLE_PRESS        (1U)        /*!<State machine SINGLE PRESS state>*/
#define SINGLE_RELEASE      (2U)        /*!<State machine SINGLE RELEASE state>*/
#define DOUBLE_CLICK        (3U)        /*!<State machine DOUBLE CLICK state>*/
#define HOLD                (4U)        /*!<State machine HOLD state>*/

#define BTN_0               (0U)        /*!<Button 0 index >*/
#define BTN_4               (1U)        /*!<Button 4 index >*/
#define BTN_5               (2U)        /*!<Button 5 index >*/

#define COUNTER_TO          (6U)        /*!<Counter Timeout max count>*/
#define COUNTER_TO_RS       (0U)        /*!<Counter Timeout reset count>*/
#define MUTEX_uS_WAIT       (100U)      /*!<uS Mutex wait time>*/

typedef struct _AppMsg_Message
{
    uint8_t button;  /*button can be BTN_0, BTN_1 or BTN_2*/
    uint8_t click;   /*click can be SINGLE, DOUBLE or HOLD*/
}AppMsg_Message;

typedef struct _AppBtns_Buttons
{
    uint8_t button;  /*button to use (BTN_0, BTN_1 or BTN_2)*/
    uint8_t state;   /*state of the button state machine*/
    uint8_t timer;   /*300ms timer ID*/
    /*add here as many elemnts you will use in your state machine*/
    Btn_Config btn_config;
}AppBtns_Buttons;

extern AppQue_Queue shared_queue;

#endif