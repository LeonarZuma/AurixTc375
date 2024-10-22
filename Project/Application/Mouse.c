#include "App_bsp.h"
#include "Mouse.h"

AppBtns_Buttons btn0_click;         /*!<Button 0 global structure configuration containing the state machine data>*/
AppBtns_Buttons btn4_click;         /*!<Button 4 global structure configuration containing the state machine data>*/
AppBtns_Buttons btn5_click;         /*!<Button 5 global structure configuration containing the state machine data>*/

static void DoubleClick_stMachine(AppBtns_Buttons  *btn_clickCnfg);

void Mouse_InitTask(void)
{    
    btn0_click.button = BTN_0;
    btn0_click.state = IDLE;
    btn0_click.timer = COUNTER_TO_RS;

    btn4_click.button = BTN_4;
    btn4_click.state = IDLE;
    btn4_click.timer = COUNTER_TO_RS;

    btn5_click.button = BTN_5;
    btn5_click.state = IDLE;
    btn5_click.timer = COUNTER_TO_RS;

    Button_Init(&btn0_click.btn_config, &MODULE_P21, 0, NULL);
    Button_Init(&btn4_click.btn_config, &MODULE_P21, 4, NULL);
    Button_Init(&btn5_click.btn_config, &MODULE_P21, 5, NULL);
}

void Mouse_PeriodicTask(void)
{
    DoubleClick_stMachine(&btn0_click);
    DoubleClick_stMachine(&btn4_click);
    DoubleClick_stMachine(&btn5_click);
}

static void DoubleClick_stMachine(AppBtns_Buttons *btn_clickCnfg)
{
    AppMsg_Message data2Write;
    uint8_t msg_rdy = FALSE;

    switch(btn_clickCnfg->state)
    {
        case IDLE :
            /* Detects first button pressed */
            if(Button_GetStatus(&btn_clickCnfg->btn_config) == BUTTON_PRESSED)
            {
                btn_clickCnfg->state = SINGLE_PRESS;
                /* Start the 300ms counter if there is a press */
                btn_clickCnfg->timer = COUNTER_TO_RS;

                data2Write.button = btn_clickCnfg->button;
                data2Write.click = SINGLE_PRESS;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Do nothing */
            }         
        break;
        
        case SINGLE_PRESS :
            if(Button_GetStatus(&btn_clickCnfg->btn_config) == BUTTON_PRESSED)
            {
                btn_clickCnfg->timer++;
            }
            else
            {                
                /* If the button is realesed before the timeout, transition to SINGLE RELEASE */
                btn_clickCnfg->state = SINGLE_RELEASE;
                btn_clickCnfg->timer = COUNTER_TO_RS;
            }
            /* Timeout reach, transition to HOLD*/
            if (btn_clickCnfg->timer > COUNTER_TO)
            {
                btn_clickCnfg->state = HOLD;
                btn_clickCnfg->timer = COUNTER_TO_RS;

                /* Send data to Queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = HOLD;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Do nothing */
            }
        break;
        
        case SINGLE_RELEASE :
            /* If the button is pressed before the timeout, transition to DOUBLE CLICK */
            if(Button_GetStatus(&btn_clickCnfg->btn_config) == BUTTON_PRESSED)
            {
                btn_clickCnfg->state = DOUBLE_CLICK;
                btn_clickCnfg->timer = COUNTER_TO_RS;

                /* Send mesasge to queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = DOUBLE_CLICK;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Increase timeout count */
                btn_clickCnfg->timer++;
            }
            /* If the timeout has been reach with no buttons pressed */
            if(btn_clickCnfg->timer > COUNTER_TO)
            {
                btn_clickCnfg->state = IDLE;
                btn_clickCnfg->timer = COUNTER_TO_RS;

                /* Send data to Queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = IDLE;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Do nothing */
            }
        break;
        
        case DOUBLE_CLICK :
            /* If the button is not realeased increase timeoutCounter */
            if(Button_GetStatus(&btn_clickCnfg->btn_config) == BUTTON_PRESSED)
            {
                btn_clickCnfg->timer++;
            }
            else
            {
                /* If the button is realesed before the timeout, transition to IDLE */
                btn_clickCnfg->state = IDLE;
                btn_clickCnfg->timer = COUNTER_TO_RS;

                /* Send data to Queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = IDLE;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            /* Timeout reach, transition to HOLD*/
            if (btn_clickCnfg->timer > COUNTER_TO)
            {
                btn_clickCnfg->state = HOLD;
                btn_clickCnfg->timer = COUNTER_TO_RS;

                /* Send data to Queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = HOLD;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Do nothing */
            }
        break;
        
        case HOLD :
            // if state jumps here is a hold click
            // wait until botton is released
            if(Button_GetStatus(&btn_clickCnfg->btn_config) == BUTTON_RELEASED)
            {
                btn_clickCnfg->state = IDLE;

                /* Send data to Queue */
                data2Write.button = btn_clickCnfg->button;
                data2Write.click = IDLE;
                AppQueue_writeDataMutex(&shared_queue, &data2Write, MUTEX_uS_WAIT);
            }
            else
            {
                /* Do nothing */
            }
        break;
        
        default :
          /* if jump here is a error */
        break;
    }
}