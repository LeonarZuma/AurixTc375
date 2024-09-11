#ifndef BUFFER_H_
#define BUFFER_H_

typedef struct
{
    uint8_t *Buffer;
    uint32_t Elements;
    uint32_t Head;
    uint32_t Tail;
    uint8_t Empty;
    uint8_t Full;
    //add more elements if necesary 
} AppBuffer_Buffer;

void AppBuffer_initBuffer( AppBuffer_Buffer *hbuffer );

void AppBuffer_writeData( AppBuffer_Buffer *hbuffer, uint8_t data );

uint8_t AppBuffer_readData( AppBuffer_Buffer *hbuffer );

uint8_t AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer );

uint8_t AppBuffer_isBufferFull( AppBuffer_Buffer *hbuffer );

#endif