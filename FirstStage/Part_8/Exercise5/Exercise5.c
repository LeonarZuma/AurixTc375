/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

int main()
{
    /* variable declaration */
    uint16_t array_largest1[] = {6790,6789,155,15,155,155,6790,235};
    uint8_t array_size = sizeof(array_largest1)/sizeof(*array_largest1);

    uint16_t array_largest_element = 0;

    printf("Disordered Array: ");
    array_print(array_largest1, array_size);

    sortArray(array_largest1,array_size);
    
    printf("Sorted Array Small To High: ");
    array_print(array_largest1, array_size);

    return 0;
}
