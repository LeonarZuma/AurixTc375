/**
 * @file    <Button.h>
 * @brief   **This file contains the configuration for a Button Driver using a certain pin **
 *
 *  This functions configures, and perform the button basic behaviour 
 * 
 * @note    
 */
#include <stdint.h>
#ifndef TESSY
    #include "Ifx_Types.h"
    #include "IfxCpu.h"
    #include "IfxScuWdt.h"
    #include "Button.h"
#else
    #include "..\HL_Driver\ts_defines.h"
    #include "Button.h"
#endif

/**
 * @brief   ** Initialize a Button in a certain Pin configuration **
 *
 * Initialize the button pin configuration including the pin set as pullup input. 
 *
 * @param[in]   btn This contains the Button setting up parameters
 * @param[in]   taskPtr function task pointer shouldn't be a NULL pointer
 * @param[in]   port_inputAddr Address for the port input pin button
 * @param[in]   pinNumber input pin number
 *
 * @retval  None
 *
 * @note The taskPtr shouldn't be a NULL pointer
 */
void Button_Init(Btn_Config *btn, Ifx_P *port_inputAddr, uint8_t pinNumber, void (*taskPtr)(void))
{
    /* Set Button pin input Address*/
    btn->pin_inputAddr = &port_inputAddr->IN.U;
    /* Set port Input Address */
    btn->port_inputAddr = port_inputAddr;
    /* Set Button pin input pin Number */
    btn->pinNumber = pinNumber;
    /* Set button debounce Delay */
    btn->delay = DELAY;  
    /* Set debounce count to zero */  
    btn->delay_count = 0;    
    btn->flags.btn_released = FALSE;
    btn->flags.btn_pressed = FALSE;
    /* Set function to call */
    btn->taskFunc = taskPtr;

    /* Configure pin as input pull-up */
    Button_pinCnfg(port_inputAddr, pinNumber);
}

/**
 * @brief   ** Button Executes function after press then release **
 *
 * After press then release, will execute a Function Task
 *
 * @param[in]   btn This contains the Button setting up parameters
 *
 * @retval  None
 *
 * @note The function after release debounce executes the pointer FuncTask
 */
void Button_pressedAndReleased(Btn_Config *btn)
{
    /* Read the pin state value */
    uint8_t pinState = ((*(btn->pin_inputAddr) >> btn->pinNumber)& INPUT_PIN_MASK);

    /* To check button has been pressed */
    if ((pinState == 0)&&(btn->flags.btn_pressed == FALSE))
    {
        /* Set Flag */
        btn->flags.btn_pressed = TRUE;
    }
    /* To check button has been released*/
    else if ((pinState == 1)&&( btn->flags.btn_pressed == TRUE))
    {
        btn->flags.btn_released = TRUE;
        btn->flags.btn_pressed = FALSE;
    }
    else
    {
        /* Do nothing */
    }

    /* Once the button has been released, start debounce 
    with the increase delay count */
    if (btn->flags.btn_released == TRUE)
    {
        /* while Flag set, start count */
        btn->delay_count = (btn->delay_count + 1) % btn->delay;
    }
    else
    {
        /* Do nothing */
    }

    /* Once the debounce time has been reached, toggle state */
    if(btn->delay_count == (btn->delay - 1))
    {
        /*Perform taskFunc */
        btn->taskFunc();
        /* change flag state */
        btn->flags.btn_released = FALSE;
        /* Reset delay count */
        btn->delay_count = 0;
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief   ** Button Executes The configuration of a certain pin as pull-up Button **
 *
 * Configures a Pin as a Pull up Button
 *
 * @param[in]   port_inputAddr Address for the port input pin button
 * @param[in]   pinNumber input pin number
 *
 * @retval  None
 *
 * @note The function after release debounce executes the pointer FuncTask
 */
void Button_pinCnfg(Ifx_P *port_inputAddr, uint8_t pinNumber)
{
    uint8_t module_pin = pinNumber % PINS_PER_REG;

    volatile Ifx_UReg_32Bit *iocr_reg[] = 
    {
        &port_inputAddr->IOCR0.U,
        &port_inputAddr->IOCR4.U,
        &port_inputAddr->IOCR8.U,
        &port_inputAddr->IOCR12.U
    };

    if((pinNumber >= 0)&&(pinNumber <= 15))
    {
        /* Clearing bits in register */
        *iocr_reg[(pinNumber/IOCR_REG_QTY)] &= ~(0xFF<<(module_pin * 8));
        /* Writing the new pin config pull up */
        *iocr_reg[(pinNumber/IOCR_REG_QTY)] |= (0x10 << (module_pin * 8));
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief   ** Interface to get the current button pin state **
 *
 * This functions returns the actual pin state value for a certain given pin
 *
 * @param[in]   btn This contains the Button setting up parameters
 *
 * @retval  None
 *
 * @note The function reads the button pin state value (0 not pressed, 1 pressed)
 */
uint8_t Button_GetStatus(Btn_Config *btn)
{
    uint8_t btnState = ((*(btn->pin_inputAddr) >> btn->pinNumber)& INPUT_PIN_MASK);
    return btnState;
}