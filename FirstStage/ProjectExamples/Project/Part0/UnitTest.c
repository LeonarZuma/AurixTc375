#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "Phase1.h"
#include "Buffer.h"


/* Initialize the circular buffer by setting the head and tail elements to zero, and the values of empty to TRUE
and full to FALSE. */

/* Write a new 8-bit data to the buffer if there is available space; if there is no space, no data will be 
written. Function will determine if the queue is full with the last data written */

/* Reads a data from the buffer, the data that is read will no longer exist within the buffer. If the buffer is 
empty, no data will be read, and the value returned by the function will not be valid. Function will determine if
the queue is empty with the last data read */

/* The function returns one if there are no more elements that can be read from the circular buffer, and zero if 
there is at least one element that can be read. It is necessary to use this function before using the read 
function.
*/