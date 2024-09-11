#ifndef UNITTEST_H_
#define UNITTEST_H_

void test_queueInit(AppQue_Queue *test_queueBuffer, uint8_t *array, uint32_t size);

void test_queueFullWrite(AppQue_Queue *test_queueBuffer, uint8_t *in_array, uint32_t size);

void test_queueFullRead(AppQue_Queue *test_queueBuffer, uint8_t *out_array);

void test_queueSingleWrite(AppQue_Queue *test_queueBuffer, uint8_t in_data);

void test_queueSingleRead(AppQue_Queue *test_queueBuffer, uint8_t *out_data);

void test_queueIsEmpty(AppQue_Queue *test_queueBuffer);

void test_queueIsFull(AppQue_Queue *test_queueBuffer);

#endif