#ifndef LEDS_H_
#define LEDS_H_

enum leds_enum { led0 = 5, led1, led2, led3, led4, led5};

void Leds_InitTask(void);
void Leds_PeriodicTask(void);

#endif