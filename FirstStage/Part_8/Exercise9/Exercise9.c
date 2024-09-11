/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

#define SECONDS_OFFSET  (2U)
#define MINUTES_OFFSET  (1U)
#define HOURS_OFFSET    (0U)

int main()
{
    /* variable declaration */
    uint8_t tx_array_size = 5;
    uint8_t array[] = {0x04, 0x02, 0x03, 0x04, 0x05, 0x55, 0x55, 0x55};
    

    for(uint8_t i = 0; i < (sizeof(array) / sizeof(*array)); i++)
    {
        printf("0x%02x \t",*(array + i));
    }

    CanTp_SingleFrameTx(array, tx_array_size);

    printf("\n");
    for(uint8_t i = 0; i < (sizeof(array) / sizeof(*array)); i++)
    {
        printf("0x%02x \t",*(array + i));
    }

    return 0;
}