#ifndef PHASE1_H_
#define PHASE1_H_

uint16_t array_largestElement( uint16_t *array, uint8_t size );

void sortArray( uint16_t *array, uint8_t size );

void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds );

void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes);

void set_dateString( int8_t *string, uint8_t month, uint8_t day, uint16_t year, uint8_t weekday);

void array_print(uint16_t *array, uint8_t size);



#endif