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
    uint8_t array_size = ARRAY_SIZE;
    uint8_t array_src[array_size];
    uint8_t array_dst[array_size];
    /* array initialization */
    memcpy(array_src, (uint8_t[]){68,10,155,89,87,56,124,235}, array_size);
    /* Checking the current array state and values */
    printf("Before copy the array: \n Array_src: ");
    for(int i=0; i<array_size; i++)
    {
        printf("%d ",*(array_src + i));
    }
    printf("\n Array_dst: ");
    for(int i=0; i<array_size; i++)
    {
        printf("%d ",*(array_dst + i));
    }
    /* array copy function call*/
    arrayCopy(array_src, array_dst, array_size, 0);
 
    /* print the array dst to check if the data was copy correctly */
    printf("\nResult of copying the array: \n Array_src: ");
    for(int i=0; i<array_size; i++)
    {
        printf("%d ",*(array_src + i));
    }
    printf("\n Array_dst: ");
    for(int i=0; i<array_size; i++)
    {
        printf("%d ",*(array_dst + i));
    }
    return 0;
}