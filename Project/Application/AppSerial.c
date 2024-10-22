
/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "AppSerial.h"
#include "bsp.h"

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/
static void Serial_singleFrameTx( uint8_t *data, uint8_t size );
    
static uint8_t Serial_singleFrameRx( uint8_t *data, uint8_t *size );

static uint8_t Serial_validateTime( uint8_t hour, uint8_t minutes, uint8_t seconds ); 

static uint8_t Serial_validateDate( uint8_t days, uint8_t month, uint16_t year );

static uint8_t Serial_validateLeapYear( uint32_t year );

static uint8_t Serial_getWeekDay( uint8_t days, uint8_t month, uint16_t year );

/*----------------------------------------------------------------------------*/
/*                     Implementation of functions                            */
/*----------------------------------------------------------------------------*/


void AppSerial_initTask( void )
{
    
}

void AppSerial_periodicTask( void )
{
    
}

