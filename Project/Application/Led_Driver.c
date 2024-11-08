/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <stdint.h>
#include "IfxPort_Io.h"
#include "Led_Driver.h"

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
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

/*----------------------------------------------------------------------------*/
/*                      Definition of private functions                       */
/*----------------------------------------------------------------------------*/
static ports_address_t Led_HashTable_Search(uint16_t id);

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/

void Led_Init(uint8_t port, uint8_t pin_number)
{
    ports_address_t pin_dir = {0, NULL};
    /* search in the hash table the pin direcction equivalence by index */
    pin_dir = Led_HashTable_Search(port);
    /*configure the pin on port as ouput pushpull */
    IfxPort_setPinMode(pin_dir.port_address, pin_number, IfxPort_Mode_outputPushPullGeneral );
    /*and cmos speed of 1*/
    IfxPort_setPinPadDriver(pin_dir.port_address, pin_number, IfxPort_PadDriver_cmosAutomotiveSpeed1 );
}

void Led_togglePin(uint8_t port, uint8_t pin_number)
{
    ports_address_t pin_dir = {0, NULL};
    /* search in the hash table the pin direcction equivalence by index */
    pin_dir = Led_HashTable_Search(port);

    IfxPort_togglePin(pin_dir.port_address, pin_number);
}
/*----------------------------------------------------------------------------*/
/*                         Implementation of local functions                  */
/*----------------------------------------------------------------------------*/
static ports_address_t Led_HashTable_Search(uint16_t id)
{
    /* container to save the matching value from the hash table */
    ports_address_t local_value = {0, NULL};
    /* flag to perform an early escape from the for loop */
    uint8_t flag = FALSE;

    for(uint8_t index = 0; index < REG_PORT_ADDR && !flag; index++)
    {
        if(id == port_table[index].id)
        {
            local_value.id = port_table[index].id;
            local_value.port_address = port_table[index].port_address;

            /* Changing the flag state to perform an early escape from the for loop */
            flag = TRUE;
        }
        else
        {
            /* do nothing */
        }
    }

    return local_value;
}