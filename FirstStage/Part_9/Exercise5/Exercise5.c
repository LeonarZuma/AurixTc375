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
    /*
    The million dollar question. What is the difference between structs and unions?, provide a detail answers
    and a example to demonstrate your response
    
    the difference between a union and a struct is the memory space. Within a union all the datatypes shares
    the same memory space. The union memory space is the size of the largest element in the union. Inside a 
    struct each single datatype has its own space, and the struct total size is the sum of all the datatype 
    elements plus the added padding. 

    */

    struct A
    {
        uint8_t val1;       //one byte
        uint8_t val2;       //one byte
        uint16_t val3;      //2 bytes
        uint32_t val4;      //4 bytes
        uint64_t val5;      //8 bytes
    };

    union B
    {
        uint8_t val1;       //one byte
        uint8_t val2;       //one byte
        uint16_t val3;      //2 bytes
        uint32_t val4;      //4 bytes
        uint64_t val5;      //8 bytes
    };
    
    /* The largest element is val5 in both of them. But the size of each is diffent */

    printf("Size of Struct in bytes: %d \n",sizeof(struct A));
    printf("Size of Union in bytes: %d \n",sizeof(union B));
   
    return 0;
}