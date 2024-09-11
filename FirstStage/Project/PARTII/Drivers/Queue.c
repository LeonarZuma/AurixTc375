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
        memcpy((uint8_t*)(queue->buffer + queue->head), data, queue->size);

        /* After copying the data to the buffer we have to check if the data were copy correctly */
        write_operResult = TRUE;

        /* Increase the Head pointer */
        queue->head += queue->size;

        queue->empty = FALSE;
    }
    else
    {
        /* Do nothing */
    }

    /* Check if its necessary to restart the Head buffer index*/
    /*
    queue->head = (queue->head == BUFFER_SIZE(queue))? 0: queue->head;
    */
   queue->head %= BUFFER_SIZE(queue);

    /* Check if there is an available space to write the next data. If both (head & tail) has the same value 
        there is no free space to perform a new write operation, otherwise, Its already possible to write 
        a new data */
    queue->full = (queue->head == queue->tail)? TRUE : FALSE;
    
    /*We have to invert the result becasuse strncpy 0 is True and 1 False */
    return write_operResult;
}

/* Reads data from the buffer controlled by queue, the data is copied into the data type referenced by the empty 
pointer data, the number of bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if 
the read is successful the function returns a TRUE and otherwise a FALSE. This function should determine when the 
queue is emptied by the current read operation and prevent the reading of a new element when it is. */
uint8_t AppQueue_readData( AppQue_Queue *queue, void *data )
{
    /* Creating an empty array to use as the substitute after a reading operation */
    uint8_t zero_array[queue->size];
    /* After reading a value from the value buffer we replace the value with a zero */
    memset( zero_array, 0, queue->size);
    uint8_t read_operResult = FALSE;

    /* increase the tail direction */
    if(queue->empty == FALSE)
    {
        /* reading the buffer, and passing the values to data */
        memcpy(data, (uint8_t*)(queue->buffer + queue->tail), queue->size);

        /* After reading the data to the buffer we have to check if the data were copy correctly, 
        this operation has to be performed before erasing the data from the buffer */
        read_operResult = TRUE;
        
        /* To erase the data space read */
        //memcpy((queue->buffer + queue->tail), zero_array, queue->size);        
        queue->tail += queue->size;

        queue->empty = FALSE;
    }

    else
    {
        /* Do nothing */
    }

    /* Check if its necessary to restart the TAIL buffer index*/
    /*
    queue->tail = (queue->tail == BUFFER_SIZE(queue))? 0: queue->tail;
    */
    /* an alternative could be using an operation using a module */
    /* this is shorter but it cant be harder to read */
    queue->tail %= BUFFER_SIZE(queue);

    /* Check if there is an available data to read from the buffer. If both (tail & head) has the same value 
        there is no more data to perform a read operation, otherwise, Its already possible to write 
        a new data*/
    queue->empty = ((queue->tail == queue->head)? TRUE : FALSE);
    if(queue->full == TRUE)
    {
        queue->full = FALSE;
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
    return ((queue->empty == TRUE)? TRUE : FALSE);
}

/* The function must empty the queue in case it has elements inside it, the information will be discarded */
void AppQueue_flushQueue( AppQue_Queue *queue )
{
    /* Creating an empty array to use as the substitute after a reading operation */
    uint8_t zero_array[queue->size];
    memset( zero_array, 0, queue->size);
    
    /* Reset the Head and Tail position to reset all the buffer */
    /* This could be optimize somehow, but i'm not sure about it */
    queue->head = 0;
    queue->tail = 0;

    /* Perform a Buffer Reset */
    /* Lets move through the buffer to reset every single element by perfoming  a read operation */
    while( AppQueue_isQueueEmpty(queue) == FALSE )
    {      
        /* To erase the data space read */
        memcpy((queue->buffer + queue->tail), zero_array, queue->size);        
        queue->tail += queue->size;
            
        queue->empty = FALSE;

        /* Check if its necessary to restart the TAIL buffer index*/
        queue->tail = ((queue->tail == BUFFER_SIZE(queue))? 0: queue->tail);

        /* Check if there is an available data to read from the buffer. If both (tail & head) has the same value 
            there is no more data to perform a read operation, otherwise, Its already possible to write 
            a new data*/
        queue->empty = ((queue->tail == queue->head)? TRUE : FALSE);
        queue->full = ((queue->tail == queue->head)? FALSE : TRUE);
    }
}