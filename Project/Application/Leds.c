#include "App_bsp.h"
#include "Leds.h"


void Leds_InitTask(void)
{
    /*configure the pin */
    IfxPort_setPinMode(&MODULE_P00, led0, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led0, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    IfxPort_setPinMode(&MODULE_P00, led1, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led1, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    IfxPort_setPinMode(&MODULE_P00, led2, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led2, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    IfxPort_setPinMode(&MODULE_P00, led3, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led3, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    IfxPort_setPinMode(&MODULE_P00, led4, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led4, IfxPort_PadDriver_cmosAutomotiveSpeed1);

    IfxPort_setPinMode(&MODULE_P00, led5, IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(&MODULE_P00, led5, IfxPort_PadDriver_cmosAutomotiveSpeed1);
}

void Leds_PeriodicTask(void)
{
    AppMsg_Message data2Read;

    uint8_t leds[3][2] = {{led2, led3},{led0, led1},{led4, led5}}; /* reaplce the number with macros with names LEDX_pin */

    if (AppQueue_readDataMutex(&shared_queue, &data2Read, MUTEX_uS_WAIT) == TRUE)
    {
        switch (data2Read.click)
        {
        case SINGLE_PRESS:
            IfxPort_setPinHigh(&MODULE_P00,leds[data2Read.button][0]);
            break;

        case DOUBLE_CLICK:
            IfxPort_setPinLow(&MODULE_P00,leds[data2Read.button][0]);
            IfxPort_setPinHigh(&MODULE_P00,leds[data2Read.button][1]);
            break;

        case HOLD:
            IfxPort_setPinHigh(&MODULE_P00,leds[data2Read.button][0]);
            IfxPort_setPinHigh(&MODULE_P00,leds[data2Read.button][1]);
            break;

        case IDLE:
            IfxPort_setPinLow(&MODULE_P00,leds[data2Read.button][0]);
            IfxPort_setPinLow(&MODULE_P00,leds[data2Read.button][1]);
            break;
        
        default:
            break;
        }
    }
}