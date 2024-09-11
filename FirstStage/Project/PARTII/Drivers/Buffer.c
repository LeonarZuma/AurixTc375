#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"
#include "Buffer.h"

/* Initialize the circular buffer by setting the head and tail elements to zero, and the values of empty to TRUE
 and full to FALSE. */
void AppBuffer_initBuffer( AppBuffer_Buffer *hbuffer )
{
    hbuffer->head = 0;
    hbuffer->tail = 0;
    hbuffer->empty = TRUE;
    hbuffer->full = FALSE;
}

/* Write a new 8-bit data to the buffer if there is available space; if there is no space, no data will be 
 written. Function will determine if the queue is full with the last data written */
void AppBuffer_writeData( AppBuffer_Buffer *hbuffer, uint8_t data )
{
    /* Check if actually there is an available space to write a new data  */
    if(hbuffer->full == FALSE)
    {
        /* Assign the current input data to the buffer */
        hbuffer->buffer[hbuffer->head] = data;
        /* increment buffer head position */
        hbuffer->head++;

        hbuffer->empty = FALSE;
    }
    /* Check if its necessary to restart the head buffer index*/
    hbuffer->head = (hbuffer->head == hbuffer->elements)? 0: hbuffer->head;
    /* Check if there is an available space to write the next data. If both (head & tail) has the same value 
        there is no free space to perform a new write operation, otherwise, Its already possible to write 
        a new data */
    hbuffer->full = (hbuffer->head == hbuffer->tail)? TRUE : FALSE;
}

/* Reads a data from the buffer, the data that is read will no longer exist within the buffer. If the buffer is
 empty, no data will be read, and the value returned by the function will not be valid. Function will determine 
 if the queue is empty with the last data read */
uint8_t AppBuffer_readData( AppBuffer_Buffer *hbuffer )
{
    uint8_t read_data = 0;

    if(hbuffer->empty == FALSE)
    {
        read_data = hbuffer->buffer[hbuffer->tail];
        hbuffer->buffer[hbuffer->tail] = 0;
        hbuffer->tail++;

        hbuffer->empty = FALSE;   
    }
    

    /* Check if its necessary to restart the tail buffer index*/
    hbuffer->tail = (hbuffer->tail == hbuffer->elements)? 0: hbuffer->tail;

    /* Check if there is an available data to read from the buffer. If both (tail & head) has the same value 
        there is no more data to perform a read operation, otherwise, Its already possible to write 
        a new data */
    hbuffer->empty = (hbuffer->tail == hbuffer->head)? TRUE : FALSE;
    hbuffer->full = (hbuffer->tail == hbuffer->head)? FALSE : TRUE;
    return read_data;
}

/* The function returns one if there are no more elements that can be read from the circular buffer, and zero if
 there is at least one element that can be read. It is necessary to use this function before using the read 
 function. */
uint8_t AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer )
{
    return (hbuffer->empty == TRUE) ? TRUE : FALSE;
}

uint8_t AppBuffer_isBufferFull( AppBuffer_Buffer *hbuffer )
{
    return (hbuffer->full == TRUE) ? TRUE : FALSE;
}