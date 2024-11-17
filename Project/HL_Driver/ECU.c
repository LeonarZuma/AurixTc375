/*
 *   ECU_Init() -> es una funcion que es la primera funcion de todo AUTOSAR que se ejecuta. Inicializa 
 *   todo lo que deba ser inicializado por primera vez o al inicio. Se ejecuta antes de que el sistema 
 *   opertivo arranque. 
 * 
 *      Esta es una funcion "General" por cada core. Se suele elegir  el core 0. (primero en bootear).
 *      
 */

void Ecu_Init(void)
{
    /* Ejemplo del Stack de CAN de autosar */
    Can_Init(/* parameters */);
    CanIf_Init(/* parameters */);
    CanTp_Init(/* parameters */);
    /* ... */
}