#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

#define FALSE           (0U)
#define TRUE            (1U)
#define ASCII_NO_OFFSET (48U)

uint16_t array_largestElement( uint16_t *array, uint8_t size )
{
    uint16_t local_largest_val = 0;
    for (int i=0; i<size; i++)
    {
        if (*(array+i) > local_largest_val)
        {
            local_largest_val = *(array + i);
        }
    }
    return local_largest_val;
}

void sortArray( uint16_t *array, uint8_t size )
{
    uint8_t local_correction_index = 0; /* A subindex for the subcycles iterations  */
    uint8_t local_is_high_flag = 0;     /* Semiboolean variable to check if the comprobation is done */
    uint8_t max_cycle_iter = size - 1;  /* The maximum index value */
    uint16_t high_elements = 0; /* Contains the total number of elements higher than i-element */
    
    /* we are going to implement a Cyclic Sort Algorithm */
    for (int cycle = 0; cycle < max_cycle_iter; cycle++)
    {
        local_correction_index = cycle + 1;
        local_is_high_flag = FALSE;
        high_elements = 0;
        //check if the element is higher than the following element
        //if its true, lets check with the next element
        // check until the condition is not meet
        //if is necessary, swap position with the no meeting condition number              
        
        while(local_is_high_flag == FALSE)
        {
            if (local_correction_index<=max_cycle_iter)
            {
                if (*(array + cycle) > *(array + local_correction_index))
                {
                    high_elements++;
                }
                local_is_high_flag = FALSE;
                local_correction_index++;
            }
            else
            {
                local_is_high_flag = TRUE;
                if(high_elements>0)
                {
                    array_swapElements((array + cycle), (array +cycle+ high_elements));
                    local_is_high_flag = FALSE;
                    high_elements = 0;
                    local_correction_index = cycle + 1;
                }
            }
        }
    }
}

void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds )
{
    convert_DecToChar(string, hours);
    *(string+2) = ':';
    convert_DecToChar((string+3), minutes);
    *(string+5) = ':';
    convert_DecToChar((string+6), seconds);
    *(string+8) = '\0';
}

void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes)
{
    
}

static void convert_DecToChar(int8_t *dec_value_string, uint8_t dec_value)
{
    *dec_value_string = (dec_value / 10) + ASCII_NO_OFFSET;
    *(dec_value_string + 1) = (dec_value % 10) + ASCII_NO_OFFSET;
}
static void array_swapElements(uint16_t *element_src, uint16_t *element_dst)
{
    uint16_t local_swap_auxiliar;

    local_swap_auxiliar = *element_dst;
    *element_dst = *element_src;
    *element_src = local_swap_auxiliar;
}

void array_print(uint16_t *array, uint8_t size)
{
    for (int i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}