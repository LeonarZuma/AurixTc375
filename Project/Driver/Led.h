/**
 * @file    <Led.h>
 * @brief   **This is a simple Scheduler that can handle periodic tasks and Timers**
 *
 * 
 * @note    
 */

#ifndef LED_H_
#define LED_H_

    #define PINS_PER_REG        (4U)                /*!< Pins available per IOCR  */
    #define IOCR_REG_QTY        (4U)                /*!< Number of IOCR Registers */

    /**
     * @brief   Struct of Led Configuration
     */
    typedef struct
    {
        Ifx_P *port_ouputAddr;                          /*!<pointer to port register>*/
        volatile Ifx_UReg_32Bit *pin_outputAddr;        /*!<pointer to Pxx_OUT register>*/
        uint8_t pinNumber;                              /*!<pin Number from 0 to 15>*/
    }Led_Config;

    void Led_Init(Led_Config *led, Ifx_P *port_ouputAddr, uint8_t pinNumber);

    void Led_Toggle(Led_Config *led);

    void Led_pinCnfg(Ifx_P *port_ouputAddr, uint8_t pinNumber);

    void Led_WriteArray(Led_Config *led_ptr, uint8_t size, uint8_t *array_ptr);

#endif