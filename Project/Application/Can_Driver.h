#ifndef CAN_H_
#define CAN_H_

#define TX_MSG_NO                   (2U)

void AppClock_CAN_Init(void);

void AppClock_Can_SendTime(uint8_t txmessage_idx, uint8_t *data);

uint8_t AppClock_Can_Decimal2BCD (uint8_t data);

#endif