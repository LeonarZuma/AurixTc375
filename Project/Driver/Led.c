/**
 * @file    <Led.h>
 * @brief   **This is a Driver to Setting up and manage a Led in a certain output **
 *
 * 
 * @note    
 */

#include <stdint.h>
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Led.h"

/**
 * @brief   ** Initialize a Led in a certain Pin configuration **
 *
 * Giving a pin number and address initialize a Led in that position including a pin as push-pull output
 *
 * @param[in]   led This contains the Led setting up parameters
 * @param[in]   pin_outputAddr Address for the output pin led
 * @param[in]   pinNumber outnput pin number
 *
 * @retval  None
 *
 * @note The taskPtr shouldn't be a NULL pointer
 */
void Led_Init(Led_Config *led, Ifx_P *port_ouputAddr, uint8_t pinNumber)
{
    /* Set Led pin out Address */
    led->pin_outputAddr = &port_ouputAddr->OUT.U;
    /* Set Led port out Address */
    led->port_ouputAddr = port_ouputAddr;
    /* Set Led pin out pin Number */
    led->pinNumber = pinNumber;

    /* Configure Pin as output push-pull */
    Led_pinCnfg(port_ouputAddr, pinNumber);
}

/**
 * @brief   ** Toggle Led state **
 *
 * After press then release, will execute a Function Task
 *
 * @param[in]   led This contains the Led setting up parameters
 *
 * @retval  None
 *
 * @note 
 */
void Led_Toggle(Led_Config *led)
{
    *led->pin_outputAddr ^= (1<<led->pinNumber);
}

/**
 * @brief   ** Write an output to a multiple pin Leds **
 *
 * Giving an array of configure leds, this functions writes a certain output in each pin depending on the
 * desired pin value configured. 
 *
 * @param[in]   led_ptr This contains the main address of a Led Config array with Leds setting up parameters
 * @param[in]   size The number of elements inside the Led_Config array
 * @param[in]   arrary_ptr This contains the addres of an array with the desired leds out configurations
 *
 * @retval  None
 *
 * @note 
 */
void Led_WriteArray(Led_Config *led_ptr, uint8_t size, uint8_t *array_ptr)
{
    /* Turn multiple leds with a certain pattern */
    
    for (uint8_t index = 0; index < size; index++)
    {
        /* clear pin out */
        led_ptr[index].port_ouputAddr->OUT.U &= ~(1 << led_ptr[index].pinNumber);
        led_ptr[index].port_ouputAddr->OUT.U |= array_ptr[index] << led_ptr[index].pinNumber;
    }
}

/**
 * @brief   ** Toggle Led state **
 *
 * After press then release, will execute a Function Task
 *
 * @param[in]   led This contains the Led setting up parameters
 *
 * @retval  None
 *
 * @note 
 */
void Led_pinCnfg(Ifx_P *port_ouputAddr, uint8_t pinNumber)
{
    int8_t module_pin = pinNumber % PINS_PER_REG;

    volatile Ifx_UReg_32Bit *iocr_reg[] = 
    {
        &port_ouputAddr->IOCR0.U,
        &port_ouputAddr->IOCR4.U,
        &port_ouputAddr->IOCR8.U,
        &port_ouputAddr->IOCR12.U
    };

    if((pinNumber >= 0)&&(pinNumber <= 15))
    {
        /* Clearing bits in register */
        *iocr_reg[(pinNumber/IOCR_REG_QTY)] &= ~(0xFF<<(module_pin * 8));
        /* Writing the new pin config pull up */
        *iocr_reg[(pinNumber/IOCR_REG_QTY)] |= (0x80 << (module_pin * 8));
    }
    else
    {
        /* Do nothing */
    }
}