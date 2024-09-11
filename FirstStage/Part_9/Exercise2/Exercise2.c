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
    struct customer 
    {
        int8_t lastName[ 15 ];
        int8_t firstName[ 15 ];
        int16_t customerNumber;
        struct 
        {
            int8_t phoneNumber[ 11 ];
            int8_t address[ 50 ];
            int8_t city[ 15 ];
            int8_t state[ 3 ];
            int8_t zipCode[ 6 ];
        } personal;
    } customerRecord, *customerPtr;
    customerPtr = &customerRecord; 

    /*Write an expression that can be used to access the structure members in each of the following parts:*/   

    /*a) Member lastName of structure customerRecord.*/
    insert_stringToString(customerRecord.lastName,(int8_t *)"Morales",0,sizeof("Morales")/sizeof(*("Morales")));
    printf("customerRecord.lastName = %s \n",customerRecord.lastName);

    /*b) Member lastName of the structure pointed to by customerPtr.*/
    insert_stringToString(&(customerPtr->lastName[0]),(int8_t *)"Paredes",0,sizeof("Paredes")/sizeof(*("Paredes")));
    printf("customerPtr->lastName = %s \n",customerPtr->lastName);

    /*c) Member firstName of structure customerRecord.*/
    insert_stringToString(customerRecord.firstName,(int8_t *)"Gabriel",0,sizeof("Gabriel")/sizeof(*("Gabriel")));
    printf("customerRecord.firstName = %s \n",customerRecord.firstName);

    /*d) Member firstName of the structure pointed to by customerPtr.*/
    insert_stringToString(&(customerPtr->firstName[0]),(int8_t *)"Luis",0,sizeof("Luis")/sizeof(*("Luis")));
    printf("customerPtr->firstName = %s \n",customerPtr->firstName);

    /*e) Member customerNumber of structure customerRecord.*/
    customerRecord.customerNumber = 1;
    printf("customerRecord.customerNumber = %d \n",(customerRecord.customerNumber));

    /*f) Member customerNumber of the structure pointed to by customerPtr.*/
    customerPtr->customerNumber = 15;
    printf("customerPtr->customerNumber = %d \n",customerPtr->customerNumber);

    /*g) Member phoneNumber of member personal of structure customerRecord.*/
    insert_stringToString(&(customerRecord.personal.phoneNumber[0]),(int8_t *)"9994131561",0,sizeof("9994131561")/sizeof(*("9994131561")));
    printf("customerRecord.personal.phoneNumber = %s \n",customerRecord.personal.phoneNumber);

    /*h) Member phoneNumber of member personal of the structure pointed to by customerPtr.*/
    insert_stringToString(customerPtr->personal.phoneNumber,(int8_t *)"9986384157",0,sizeof("9986384157")/sizeof(*("9986384157")));
    printf("customerPtr->personal.phoneNumber = %s \n",customerPtr->personal.phoneNumber);

    /*i) Member address of member personal of structure customerRecord.*/
    insert_stringToString(&(customerRecord.personal.address[0]),(int8_t *)"77, Baton Rogue",0,sizeof("77, Baton Rogue")/sizeof(*("77, Baton Rogue")));
    printf("customerRecord.personal.phoneNumber = %s \n",customerRecord.personal.address);

    /*j) Member address of member personal of the structure pointed to by customerPtr.*/
    insert_stringToString(customerPtr->personal.address,(int8_t *)"3535, Perkins Rd",0,sizeof("3535, Perkins Rd")/sizeof(*("3535, Perkins Rd")));
    printf("customerPtr->personal.phoneNumber = %s \n",customerPtr->personal.address);

    /*k) Member city of member personal of structure customerRecord.*/
    insert_stringToString(&(customerRecord.personal.city[0]),(int8_t *)"Lafayette",0,sizeof("Lafayette")/sizeof(*("Lafayette")));
    printf("customerRecord.personal.city = %s \n",customerRecord.personal.city);

    /*l) Member city of member personal of the structure pointed to by customerPtr.*/
    insert_stringToString(customerPtr->personal.city,(int8_t *)"Nueva Orleans",0,sizeof("Nueva Orleans")/sizeof(*("Nueva Orleans")));
    printf("customerPtr->personal.city = %s \n",customerPtr->personal.city);

    /*m) Member state of member personal of structure customerRecord.*/
    insert_stringToString(&(customerRecord.personal.state[0]),(int8_t *)"Luisiana",0,sizeof("Luisiana")/sizeof(*("Luisiana")));
    printf("customerRecord.personal.state = %s \n",customerRecord.personal.state);

    /*n) Member state of member personal of the structure pointed to by customerPtr.*/    
    insert_stringToString(customerPtr->personal.state,(int8_t *)"Misisipi",0,sizeof("Misisipi")/sizeof(*("Misisipi")));
    printf("customerPtr->personal.state = %s \n",customerPtr->personal.state);

    /*o) Member zipCode of member personal of structure customerRecord.*/
    insert_stringToString(customerPtr->personal.zipCode,(int8_t *)"70507",0,sizeof("70507")/sizeof(*("70507")));
    printf("customerPtr->personal.zipCode = %s \n",customerPtr->personal.zipCode);

    /*p) Member zipCode of member personal of the structure pointed to by customerPtr.*/
    insert_stringToString(customerPtr->personal.zipCode,(int8_t *)"70506",0,sizeof("70506")/sizeof(*("70506")));
    printf("customerPtr->personal.zipCode = %s \n",customerPtr->personal.zipCode);

    return 0;
}