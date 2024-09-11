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
    uint8_t array_size = 8;
    uint8_t can_rx_bytes = 0;
    uint8_t array[] = {0x04, 0x02, 0x03, 0x04, 0x05, 0x55, 0x55, 0x55};
    

    for(uint8_t i = 0; i < array_size; i++)
    {
        printf("0x%02x \t",*(array + i));
    }

    if(CanTp_SingleFrameRx(array, &can_rx_bytes) == CAN_SING_FRAME_VALID)
    {
        printf("\nRx valid data = %d \n", can_rx_bytes);
        for(uint8_t i = 0; i < array_size; i++)
        {
            printf("0x%02x \t",*(array + i));
        }
    }

    return 0;
}