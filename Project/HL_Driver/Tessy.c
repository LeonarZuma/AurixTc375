#include <stdint.h>
#include "Tessy.h"

/* global variables to check the number of functions called */
uint8_t call_Init_funcA = 0;
uint8_t call_Init_funcB = 0;
uint8_t call_Init_funcC = 0;
uint8_t call_funcA = 0;
uint8_t call_funcB = 0;
uint8_t call_funcC = 0;

uint8_t call_Timer_funcA = 0;
uint8_t call_Timer_funcB = 0;
uint8_t call_Timer_funcC = 0;

void Timer_funcA (void)   
{
    call_Timer_funcA++;
}

void Timer_funcB (void)   
{
    call_Timer_funcB++;
}

void Timer_funcC (void)   
{
    call_Timer_funcC++;
}

void funcA (void)   
{
    call_funcA++;
}

void Init_funcA (void)   
{
    call_Init_funcA++;
}

void funcB (void)   
{
    call_funcB++;
}

void Init_funcB (void)   
{
    call_Init_funcB++;
}

void funcC (void)   
{
    call_funcC++;
}

void Init_funcC (void)   
{
    call_Init_funcC++;
}