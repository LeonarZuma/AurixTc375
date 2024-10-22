/**
 * @file    <Button.h>
 * @brief   **This is a simple Scheduler that can handle periodic tasks and Timers**
 *
 * 
 * @note    
 */

#ifndef BUTTON_H_
#define BUTTON_H_

    #define DELAY               (0x0003U)           /*!< MAX Delay count */
    #define INPUT_PIN_MASK      (0b1)               /*!< Mask to select one input pin */
    #define PINS_PER_REG        (4U)                /*!< Pins available per IOCR  */
    #define IOCR_REG_QTY        (4U)                /*!< Button pin state Low */
    #define BUTTON_PRESSED      (0U)                /*!< Button pin state High */
    #define BUTTON_RELEASED     (1U)

    /**
     * @brief   Struct of Button Configuration
     */
    typedef struct 
    {
        Ifx_P *port_inputAddr;                          /*!<pointer to port register>*/
        volatile Ifx_UReg_32Bit *pin_inputAddr;         /*!<pointer to Pxx_IN register>*/
        uint8_t pinNumber;                              /*!<pin Number from 0 to 15>*/
        uint32_t delay;                                 /*!<debounce Delay time>*/
        uint32_t delay_count;                           /*!<debounce Delay time counter from 0 to Delay>*/
        void (*taskFunc)(void);                         /*!<pointer to task function>*/
        /**
         * @brief   Struct of flags to record a button status
         */
        struct 
        {
            uint8_t   btn_pressed:1;    /*!<button pressed flag>*/
            uint8_t   btn_released:1;   /*!<button released flag>*/
        }flags;
    }Btn_Config;

    void Button_Init(Btn_Config *btn, Ifx_P *port_inputAddr, uint8_t pinNumber, void (*taskPtr)(void));
    
    void Button_pressedAndReleased(Btn_Config *btn);

    void Button_pinCnfg(Ifx_P *port_inputAddr, uint8_t pinNumber);

    uint8_t Button_GetStatus(Btn_Config *btn);

#endif