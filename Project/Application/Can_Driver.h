#ifndef CAN_H_
#define CAN_H_


#define TX_MSG_NO               (2U)

void AppClock_CAN_Init(void);

void AppClock_Can_SendTime(uint8_t *data);

#endif