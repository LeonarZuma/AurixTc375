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
#include "Drivers/Phase1.h"
#include "Drivers/Buffer.h"
#include "Drivers/Queue.h"
#include "Drivers/Scheduler.h"
#include "Drivers/UnitTest.h"

#define CICULAR_BUFFER_SIZE     (5U)

int main()
{
    uint8_t in_data_array[] = {15, 25, 35, 45, 55, 65, 75, 85, 95, 105};
    uint8_t single_out_data = 0;
    uint8_t out_data_array[CICULAR_BUFFER_SIZE];
    uint8_t circ_buf_array[CICULAR_BUFFER_SIZE];
    
    AppBuffer_Buffer CircBuffer;

    test_bufferInit(&CircBuffer,circ_buf_array,CICULAR_BUFFER_SIZE);
    printf("Initialization Assert Test Succesful\n");

    /* Writing in the buffer until its completely full */
    test_bufferFullWrite(&CircBuffer,in_data_array,CICULAR_BUFFER_SIZE);
    printf("\nFull Write Assert Test Succesful\n");
    printf("Actual buffer data: ");
    print_array8Bits(CircBuffer.buffer, CICULAR_BUFFER_SIZE);

    /* Check the Full Flag must be set TRUE */
    test_bufferIsFull(&CircBuffer);
    printf("\nFull True Assert Test Succesful\n");

    /* Reading the buffer until is completely empty */
    test_bufferFullRead(&CircBuffer, out_data_array);
    printf("\nFull Read Assert Test Succesful\n");
    printf("Actual buffer data: ");
    print_array8Bits(CircBuffer.buffer, CICULAR_BUFFER_SIZE);
    printf("Read data: ");
    print_array8Bits(out_data_array, CICULAR_BUFFER_SIZE);

    /* Check the Empty Flag must be set TRUE*/
    test_bufferIsEmpty(&CircBuffer);
    printf("\nEmpty True Assert Test Succesful\n");

    /* Writing a single element inside the Buffer */
    test_bufferSingleWrite(&CircBuffer, in_data_array[7]);
    printf("\nsingle Write Assert Test Succesful\n");
    printf("Actual buffer data: ");
    print_array8Bits(CircBuffer.buffer, CICULAR_BUFFER_SIZE);

    /* Reading a single element inside the Buffer */
    test_bufferSingleRead(&CircBuffer,&single_out_data);
    printf("\nsingle Read Assert Test Succesful\n");
    printf("Actual buffer data: ");
    print_array8Bits(CircBuffer.buffer, CICULAR_BUFFER_SIZE);
    printf("Out buffer data: %d",single_out_data);



    return 0;
}