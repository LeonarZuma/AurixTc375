/**
 * @file    <Phase1.h>
 * @brief   ** Auxiliar functions **
 *
 * This driver contains some auxiliar functions to implement the RTCC project. Some of this functions are not used in
 * the current code, but could be helpful for any future implementation.
 *
 */

#ifndef PHASE1_H_
#define PHASE1_H_

/** 
  * @defgroup <CAN_MESSAGE> Auxiliar defines to boolean descriptors
  @{ */
#define CAN_PADDING_BYTES                  (0x55u)  /*!< CAN Pattern for empty bytes */
#define MSN_TO_ZERO_MASK                   (0xFFu)  /*!< Zero Mask */
#define CAN_SING_FRAME_VALID               (1u)     /*!< Valid Can Frame Value */
#define CAN_SING_FRAME_INVALID             (0u)     /*!< Invalid Can Frame Value */
/**
  @} */

/** 
  * @defgroup <ASCII> Auxiliar definition to ASCII code
  @{ */
#define ASCII_NO_OFFSET                    (48U)    /*!< ASCII offset to CHAR number representation */
/**
  @} */

/** 
  * @defgroup <Boolean> Auxiliar defines to boolean descriptors
  @{ */
#define FALSE                              (0U)     /*!< boolean 0 means FALSE */
#define TRUE                               (1U)     /*!< boolean 1 means TRUE */
/**
  @} */

/** 
  * @defgroup <Float_type> Float datatype definition by size
  @{ */
typedef float float32_t;        /*!< 32 bits size float data type */
typedef double float64_t;       /*!< 64 bits size float data type */
/**
  @} */

#define CALCUTATE_SIZE(x)       sizeof((x))/sizeof(*x)

/**
  * @brief   Seven bytes struct for un-pack Data
  */
typedef struct {
    uint32_t word:32;    /*!< Four bytes struct element */
    uint8_t byte:8;      /*!< One byte struct element */
    uint16_t hword:16;   /*!< Two bytes struct element */
} Struct_Pack;

/**
  * @brief   Eleven bytes struct for pack data
  */
typedef struct {
    uint32_t word1:32;  /*!< Four bytes struct element */
    uint32_t word2:32;  /*!< Four bytes struct element */
    uint8_t byte:8;     /*!< One byte struct element */
    uint16_t hword1:16; /*!< Two bytes struct element */
} Struct_Pack_11bits;

void insert_stringToString(int8_t *string_dst, int8_t *string_src, uint16_t ins_index, uint8_t string_src_size);

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

void unpackingBytes( Struct_Pack *message, uint8_t *array );

void PackingBytes( uint8_t *array, Struct_Pack_11bits *message );

#endif