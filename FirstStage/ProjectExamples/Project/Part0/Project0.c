/******************************************************************************

how do i know, how many items are stored inside the circular buffer?
	the Tail pointer must be behind the Head pointer
	the tail only could read a previous write space
	the head only could write a previous read space or empty one
	after each operation the pointer must be increment by one.

Function will determine if the queue is full with the last data written. How?
	If both pointer are in the same position after an operation (read/write). This mean that you cant perform the actual operation again.
e.g.
	If you are performing a reading and after increassing the Tail pointer direction is the same as, Head pointer, there is no new available information to read. 

Otherwise e.g.
	If you are performing a writing and after increasing the Head pointer direction is the same as Tail pointer, there is no new available space to write, the buffer is full (EMPTY = FALSE, FULL = TRUE). 


Possibilities
	head > tail	its easy to know if there is 
	tail < head

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"
#include "Buffer.h"
#include "UnitTest.h"

#define CICULAR_BUFFER_SIZE     (8U)

int main()
{
    uint8_t in_data_array[] = {15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155, 165, 175, 185};
    uint8_t out_data;
    uint8_t circ_buf_array[CICULAR_BUFFER_SIZE] = {0};
    uint8_t write_index = 0;
    AppBuffer_Buffer CircBuffer;

    /* inicialización */
    CircBuffer.Buffer = circ_buf_array;
    CircBuffer.Elements = CICULAR_BUFFER_SIZE;
    AppBuffer_initBuffer( &CircBuffer );

    while( AppBuffer_isBufferFull(&CircBuffer) == FALSE ) /* Check if the buffer is full */
    {        
        /* writting in the buffer */
        AppBuffer_writeData( &CircBuffer, in_data_array[write_index] );
        print_array8Bits(CircBuffer.Buffer, CICULAR_BUFFER_SIZE);
        write_index++;
    }

    /* read all the messages */
    while( AppBuffer_isBufferEmpty(&CircBuffer) == FALSE ) /* Check if the buffer is empty */
    {
        out_data = AppBuffer_readData( &CircBuffer );
        printf( "data read from the queue %d\n", out_data );
    }

    while( AppBuffer_isBufferFull(&CircBuffer) == FALSE ) /* Check if the buffer is full */
    {        
        /* writting in the buffer */
        AppBuffer_writeData( &CircBuffer, in_data_array[write_index] );
        print_array8Bits(CircBuffer.Buffer, CICULAR_BUFFER_SIZE);
        write_index++;
    }

    /* read all the messages */
    while( AppBuffer_isBufferEmpty(&CircBuffer) == FALSE ) /* Check if the buffer is empty */
    {
        out_data = AppBuffer_readData( &CircBuffer );
        printf( "data read from the queue %d\n", out_data );
    }

    return 0;
}