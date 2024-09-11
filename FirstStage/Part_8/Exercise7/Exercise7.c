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
    uint8_t string_time_elements = 12;
    uint16_t array_time_24form[] = {13,15,45};
    uint16_t array_time_alarm[] = {13,15};
    int8_t time_string[string_time_elements];

    set_alarmString(time_string, *(array_time_alarm + HOURS_OFFSET), *(array_time_alarm + MINUTES_OFFSET));

    printf("%s",time_string);

    return 0;
}
