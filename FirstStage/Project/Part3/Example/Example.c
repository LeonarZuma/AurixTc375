#include <stdio.h>
#include <time.h>

//#define CLOCKS_PER_SEC     (10000U)

long milliseconds( void )
{
    return clock() / ( CLOCKS_PER_SEC / 1000 );
}

int main( void )
{
    long x = 0;
    /*get the milliseconds for the first time*/
    long tickstart = milliseconds();
    while( x < 10 )
    {
        /* Preguntamos si han pasado 500ms desde que obtuvimos el anterior valor */
        if( ( milliseconds() - tickstart ) >= 500 )
        {
            tickstart = milliseconds();/*volvemos a obtener los ms actuales*/
            printf( "clocks per second: %d\n\r", x++ ); /*imprimos el valor de x*/
        }
    }
    return 0;
}