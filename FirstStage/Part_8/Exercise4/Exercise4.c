/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

#define ARRAY_SIZE      (8U)

int main()
{
    /* variable declaration */
    uint16_t array_largest1[] = {68,6789,155,89,8,56,124,235};
    uint8_t array_size = sizeof(array_largest1)/sizeof(*array_largest1);
    uint8_t comparador = 1;

    uint16_t array_largest_element = 0;
    
    printf("Array: ");
    if(comparador == CAN_SING_FRAME_VALID)
    {
        print_array16Bits(array_largest1, array_size);
    }
    

    /* function call for the largest element in array */
    array_largest_element = get_arrayLargestElement(array_largest1,array_size);

    printf("Largest element is: %d",array_largest_element);

    return 0;
}
