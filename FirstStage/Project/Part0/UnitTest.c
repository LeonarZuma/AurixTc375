#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "Phase1.h"
#include "Buffer.h"


/* Initialize the circular buffer by setting the head and tail elements to zero, and the values of empty to TRUE
and full to FALSE. */
void test_bufferInit(AppBuffer_Buffer *test_circBuffer, uint8_t *array, uint32_t size)
{
    /* inicialización */
    test_circBuffer->Buffer = array;
    test_circBuffer->Elements = size;
    AppBuffer_initBuffer( test_circBuffer );

    assert(test_circBuffer->Head == 0);
    assert(test_circBuffer->Tail == 0);
    assert(test_circBuffer->Empty == TRUE);
    assert(test_circBuffer->Full == FALSE);
}

/* Write a new 8-bit data to the buffer if there is available space; if there is no space, no data will be 
written. Function will determine if the queue is full with the last data written */
void test_bufferFullWrite(AppBuffer_Buffer *test_circBuffer, uint8_t *in_array, uint32_t size)
{
    uint8_t write_index = 0;
    while( AppBuffer_isBufferFull(test_circBuffer) == FALSE ) /* Check if the buffer is full */
    {        
        /* writting in the buffer */
        AppBuffer_writeData( test_circBuffer, in_array[write_index] );
        write_index++;
    }
    /* Until here the buffer must be completely full, no available space to write */
    assert(test_circBuffer->Full == TRUE);
    /* Write Index must be 5, because there is only 5 available spaces inside the buffer to write on it */
    assert(write_index == 5);
    /* Check if the 5th element inside the buffer is the same element as the 5th in_array element */
    assert(test_circBuffer->Buffer[write_index - 1] == in_array[write_index - 1]);
    /* Check that the Head index has been reset to 0 because the buffer has reach its own limit after being 
    completely full by the write operation */
    assert(test_circBuffer->Head == 0);
}

/* Reads a data from the buffer, the data that is read will no longer exist within the buffer. If the buffer is 
empty, no data will be read, and the value returned by the function will not be valid. Function will determine if
the queue is empty with the last data read */
void test_bufferFullRead(AppBuffer_Buffer *test_circBuffer, uint8_t *out_array)
{
    uint8_t read_index = 0;
    /* read all the messages */
    while( AppBuffer_isBufferEmpty(test_circBuffer) == FALSE ) /* Check if the buffer is empty */
    {
        out_array[read_index] = AppBuffer_readData( test_circBuffer );
        read_index++;
    }
    /* Once the buffer has been completely read, Empty flag must be updated to TRUE indicating there is no remaining
    items inside the buffer to read */
    assert(test_circBuffer->Empty == TRUE);
    /* If the buffer flag FULL state was TRUE before starting the reading, after complete the reading operation 
    the value must be reset to FALSE, this indicates that the buffer has available space to perform a new write 
    operation */
    assert(test_circBuffer->Full == FALSE);

    /* After reading a value from the buffer that index position must be reset to zero, every value inside the
    buffer can only read once. Check if the 5th element inside the buffer is empty */
    assert(test_circBuffer->Buffer[read_index - 1] == 0);

    /* If we have done a complete buffer read, from the begin postion Tail = 0, after reading the whole buffer
    the Tail value have been reset to 0 */
    assert(test_circBuffer->Tail == 0);

}

void test_bufferSingleWrite(AppBuffer_Buffer *test_circBuffer, uint8_t in_data)
{
    /* Saving the value of Tail and Head beafore any probable change */
    uint8_t aux_headPostion = test_circBuffer->Head;
    uint8_t aux_tailPostion = test_circBuffer->Tail;
    AppBuffer_writeData( test_circBuffer, in_data );

    /* Check Empty Flag must be reset to FALSE */
    assert(test_circBuffer->Empty == FALSE);

    /* Buffer Head Postiton Has been move one position foward */
    assert(test_circBuffer->Head == aux_headPostion + 1);

    /* Buffer Tail Postiton Has not been changed */
    assert(test_circBuffer->Tail == aux_tailPostion);

    /* Previous data wrote in buffer was in_data */
    assert(test_circBuffer->Buffer[aux_headPostion] == in_data);
}

void test_bufferSingleRead(AppBuffer_Buffer *test_circBuffer, uint8_t *out_data)
{
    /* Saving the value of Tail and Head beafore any probable change */
    uint8_t aux_headPostion = test_circBuffer->Head;
    uint8_t aux_tailPostion = test_circBuffer->Tail;

    /* the data is not being stored because its been probing the procedure of single data reading */
    *out_data = AppBuffer_readData( test_circBuffer);

    /* In this point, there is only one element avaiable inside the buffer to being read. If we read this single 
    value the Empty flag must be set TRUE */
    assert(test_circBuffer->Empty == TRUE);

    /* The Tail position to read has been updated one position foward */
    assert(test_circBuffer->Tail == aux_tailPostion + 1);

    /* The head position has not been changed */
    assert(test_circBuffer->Head == aux_headPostion);
}

void test_bufferIsEmpty(AppBuffer_Buffer *test_circBuffer)
{
    uint8_t aux_emptyFlagState =  AppBuffer_isBufferEmpty(test_circBuffer);
    /* After the buffer has been write, the Empty Flag must be set TRUE */
    assert( aux_emptyFlagState == TRUE);
}

void test_bufferIsFull(AppBuffer_Buffer *test_circBuffer)
{
    uint8_t aux_fullFlagState =  AppBuffer_isBufferFull(test_circBuffer);
    /* After the buffer has been write, the Full Flag must be set TRUE */
    assert( aux_fullFlagState == TRUE);
}