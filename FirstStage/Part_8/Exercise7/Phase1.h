#ifndef PHASE1_H_
#define PHASE1_H_

uint16_t array_largestElement( uint16_t *array, uint8_t size );

void sortArray( uint16_t *array, uint8_t size );

void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds );

void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes);

static void add_stringToString(int8_t *string_dst, int8_t *string_src, uint16_t ins_index, uint8_t string_src_size);

static void array_swapElements(uint16_t *element_src, uint16_t *element_dst);

static void convert_DecToChar(int8_t *dec_value_string, uint8_t dec_value);

void array_print(uint16_t *array, uint8_t size);



#endif