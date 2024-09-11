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


New Notes
    There is only one datatype to write. I mean if you start writng in the buffer Structs of Type Message you must
    keep writing Message data types to the buffer. You cant mixup different datatypes as sending a char, then an int
    and so on.




*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"
#include "Buffer.h"
#include "Queue.h"
//#include "UnitTest.h"

#define QUEUE_BUFFER_SIZE     (6)

#define OPER_RESULT_STR(result)   ((result == TRUE)? "TRUE":"FALSE") 

/* Declare a structure to handle different datatypes */
typedef struct
{
    uint8_t id;
    uint8_t data;
    uint8_t checksum; 
} MsgType_Message;

int main( void )
{
    uint8_t write_oprResult = FALSE;
    MsgType_Message MsgToWrite;
    MsgType_Message MsgToRead;
    
    /* Buffer array to assign the memory space */
    MsgType_Message buffer[QUEUE_BUFFER_SIZE];
    AppQue_Queue Queue;    
    
    /* Set the buffer for the Queue */
    Queue.buffer = (void*)buffer;
    /* Queue lenght must be the same or less than the buffer size */
    Queue.elements = QUEUE_BUFFER_SIZE;
    /* The size of a single element */
    Queue.size = sizeof( MsgType_Message );

    /* Init queue Function call */
    AppQueue_initQueue( &Queue );

    printf("Size of one element to handle: %d\n",Queue.size);
    printf("Total Size of Buffer: %d\n",sizeof(buffer));
    printf("Queue Full is: %s\n", OPER_RESULT_STR(Queue.full));

    /* Writing a message */
    MsgToWrite.id = 97;
    MsgToWrite.data = 105u;
    MsgToWrite.checksum = 36;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    /* Writing a message */
    MsgToWrite.id = 98;
    MsgToWrite.data = 115u;
    MsgToWrite.checksum = 37;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    /* Writing a message */
    MsgToWrite.id = 99;
    MsgToWrite.data = 125u;
    MsgToWrite.checksum = 38;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    /* Writing a message */
    MsgToWrite.id = 100;
    MsgToWrite.data = 135u;
    MsgToWrite.checksum = 39;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    /* Writing a message */
    MsgToWrite.id = 101;
    MsgToWrite.data = 135u;
    MsgToWrite.checksum = 40;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    /* Writing a message */
    MsgToWrite.id = 102;
    MsgToWrite.data = 145u;
    MsgToWrite.checksum = 45;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));

    printf("Queue Full is: %s\n", OPER_RESULT_STR(Queue.full));

    /* If we call the flush opertion we wont be able to perform a read after */
    //AppQueue_flushQueue(&Queue);

    /* This message writing try is to check if we can overflow the current buffer */
    MsgToWrite.id = 103;
    MsgToWrite.data = 155u;
    MsgToWrite.checksum = 55;
    write_oprResult = AppQueue_writeData( &Queue, &MsgToWrite );
    printf("Operation Succes: %s\n",OPER_RESULT_STR(write_oprResult));
    
    printf("\n=STARING BUFFER DATA READING=\n");
    /* Reading the complete buffer */
    while( AppQueue_isQueueEmpty(&Queue) == FALSE )
    {
        AppQueue_readData( &Queue, &MsgToRead );
        printf( "\nId read from the queue: %d\n", MsgToRead.id );
        printf( "Data read from the queue: %d\n", MsgToRead.data );
        printf( "Checksum read from the queue %d\n", MsgToRead.checksum );
        printf("Queue Empty is: %s\n", OPER_RESULT_STR(Queue.empty));
    }
}