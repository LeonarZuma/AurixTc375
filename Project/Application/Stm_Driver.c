#include <stdint.h>
#include "Ifx_Types.h"
#include "IfxStm.h"
#include "Stm_Driver.h"

#define IFX_INTPRIO_STM0_CMP0    10
#define IFX_INTPRIO_STM1_CMP0    10
#define IFX_INTPRIO_STM2_CMP0    10

/*Global variable to configure the STM0 Cmp0*/
static IfxStm_CompareConfig stm_cmp_config[3];

Ifx_STM* stm_sel[] =
{
    &MODULE_STM0,
    &MODULE_STM1,
    &MODULE_STM2
};

IfxSrc_Tos typeOfService_sel[] =
{
    IfxSrc_Tos_cpu0,
    IfxSrc_Tos_cpu1,
    IfxSrc_Tos_cpu2
};

extern callback_stm_func_t ptr_AppSched_Callback_Tickflag_Core0;
extern callback_stm_func_t ptr_AppSched_Callback_Tickflag_Core1;
extern callback_stm_func_t ptr_AppSched_Callback_Tickflag_Core2;

void Init_Stm(uint8_t core, uint32_t scheduler_tick)
{
    IfxStm_initCompareConfig( &stm_cmp_config[core] );
    stm_cmp_config[core].ticks = scheduler_tick;
    stm_cmp_config[core].comparator = IfxStm_Comparator_0;
    stm_cmp_config[core].comparatorInterrupt = IfxStm_ComparatorInterrupt_ir0;
    stm_cmp_config[core].triggerPriority = IFX_INTPRIO_STM0_CMP0;
    stm_cmp_config[core].typeOfService = typeOfService_sel[core];
    /*Configure the comparator to se for 500ms and enable its corresponding interrupt
    * using its corresponding Service Request Node (SRN) */
    IfxStm_initCompare( stm_sel[core], &stm_cmp_config[core] );
}

IFX_INTERRUPT( Isr_Stm0_Cmp0, 0, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    ptr_AppSched_Callback_Tickflag_Core0();
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( stm_sel[0], stm_cmp_config[0].comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( stm_sel[0], stm_cmp_config[0].comparator, stm_cmp_config[0].ticks );
}

IFX_INTERRUPT( Isr_Stm1_Cmp0, 1, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    ptr_AppSched_Callback_Tickflag_Core1();
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( stm_sel[1], stm_cmp_config[1].comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( stm_sel[1], stm_cmp_config[1].comparator, stm_cmp_config[1].ticks );
}

IFX_INTERRUPT( Isr_Stm2_Cmp0, 2, IFX_INTPRIO_STM0_CMP0)
{
    /*we do something set tick flag */
    ptr_AppSched_Callback_Tickflag_Core2();
    /*it is neccesary to clear the module (STM0 CMP0) interrupt flag*/
    IfxStm_clearCompareFlag( stm_sel[2], stm_cmp_config[2].comparator );
    /* reload the comparator with the last value plus the same amount of ticks to keep
    * setting the comparator flag at the same frequency */
    IfxStm_increaseCompare( stm_sel[2], stm_cmp_config[2].comparator, stm_cmp_config[2].ticks );
}