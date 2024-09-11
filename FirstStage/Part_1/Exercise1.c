#include <stdio.h>
#include <stdint.h>

/* 
Write a program that asks the user to enter two numbers, obtains them from the user, and prints their sum, product,
difference, quotient, and remainder.
*/

int main()
{
    uint32_t val1 = 0;
    uint32_t val2 = 0;

    printf("Introduce dos enteros separados por un espacio: \n");
    scanf("%d %d", &val1, &val2);
    printf("The sum of %d + %d is %d",val1, val2, val1+val2);
    printf("The product of %d + %d is %d",val1, val2, val1*val2);
    printf("The difference of %d + %d is %d",val1, val2, val1-val2);
    printf("The quotient of %d + %d is %d",val1, val2, val1/val2);
    printf("The remainder of %d + %d is %d",val1, val2, val1%val2);

    return 0;
}