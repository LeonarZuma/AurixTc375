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
   /*
   1.- Provide the definition for each of the following structures and unions:
        *Structure inventory containing character array partName[ 30 ], integer partNumber, floating point price, integer stock and integer reorder.
        *Union data containing char c, short s, long b, float f and double d.
        *A structure called address that contains character arrays streetAddress[ 25 ], city[ 20 ], state[ 3 ] and zipCode[ 6 ].
        *Structure student that contains arrays firstName[ 15 ] and lastName[ 15 ] and variable homeAddress of type struct address from part (c).
        *Structure test containing 16 bit fields with widths of 1 bit. The names of the bit fields are the letters a to p.
   */
    struct 
    {
            uint8_t     partName[30];
            uint16_t    partNumber;
            float32_t       price;
            uint16_t    stock;
            uint16_t    reorder;
    }inventory;

    union
    {
        uint8_t     c;
        uint16_t    s;
        uint64_t    b;
        float32_t   f;
        float64_t   d;
    }data;

    typedef struct 
    {
        uint8_t streetAddress[25];
        uint8_t city[20];
        uint8_t state[3];
        uint8_t zipCode[6];       
    }Address; 

    typedef struct
    {
        uint8_t firstName[15];
        uint8_t lastName[15];
    }Student;

    struct
    {
        uint16_t a:1;
        uint16_t b:1;
        uint16_t c:1;
        uint16_t d:1;
        uint16_t e:1;
        uint16_t f:1;
        uint16_t g:1;
        uint16_t h:1;
        uint16_t i:1;
        uint16_t j:1;
        uint16_t k:1;
        uint16_t l:1;
        uint16_t m:1;
        uint16_t n:1;
        uint16_t o:1;
        uint16_t p:1;
    }test;
     
    Address homeAddress;

    return 0;
}