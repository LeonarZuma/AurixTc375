#ifndef CAN_TASK_H
#define CAN_TASK_H

#define TX_MSG_NO               3U
#define ISR_PRIORITY_CAN_RX     1

void InitCanTask_Core0(void);

void PeriodicCanTask_Core0(void);

#endif