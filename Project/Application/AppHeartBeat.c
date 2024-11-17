/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include "AppHeartBeat.h"
#include "Led_Driver.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

/**
 * @brief   ** This functions calls a single led configuration as the initialization **
 *
 * The AppHeartbeat has an asigned port-pin by default that depends on the core where is going to be 
 * running. This configures a predefined port-pin to be an output. 
 *
 * @note This is function is called once by the Ecu
 */
void AppHeartBeat_initTask(void)
{
    Led_Init(PORT_00, PIN_5);
}

/**
 * @brief   ** This functions alternates the led state from 0 to 1 to perform a blink **
 *
 * The led blinking is performed by a state toggle every time the function is called
 *
 * @note This is function is called periodically as a register Task in the Scheduler
 */
void AppHeartBeat_periodicTask(void)
{
    Led_togglePin(PORT_00, PIN_5);
}

/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
