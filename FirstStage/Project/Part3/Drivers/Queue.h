#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct
{
    void        *buffer;    //pointer to array that store buffer data
    uint32_t    elements;   //number of elements to store (the queue lenght) 
    uint8_t     size;       //size of the elements to store
    uint8_t     head;       //variable to signal the next queue space to write 
    uint8_t     tail;       //variable to signal the next queue space to read
    uint8_t     empty;      //flag to indicate if the queue is empty
    uint8_t     full;       //flag to indicate if the queue is full
    
} AppQue_Queue;

#define BUFFER_SIZE(queue_name)   (queue_name->elements * queue_name->size)

void AppQueue_initQueue( AppQue_Queue *queue );

uint8_t AppQueue_writeData( AppQue_Queue *queue, void *data );

uint8_t AppQueue_readData( AppQue_Queue *queue, void *data );

uint8_t AppQueue_isQueueEmpty( AppQue_Queue *queue );

void AppQueue_flushQueue( AppQue_Queue *queue );

#endif