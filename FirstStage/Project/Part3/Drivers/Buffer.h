#ifndef buffer_H_
#define buffer_H_

typedef struct
{
    uint8_t *buffer;
    uint32_t elements;
    uint32_t head;
    uint32_t tail;
    uint8_t empty;
    uint8_t full;
     
} AppBuffer_Buffer;

void AppBuffer_initBuffer( AppBuffer_Buffer *hbuffer );

void AppBuffer_writeData( AppBuffer_Buffer *hbuffer, uint8_t data );

uint8_t AppBuffer_readData( AppBuffer_Buffer *hbuffer );

uint8_t AppBuffer_isBufferEmpty( AppBuffer_Buffer *hbuffer );

uint8_t AppBuffer_isBufferFull( AppBuffer_Buffer *hbuffer );

#endif