/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include "Led_Driver.h"
#include "IfxPort_Io.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
static ports_address_t port_table[] =
{
    {0, &MODULE_P00},
    {1, &MODULE_P01},
    {2, &MODULE_P02},
    {10, &MODULE_P10},
    {11, &MODULE_P11},
    {12, &MODULE_P12},
    {13, &MODULE_P13},
    {14, &MODULE_P14},
    {15, &MODULE_P15},
    {20, &MODULE_P20},
    {21, &MODULE_P21},
    {22, &MODULE_P22},
    {23, &MODULE_P23},
    {32, &MODULE_P32},
    {33, &MODULE_P33},
    {34, &MODULE_P34},
    {40, &MODULE_P40}
 };

void Led_Init(uint8_t port, uint8_t pin_number)
{
    /*configure the pin 5 on port 00 as ouput pushpull */
    IfxPort_setPinMode( &MODULE_P00, 5, IfxPort_Mode_outputPushPullGeneral );
    /*and cmos speed of 1*/
    IfxPort_setPinPadDriver( &MODULE_P00, 5, IfxPort_PadDriver_cmosAutomotiveSpeed1 );
}

void Led_togglePin(uint8_t port, uint8_t pin_number)
{
    IfxPort_togglePin( &MODULE_P00, 5);
}
/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
