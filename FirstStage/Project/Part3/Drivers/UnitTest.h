#ifndef UNITTEST_H_
#define UNITTEST_H_

void test_bufferInit(AppBuffer_Buffer *test_circBuffer, uint8_t *array, uint32_t size);

void test_bufferFullWrite(AppBuffer_Buffer *test_circBuffer, uint8_t *in_array, uint32_t size);

void test_bufferFullRead(AppBuffer_Buffer *test_circBuffer, uint8_t *out_array);

void test_bufferSingleWrite(AppBuffer_Buffer *test_circBuffer, uint8_t in_data);

void test_bufferSingleRead(AppBuffer_Buffer *test_circBuffer, uint8_t *out_data);

void test_bufferIsEmpty(AppBuffer_Buffer *test_circBuffer);

void test_bufferIsFull(AppBuffer_Buffer *test_circBuffer);

#endif