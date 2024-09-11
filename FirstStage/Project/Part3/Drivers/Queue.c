/*******************************************************************************************
 TO DO: 
 *******************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Phase1.h"
#include "Buffer.h"
#include "Queue.h"

/* Initializes the queue by setting the head and tail elements to zero, and the values of empty to one and full to
 zero */
void AppQueue_initQueue( AppQue_Queue *queue )
{
    queue->head = 0;
    queue->tail = 0;
    queue->empty = TRUE;
    queue->full = FALSE;
}

/* Copies the information referenced by the empty pointer data to the buffer controlled by queue, the number of 
bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if the write is successful the
function returns a TRUE, and if not a FALSE. This function should determine when the queue is full by the current 
write operation and prevent the writing of a new element when it is. */
uint8_t AppQueue_writeData( AppQue_Queue *queue, void *data )
{
    uint8_t write_operResult = FALSE;
    if (queue->full == FALSE)
    {        
        /* copying from data to Buffer queue */
        memcpy((queue->buffer + queue->head), data, queue->size);

        /* After copying the data to the buffer we have to check if the data were copy correctly */
        write_operResult = TRUE;

        /* Increase the Head pointer */
        queue->head += queue->size;

        queue->empty = FALSE;
        /* Check if its necessary to restart the Head buffer index*/
        queue->head %= BUFFER_SIZE(queue);
        /* Check if there is an available space to write the next data. If both (head & tail) has the same value 
            there is no free space to perform a new write operation, otherwise, Its already possible to write 
            a new data */
        if(queue->head == queue->tail)
        {
            queue->full = TRUE;
        }
        else
        {
            queue->full = FALSE;
        }
        
    }
    else
    {
        /* Do nothing */
    }

    /*We have to invert the result becasuse strncpy 0 is True and 1 False */
    return write_operResult;
}

/* Reads data from the buffer controlled by queue, the data is copied into the data type referenced by the empty 
pointer data, the number of bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if 
the read is successful the function returns a TRUE and otherwise a FALSE. This function should determine when the 
queue is emptied by the current read operation and prevent the reading of a new element when it is. */
uint8_t AppQueue_readData( AppQue_Queue *queue, void *data )
{
    uint8_t read_operResult = FALSE;

    /* increase the tail direction */
    if(queue->empty == FALSE)
    {
        /* reading the buffer, and passing the values to data */
        memcpy(data, (queue->buffer + queue->tail), queue->size);

        /* After reading the data to the buffer we have to check if the data were copy correctly, 
        this operation has to be performed before erasing the data from the buffer */
        read_operResult = TRUE;
        
        /* To erase the data space read */    
        queue->tail += queue->size;

        /* Check if its necessary to restart the TAIL buffer index*/
        queue->tail %= BUFFER_SIZE(queue);

        /* If we read, its not possible that the buffer stays full */
        queue->full = FALSE;

        /* Check if there is an available data to read from the buffer. If both (tail & head) has the same value 
        there is no more data to perform a read operation, otherwise, Its already possible to write 
        a new data*/
        
        if(queue->tail == queue->head)
        {
            queue->empty = TRUE;
        }
        else
        {
            queue->empty = FALSE;
        }
    }

    else
    {
        /* Do nothing */
    }

    return read_operResult;
}

/* The function returns a one if there are no more elements that can be read from the queue and zero if there is 
at least one element that can be read */
uint8_t AppQueue_isQueueEmpty( AppQue_Queue *queue )
{
    return queue->empty;
}

/* The function must empty the queue in case it has elements inside it, the information will be discarded */
void AppQueue_flushQueue( AppQue_Queue *queue )
{
    /* calling init queue to flush the queue */
    AppQueue_initQueue(queue);
}