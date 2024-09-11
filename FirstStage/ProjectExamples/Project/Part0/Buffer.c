#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"
#include "Buffer.h"

/* Initialize the circular buffer by setting the head and tail elements to zero, and the values of empty to TRUE
 and full to FALSE. */
void AppBuffer_initBuffer( AppBuffer_Buffer *hbuffer )
{
    hbuffer->Head = 0;
    hbuffer->Tail = 0;
    hbuffer->Empty = TRUE;
    hbuffer->Full = FALSE;
}

/* Write a new 8-bit data to the buffer if there is available space; if there is no space, no data will be 
 written. Function will determine if the queue is full with the last data written */
void AppBuffer_writeData( AppBuffer_Buffer *hbuffer, uint8_t data )
{
    /* Check if actually there is an available space to write a new data  */
    if(hbuffer->Full == FALSE)
    {
        /* Assign the current input data to the buffer */
        hbuffer->Buffer[hbuffer->Head] = data;
        /* increment buffer head position */
        hbuffer->Head++;

        hbuffer->Empty = FALSE;
    }
    /* Check if its necessary to restart the Head buffer index*/
    hbuffer->Head = (hbuffer->Head == hbuffer->Elements)? 0: hbuffer->Head;
    /* Check if there is an available space to write the next data. If both (head & tail) has the same value 
        there is no free space to perform a new write operation, otherwise, Its already possible to write 
        a new data */
    hbuffer->Full = (hbuffer->Head == hbuffer->Tail)? TRUE : FALSE;
}

/* Reads a data from the buffer, the data that is read will no longer exist within the buffer. If the buffer is
 empty, no data will be read, and the value returned by the function will not be valid. Function will determine 
 if the queue is empty with the last data read */
uint8_t AppBuffer_readData( AppBuffer_Buffer *hbuffer )
{
    uint8_t read_data = 0;

    read_data = hbuffer->Buffer[hbuffer->Tail];
    hbuffer->Buffer[hbuffer->Tail] = 0;
    hbuffer->Tail++;

    /* Check if its necessary to restart the TAIL buffer index*/
    hbuffer->Tail = (hbuffer->Tail == hbuffer->Elements)? 0: hbuffer->Tail;

    /* Check if there is an available data to read from the buffer. If both (tail & head) has the same value 
        there is no more data to perform a read operation, otherwise, Its already possible to write 
        a new data*/
    hbuffer->Empty = (hbuffer->Tail == hbuffer->Head)? TRUE : FALSE;
    hbuffer->Full = (hbuffer->Tail == hbuffer->Head)? FALSE : TRUE;
    return read_data;
}

/* The function returns one if there are no more elements that can be read from the circular buffer, and zero if
 there is at least one element that can be read. It is necessary to use this function before using the read 
 function. */
uint8_t AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer )
{
    return (hbuffer->Empty == TRUE) ? TRUE : FALSE;
}

uint8_t AppBuffer_isBufferFull( AppBuffer_Buffer *hbuffer )
{
    return (hbuffer->Full == TRUE) ? TRUE : FALSE;
}