/******************************************************************************
 
Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.
 
*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Phase1.h"

#define ARRAY_SIZE      (8U)

int main()
{
    /* variable declaration */
    uint8_t array_size = ARRAY_SIZE;
    uint8_t array_cmp1[array_size];
    uint8_t array_cmp2[array_size];
    uint8_t array_cmp_flg = FALSE;
    /* array initialization */
    memcpy(array_cmp1, (uint8_t[]){68,10,155,89,87,56,124,235}, array_size);
    memcpy(array_cmp2, (uint8_t[]){68,10,155,89,87,5,124,235}, array_size);
    printf("Array one: ");
    print_array8Bits(array_cmp1, array_size);
    printf("Array two: ");
    print_array8Bits(array_cmp2, array_size);
    
    /* function call to compare arrays*/
    array_cmp_flg = arrayCompare(array_cmp1, array_cmp2, array_size);
 
    printf("Are the arrays equal? %s",(array_cmp_flg == TRUE) ? "TRUE" : "FALSE");
 
    return 0;
}