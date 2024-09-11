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
    Made a function that takes an array made of 11 bytes and place that information into a defined structured, 
    information shall be place in the following order: (Where word0 is the less significant byte of word element
    and word3 is the most significant byte, same with hword0 and hword1).
        <StructPack>.word1  = byte0, byte1, byte2, byte3
        <StructPack>.byte  = byte4
        <StructPack>.hword  = byte5, byte6
        <StructPack>.word2 = byte7, byte8, byte9, byte10
    */
   Struct_Pack_11bits var_struct;
   uint8_t local_array_aux[]= {0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75, 0x85, 0x95, 0x86, 0x99};

   PackingBytes(local_array_aux, &var_struct);

   printf("var_struct.word1 = %x \n", var_struct.word1);
   printf("var_struct.word2 = %x \n", var_struct.word2);
   printf("var_struct.byte = %x \n", var_struct.byte);
   printf("var_struct.hword1 = %x \n", var_struct.hword1);
   
    return 0;
}