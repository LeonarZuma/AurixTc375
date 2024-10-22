/**
 * @file    <Queue.c>
 * @brief   **This is an implentation of a more complex circular Buffer, using void pointers it's able to 
 *              received any data type,**
 *
 * Write a detail description of your driver, what it does and how and how to work with its interfaces
 * Use as many lines as you need
 *
 * @note    If there is something that needs to be take into account beyond its normal
 *          utilization, write right here
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Phase1.h"
#include "Buffer.h"
#include "Queue.h"
#include "IfxCpu.h"
#include "IfxStm.h"
#include "IfxSrc.h"

/**
 *
 *  @brief   **  Routine to check if mutex has been realease after a us waiting time **
 *
 * This functions waits until a certain us time period has been reach to as part of the mutex queue routine
 * to write, read, flush or check if empty buffer. The waiting time porpouse is to add window to release the
 * mutex while the program is executing.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   microseconds   Waiting time
 *
 * @retval  None
 * 
 * */
static void AppQueue_mutexWaitUs(AppQue_Queue *queue, uint32_t microseconds)
{
    uint32_t ticks = IfxStm_getTicksFromMicroseconds( &MODULE_STM0, microseconds );

    /* Check if queue by default is free, if is not, wait some us and check again*/
    if (queue->mutex == FALSE)
    {
        IfxStm_waitTicks( &MODULE_STM0, ticks );
    }
    else
    {
        /* Do nothing Check the nex queue comprobation */
    }
}

/**
 *
 *  @brief   **  Initializes the queue **
 *
 * Initializes the queue by setting the head and tail elements to zero, and the values of empty to one and
 * full to zero
 * 
 * @param[in]   queue   Queue control structure
 *
 * @retval  None
 * 
 * */
void AppQueue_initQueue( AppQue_Queue *queue )
{
    queue->head = 0;
    queue->tail = 0;
    queue->empty = TRUE;
    queue->full = FALSE;
    queue->mutex = TRUE;
}

/**
 *
 *  @brief   ** Interface that allows writing an element to the queue **
 *
 * Copies the information referenced by the empty pointer data to the buffer controlled by queue, the 
 * number of bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if the 
 * write is successful the function returns a TRUE, and if not a FALSE. This function should determine 
 * when the queue is full by the current write operation and prevent the writing of a new element when 
 * it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy on the queue buffer
 *
 * @retval  write_operResult        True if the write was succesfull, otherwise FALSE
 * 
 * */
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

/**
 *
 *  @brief   **  Interface that allows reading an element from the queue. **
 *
 * Reads data from the buffer controlled by queue, the data is copied into the data type referenced by 
 * the empty pointer data, the number of bytes to copy is indicated by the Size element of the 
 * AppQue_Queue type structure, if the read is successful the function returns a TRUE and otherwise a 
 * FALSE. This function should determine when the queue is emptied by the current read operation and 
 * prevent the reading of a new element when it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy an element from the queue buffer
 *
 * @retval  read_operResult    True if the read was succesfull, otherwise FALSE
 * 
 * */
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

/**
 *
 *  @brief   ** Interface that indicates if the queue is empty **
 *
 * The function returns a one if there are no more elements that can be read from the queue and zero if 
 * there is at least one element that can be read.
 * 
 * @param[in]   queue   Queue control structure
 *
 * @retval  queue->empty    True if the buffer is empty, otherwise FALSE
 * 
 * */
uint8_t AppQueue_isQueueEmpty( AppQue_Queue *queue )
{
    return queue->empty;
}


/**
 *
 *  @brief   ** Interface that empties the queue. **
 *
 * The function must empty the queue in case it has elements inside it, the information will be discarded
 * 
 * @param[in]   queue   Queue control structure
 *
 * @retval  None
 * 
 * */
void AppQueue_flushQueue( AppQue_Queue *queue )
{
    /* calling init queue to flush the queue */
    AppQueue_initQueue(queue);
}

/**
 *
 *  @brief   ** Interface that allows writing an element to the queue **
 *
 * Copies the information referenced by the empty pointer data to the buffer controlled by queue, the 
 * number of bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if the 
 * write is successful the function returns a TRUE, and if not a FALSE. This function should determine 
 * when the queue is full by the current write operation and prevent the writing of a new element when 
 * it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy on the queue buffer
 *
 * @retval  write_operResult        True if the write was succesfull, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 * 
 * */
uint8_t AppQueue_writeDataIsr( AppQue_Queue *queue, void *data )
{
    uint8_t write_operResult = FALSE;
    DISABLE_ISR();
    write_operResult = AppQueue_writeData(queue, data);
    ENABLE_ISR();

    return write_operResult;
}

/**
 *
 *  @brief   **  Interface that allows reading an element from the queue. **
 *
 * Reads data from the buffer controlled by queue, the data is copied into the data type referenced by 
 * the empty pointer data, the number of bytes to copy is indicated by the Size element of the 
 * AppQue_Queue type structure, if the read is successful the function returns a TRUE and otherwise a 
 * FALSE. This function should determine when the queue is emptied by the current read operation and 
 * prevent the reading of a new element when it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy an element from the queue buffer
 *
 * @retval  read_operResult    True if the read was succesfull, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete 
 * 
 * */
uint8_t AppQueue_readDataIsr( AppQue_Queue *queue, void *data )
{
    uint8_t read_operResult = FALSE;
    DISABLE_ISR();
    read_operResult = AppQueue_readData(queue, data);
    ENABLE_ISR();

    return read_operResult;
}

/**
 *
 *  @brief   ** Interface that indicates if the queue is empty **
 *
 * The function returns a one if there are no more elements that can be read from the queue and zero if 
 * there is at least one element that can be read.
 * 
 * @param[in]   queue   Queue control structure
 *
 * @retval  queue->empty    True if the buffer is empty, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 * 
 * */
uint8_t AppQueue_isQueueEmptyIsr( AppQue_Queue *queue )
{
    uint8_t queue_empty = FALSE;
    DISABLE_ISR();
    queue_empty =  AppQueue_isQueueEmpty(queue);
    ENABLE_ISR();

    return queue_empty;
}

/**
 *
 *  @brief   ** Interface that empties the queue. **
 *
 * The function must empty the queue in case it has elements inside it, the information will be discarded
 * 
 * @param[in]   queue   Queue control structure
 *
 * @retval  None
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 *
 * */
void AppQueue_flushQueueIsr( AppQue_Queue *queue )
{
    DISABLE_ISR();
    AppQueue_flushQueue(queue);
    ENABLE_ISR();
}

/**
 *
 *  @brief   ** Interface that allows writing an element to the queue **
 *
 * Copies the information referenced by the empty pointer data to the buffer controlled by queue, the 
 * number of bytes to copy is indicated by the Size element of the AppQue_Queue type structure, if the 
 * write is successful the function returns a TRUE, and if not a FALSE. This function should determine 
 * when the queue is full by the current write operation and prevent the writing of a new element when 
 * it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy on the queue buffer
 * @param[in]   microseconds    timeoout wait for mutex release
 *
 * @retval  write_operResult        True if the write was succesfull, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 * 
 * */
uint8_t AppQueue_writeDataMutex( AppQue_Queue *queue, void *data, uint32_t microseconds)
{
    uint8_t write_operResult = FALSE;
    
    AppQueue_mutexWaitUs(queue, microseconds);

    /* Second time check, if after the us waiting time the queue has been free again */
    if(queue->mutex == TRUE)    /* Check if the mutex is free */
    {
        queue->mutex = FALSE;   /* Set mutex free as FALSE */
        write_operResult = AppQueue_writeData(queue, data);
        queue->mutex = TRUE;    /* The mutex is free once the operation is complete */
    }
    else
    {
        /* Do nothing complete the program */
    }

    return write_operResult;
}

/**
 *
 *  @brief   **  Interface that allows reading an element from the queue. **
 *
 * Reads data from the buffer controlled by queue, the data is copied into the data type referenced by 
 * the empty pointer data, the number of bytes to copy is indicated by the Size element of the 
 * AppQue_Queue type structure, if the read is successful the function returns a TRUE and otherwise a 
 * FALSE. This function should determine when the queue is emptied by the current read operation and 
 * prevent the reading of a new element when it is.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   data    pointer to data to copy an element from the queue buffer
 * @param[in]   microseconds    timeoout wait for mutex release
 *
 * @retval  read_operResult    True if the read was succesfull, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete 
 * 
 * */
uint8_t AppQueue_readDataMutex( AppQue_Queue *queue, void *data, uint32_t microseconds )
{
    uint8_t read_operResult = FALSE;

    AppQueue_mutexWaitUs(queue, microseconds);

    /* Second time check, if after the us waiting time the queue has been free again */
    if(queue->mutex == TRUE)    /* Check if the mutex is free */
    {
        queue->mutex = FALSE;   /* Set mutex free as FALSE */
        read_operResult = AppQueue_readData(queue, data);
        queue->mutex = TRUE;    /* The mutex is free once the operation is complete */
    }
    else
    {
        /* Do nothing complete the program */
    }

    return read_operResult;
}

/**
 *
 *  @brief   ** Interface that indicates if the queue is empty **
 *
 * The function returns a one if there are no more elements that can be read from the queue and zero if 
 * there is at least one element that can be read.
 * 
 * @param[in]   queue   Queue control structure
 * @param[in]   microseconds    timeoout wait for mutex release
 *
 * @retval  queue->empty    True if the buffer is empty, otherwise FALSE
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 * 
 * */
uint8_t AppQueue_isQueueEmptyMutex( AppQue_Queue *queue, uint32_t microseconds )
{
    uint8_t queue_empty = FALSE;

    AppQueue_mutexWaitUs(queue, microseconds);

    /* Second time check, if after the us waiting time the queue has been free again */
    if(queue->mutex == TRUE)    /* Check if the mutex is free */
    {
        queue->mutex = FALSE;   /* Set mutex free as FALSE */
        queue_empty =  AppQueue_isQueueEmpty(queue);
        queue->mutex = TRUE;    /* The mutex is free once the operation is complete */
    }    
    else
    {
        /* Do nothing complete the program */
    }

    return queue_empty;
}

/**
 *
 *  @brief   ** Interface that empties the queue. **
 *
 * The function must empty the queue in case it has elements inside it, the information will be discarded
 * 
 * @param[in]   queue           Queue control structure
 * @param[in]   microseconds    timeoout wait for mutex release
 *
 * @retval  None
 * 
 * @note    This Writing Queue disable interrupts after writing and enables before the operations is complete
 *
 * */
void AppQueue_flushQueueMutex( AppQue_Queue *queue, uint32_t microseconds )
{
    AppQueue_mutexWaitUs(queue, microseconds);

    /* Second time check, if after the us waiting time the queue has been free again */
    if(queue->mutex == TRUE)    /* Check if the mutex is free */
    {
        queue->mutex = FALSE;   /* Set mutex free as FALSE */
        AppQueue_flushQueue(queue);
        queue->mutex = TRUE;    /* The mutex is free once the operation is complete */
    }
    else
    {
        /* Do nothing complete the program */
    }
}