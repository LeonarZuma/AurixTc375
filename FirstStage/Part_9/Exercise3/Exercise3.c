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
    Made a function that takes an structure with the elements below and place them byte by byte into and array 
    made of 7 bytes, information shall be place in the following order: (Where word0 is the less significant 
    byte of word element and word3 is the most significant byte, same with hword0 and hword1).
    
    byte0 | byte1 | byte2 | byte3 | byte4 | byte5 | byte6 

    word0 | word1 | word2 | word3 | byte | hword0 | hword1
    */

   Struct_Pack var_str;
   var_str.word = 858993459;
   var_str.byte = 250;
   var_str.hword = 65530;

    uint8_t var_array[8];

   unpackingBytes(&var_str,var_array);

   print_array8Bits(var_array,CALCUTATE_SIZE(var_array)-1);

    return 0;
}