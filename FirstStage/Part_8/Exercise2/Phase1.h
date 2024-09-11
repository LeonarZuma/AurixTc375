#ifndef PHASE1_H_
#define PHASE1_H_

#define CAN_PADDING_BYTES                  (0x55u)
#define MSN_TO_ZERO_MASK                   (0xFFu)
#define FALSE                              (0U)
#define TRUE                               (1U)
#define ASCII_NO_OFFSET                    (48U)
#define CAN_SING_FRAME_VALID               (1u)
#define CAN_SING_FRAME_INVALID             (0u)

uint8_t get_arrayAverage( uint8_t *array, uint8_t size );

uint16_t get_arrayLargestElement( uint16_t *array, uint8_t size );

void sortArray( uint16_t *array, uint8_t size );

void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds );

void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes);

void set_dateString( int8_t *string, uint8_t month, uint8_t day, uint16_t year, uint8_t weekday);

void CanTp_SingleFrameTx( uint8_t *data, uint8_t size );

uint8_t CanTp_SingleFrameRx( uint8_t *data, uint8_t *size );

void arrayCopy( uint8_t *arrayA, uint8_t *arrayB, uint8_t size, int8_t shift );

void print_array16Bits(uint16_t *array, uint8_t size);

void print_array8Bits(uint8_t *array, uint8_t size);



#endif