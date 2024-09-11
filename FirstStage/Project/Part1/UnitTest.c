#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "Phase1.h"
#include "Buffer.h"
#include "Queue.h"


/* Initialize the circular buffer by setting the head and tail elements to zero, and the values of empty to TRUE
and full to FALSE. */
void test_queueInit(AppQue_Queue *test_queueBuffer, uint8_t *array, uint32_t size)
{
    /* inicialización */
    test_queueBuffer->buffer = array;
    test_queueBuffer->elements = size;
    AppQueue_initQueue( test_queueBuffer );

    assert(test_queueBuffer->head == 0);
    assert(test_queueBuffer->tail == 0);
    assert(test_queueBuffer->empty == TRUE);
    assert(test_queueBuffer->full == FALSE);
}

/* Write a new 8-bit data to the buffer if there is available space; if there is no space, no data will be 
written. Function will determine if the queue is full with the last data written */
void test_queueFullWrite(AppQue_Queue *test_queueBuffer, uint8_t *in_array, uint32_t size)
{
    uint8_t write_index = 0;
    
    /* Write Index must be 5, because there is only 5 available spaces inside the buffer to write on it */
    assert(write_index == 5);
    /* Check if the 5th element inside the buffer is the same element as the 5th in_array element */
    //assert(test_queueBuffer->buffer[write_index - 1] == in_array[write_index - 1]);
    /* Check that the head index has been reset to 0 because the buffer has reach its own limit after being 
    completely full by the write operation */
    assert(test_queueBuffer->head == 0);
}

/* Reads a data from the buffer, the data that is read will no longer exist within the buffer. If the buffer is 
empty, no data will be read, and the value returned by the function will not be valid. Function will determine if
the queue is empty with the last data read */
void test_queueFullRead(AppQue_Queue *test_queueBuffer, uint8_t *out_data)
{
    uint8_t aux_localTail = test_queueBuffer->tail;
    /* read all the messages */
    while( AppQueue_isQueueEmpty(test_queueBuffer) == FALSE )
    {
        AppQueue_readData( test_queueBuffer, out_data );
    }
    /* Once the buffer has been completely read, empty flag must be updated to TRUE indicating there is no remaining
    items inside the buffer to read */
    assert(test_queueBuffer->empty == TRUE);
    /* If the buffer flag full state was TRUE before starting the reading, after complete the reading operation 
    the value must be reset to FALSE, this indicates that the buffer has available space to perform a new write 
    operation */
    assert(test_queueBuffer->full == FALSE);

    /* After reading a value from the buffer that index position must be reset to zero, every value inside the
    buffer can only read once. Check if the 5th element inside the buffer is empty */
    //assert(test_queueBuffer->buffer[read_index - 1] == 0);

    /* If we have done a complete buffer read, from the begin postion tail = 0, after reading the whole buffer
    the tail value have been reset to 0 */
    assert(test_queueBuffer->tail == aux_localTail);

}

void test_queueSingleWrite(AppQue_Queue *test_queueBuffer, uint8_t in_data)
{
    /* Saving the value of tail and head beafore any probable change */
    uint8_t aux_headPostion = test_queueBuffer->head;
    uint8_t aux_tailPostion = test_queueBuffer->tail;
    AppBuffer_writeData( test_queueBuffer, in_data );

    /* Check empty Flag must be reset to FALSE */
    assert(test_queueBuffer->empty == FALSE);

    /* Buffer head Postiton Has been move one position foward */
    assert(test_queueBuffer->head == aux_headPostion + 1);

    /* Buffer tail Postiton Has not been changed */
    assert(test_queueBuffer->tail == aux_tailPostion);

    /* Previous data wrote in buffer was in_data */
    //assert(test_queueBuffer->buffer[aux_headPostion] == in_data);
}

void test_queueSingleRead(AppQue_Queue *test_queueBuffer, uint8_t *out_data)
{
    /* Saving the value of tail and head beafore any probable change */
    uint8_t aux_headPostion = test_queueBuffer->head;
    uint8_t aux_tailPostion = test_queueBuffer->tail;

    /* the data is not being stored because its been probing the procedure of single data reading */
    *out_data = AppBuffer_readData( test_queueBuffer);

    /* In this point, there is only one element avaiable inside the buffer to being read. If we read this single 
    value the empty flag must be set TRUE */
    assert(test_queueBuffer->empty == TRUE);

    /* The tail position to read has been updated one position foward */
    assert(test_queueBuffer->tail == aux_tailPostion + 1);

    /* The head position has not been changed */
    assert(test_queueBuffer->head == aux_headPostion);
}

void test_queueIsEmpty(AppQue_Queue *test_queueBuffer)
{
    uint8_t aux_emptyFlagState =  AppBuffer_isBufferEmpty(test_queueBuffer);
    /* After the buffer has been write, the empty Flag must be set TRUE */
    assert( aux_emptyFlagState == TRUE);
}

void test_queueIsFull(AppQue_Queue *test_queueBuffer)
{
    uint8_t aux_fullFlagState =  AppBuffer_isBufferFull(test_queueBuffer);
    /* After the buffer has been write, the full Flag must be set TRUE */
    assert( aux_fullFlagState == TRUE);
}