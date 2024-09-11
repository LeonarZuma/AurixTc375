/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Phase1.h"

#define ARRAY_SIZE      (8U)

int main()
{
   /* variable declaration */
    const uint8_t avg_array_size = ARRAY_SIZE;
    uint8_t avg_array[] = {68,10,155,89,87,56,124,235};
    uint8_t result_average = 0;
    printf("Entry array: ");
    print_array8Bits(avg_array, avg_array_size);
    /* average function call */
    result_average = get_arrayAverage(avg_array,avg_array_size);
    /* result printing */
    printf("The average value is: %d",result_average);
    return 0;
}