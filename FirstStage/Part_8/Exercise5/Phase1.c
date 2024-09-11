#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

#define FALSE           (0U)
#define TRUE            (1U)

uint16_t array_largestElement( uint16_t *array, uint8_t size )
{
    uint16_t local_largest_val = 0;
    for (uint8_t i=0; i<size; i++)
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
    uint8_t max_cycle_iter = size;  /* The maximum index value */
    
    
    /* we are going to implement a Cyclic Sort Algorithm */
    for (int8_t cycle = 1; cycle < size; cycle++)
    {
        uint16_t key_element = *(array + cycle);
        printf("key: %d \n",key_element);
        int16_t cycle_sort = cycle - 1;

        while((cycle_sort >= 0) && (*(array + cycle_sort) > key_element))
        {
            printf("Sorting: %d %d\n",*(array + cycle_sort),*(array + cycle_sort + 1));
            *(array + cycle_sort + 1) = *(array + cycle_sort);
            cycle_sort -= 1;
        }
        printf("%d \n", cycle_sort);
        *(array + cycle_sort) = key_element;
    }
}

void array_swapElements(uint16_t *element_src, uint16_t *element_dst)
{
    uint16_t local_swap_auxiliar;

    local_swap_auxiliar = *element_dst;
    *element_dst = *element_src;
    *element_src = local_swap_auxiliar;
}

void array_print(uint16_t *array, uint8_t size)
{
    for (uint8_t i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}