/**
 * @file    <Phase1.c>
 * @brief   **Auxiliar functions**
 *
 * This driver contains some auxiliar functions to implement the RTCC project. Some of this functions are not used in
 * the current code, but could be helpful for any future implementation
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

/* Declaring the private functions */
/**
 * @brief   ** Copy a string_src to a string_dst **
 *
 * Copy a certain string_src to string_src in a given position ins_index. 
 *
 * @param[in]   string_src_size The size of the string_src
 * @param[in]   ins_index The position in string_dst to insert string_src
 * @param[in]   string_src The address of the string_src
 * @param[out]  string_dst The addres of the new string_dst with the added string_src in the desired position
 *
 * @retval  None
 *
 * @note The ins_index permits to insert the string_src in a certain desired position string_dst
 */
void insert_stringToString(int8_t *string_dst, int8_t *string_src, uint16_t ins_index, uint8_t string_src_size)
{
    int8_t i = 0;
    /* Iteration to add every element of string_src to string_dst  */
    for(; i < (string_src_size); i++)
    {
        *(string_dst + ins_index + i) = *(string_src + i);
    }
    /* Add the end element to string */
    *(string_dst + ins_index + i) = '\0';
}

/**
 * @brief   ** Convert a pair of decimal numbers DD to the equivalent char representation "DD" **
 *
 * Given a certain pair of numbers DD, translate the value to the equivalent ASCII representation "DD". Example,
 * 10 decimal is "10", is part of an array of two elements '1' and '0' and each one has a decimal equivalent value
 * 48 and 49.
 *
 * @param[in]   dec_value The decimal pair of numbers DD
 * @param[out]  ins_index The translated number to char ASCII representation "DD"
 *
 * @retval  None
 *
 */
static void convert_DecToChar(int8_t *dec_value_string, uint8_t dec_value)
{
    /* Unit ASCII equivalent */
    *dec_value_string = (dec_value / 10) + ASCII_NO_OFFSET;
    /* Tens ASCII equivalent */
    *(dec_value_string + 1) = (dec_value % 10) + ASCII_NO_OFFSET;
}

/**
 * @brief   ** Swap a single element between two arrays **
 *
 * Swap a single element between two arrays
 *
 * @param[in]    element_src The address of the src element
 * @param[out]   element_dst The address of the dst element
 *
 * @retval  None
 *
 */
static void array_swapElements(uint16_t *element_src, uint16_t *element_dst)
{
    uint16_t local_swap_auxiliar = *element_dst;

    *element_dst = *element_src;
    *element_src = local_swap_auxiliar;
}

/**
 * @brief   ** Given a integer value x return the absolute value of it **
 *
 * Returns the non-negative value of x without regard to its sign
 *
 * @param[in]   value Parameer description based on what does
 *
 * @retval  absolute value Returns the non-negative representation of a given number
 *
 */
static uint8_t get_absoluteVal(int8_t value)
{
    return (value > 0) ? value : (value * (-1));
}

/* Declaring all the public functions */
/**
 * @brief   **A function that calculates the average of the values in an array**
 *
 * The function returns the average value of the elements in an array, the result it's returned as an 
 * integer value, it is not necessary to have precision with decimal values
 *
 * @param[in]   array a pointer that receives the address where the array with the values to be averaged is located
 * @param[in]   size array size
 *
 * @retval  <local_average> average of the values in an array
 */
uint8_t get_arrayAverage( uint8_t *array, uint8_t size )
{
    uint16_t local_average = 0;
    for (uint8_t i=0; i<size; i++)
    {
        local_average = (local_average + *(array + i));
    }
    local_average = local_average / size;
    /* typecasting to return an 8bit unsigned data value */
    return (uint8_t)local_average;
}

/**
 * @brief   **Function to get the largest number in a given array**
 *
 * The function returns the highest value number in an array.
 *
 * @param[in]   array a pointer that receives the address where the array with the values is located
 * @param[in]   size array size
 *
 * @retval  <local_largest_val> the largest number in a given array
 *
 */
uint16_t get_arrayLargestElement( uint16_t *array, uint8_t size )
{
    uint16_t local_largest_val = 0;
    for (int8_t i=0; i<size; i++)
    {
        if (*(array+i) > local_largest_val)
        {
            local_largest_val = *(array + i);
        }
        else
        {
            /* do nothing */
        }
    }
    return local_largest_val;
}

/**
 * @brief   **Function to sort an array of a given size**
 *
 * The function orders the elements in an array from smallest to largest
 *
 * @param[inout]   array a pointer that receives the address where the array with the values to be sorted is located
 * @param[in]      size array size
 *
 * @retval  None
 *
 */
void sortArray( uint16_t *array, uint8_t size )
{
    uint8_t local_correction_index = 0; /* A subindex for the subcycles iterations  */
    uint8_t local_is_high_flag = 0;     /* Semiboolean variable to check if the comprobation is done */
    uint8_t max_cycle_iter = size - 1;  /* The maximum index value */
    uint16_t high_elements = 0; /* Contains the total number of elements higher than i-element */
    
    /* we are going to implement a Cyclic Sort Algorithm */
    for (int8_t cycle = 0; cycle < max_cycle_iter; cycle++)
    {
        local_correction_index = cycle + 1;
        local_is_high_flag = FALSE;
        high_elements = 0;
        //check if the element is higher than the following element
        //if its true, lets check with the next element
        // check until the condition is not meet
        //if is necessary, swap position with the no meeting condition number              
        
        while(local_is_high_flag == FALSE)
        {
            if (local_correction_index<=max_cycle_iter)
            {
                if (*(array + cycle) > *(array + local_correction_index))
                {
                    high_elements++;
                }
                else if (*(array + cycle) == *(array + local_correction_index))
                {
                    /* Do nothing */
                }
                else
                {
                    /* Do nothing */
                }
                local_is_high_flag = FALSE;
                local_correction_index++;
            }
            else
            {
                local_is_high_flag = TRUE;
                if(high_elements>0)
                {
                    array_swapElements((array + cycle), (array +cycle+ high_elements));
                    //local_is_high_flag = FALSE;
                    high_elements = 0;
                    local_correction_index = cycle + 1;
                }
                else
                {
                    /* Do nothing */
                }
            }
        }
    }
}

/**
 * @brief   **Function to convert time to a string representation**
 *
 * The function receives time in 24h format and return a string representation with theformat “00:00:00“.
 *
 * @param[out]  string pointer to array address to store the time string
 * @param[in]   hours hours in 24h format
 * @param[in]   minutes  minutes
 * @param[in]   seconds seconds
 *
 * @retval  None
 * 
 */
void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds )
{
    convert_DecToChar(string, hours);
    *(string+2) = ':';
    convert_DecToChar((string+3), minutes);
    *(string+5) = ':';
    convert_DecToChar((string+6), seconds);
    *(string+8) = '\0';
}

/**
 * @brief   **Function to convert time to a string representation plus a string**
 *
 * The function shall receive time in 24h format with no seconds, and return a string representation with the 
 * following format “ALARM=00:00“
 *
 * @param[out]   string pointer to array address to store the alarm string
 * @param[in]    hours hours in 24h format
 * @param[in]    minutes minutes
 *
 * @retval  None
 * 
 */
void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes)
{
    uint8_t alarm_string[] = "ALARM=00:00";
    insert_stringToString((int8_t*)string, (int8_t*)alarm_string, 0, sizeof(alarm_string)/sizeof(*alarm_string));
    convert_DecToChar(string + 6, hours);
    *(string+8) = ':';
    convert_DecToChar((string + 9), minutes);
    *(string+11) = '\0';
}

/**
 * @brief   **Function to convert date to a string representation**
 *
 * The function shall receive date in day of the month, month and year and return a string representation with the 
 * following format “Mon dd, yyyy Dy“
 *
 * @param[out]  string pointer to array address to store the time string
 * @param[in]   month month from 1 to 12
 * @param[in]   day month from 1 to 12
 * @param[in]   year month from 1 to 12
 * @param[in]   weekday day of the week
 *
 * @retval  None
 */
void set_dateString( int8_t *string, uint8_t month, uint8_t day, uint16_t year, uint8_t weekday)
{
    uint8_t week_days[8][10] = 
    {
        "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday"
    };

    uint8_t year_months[13][13] =
    {
        "January", "February", "March",
            "April", "May", "June", 
            "July", "August", "September",
            "October", "November", "December"
    };

    uint8_t year_months_str_size[]= {7,8,5,5,3,4,4,6,9,7,8,8};
    uint8_t week_days_str_size[]= {6,8,9,8,6,8,6};

    uint8_t local_ins_index = 0;
    int8_t local_day_to_string[3];
    int8_t local_year_to_string[3][2];
    int8_t string_punctuation[][2]={" ",", "," "};
    int8_t string_punctuation_size[] = {1,2,1};
    
    /* This substraction are done to correct the start to make 0 of the first element selected*/
    month--;
    weekday--;
    
    /* Inserting the month */
    insert_stringToString(string, (int8_t *)(year_months + month),local_ins_index,*(year_months_str_size + month));

    local_ins_index = *(year_months_str_size + month);

    /* Placing punctuation marks */
    insert_stringToString(string, *(string_punctuation), local_ins_index, *(string_punctuation_size));
    local_ins_index = local_ins_index + *(string_punctuation_size);
    
    /* Placing date no. */
    convert_DecToChar(local_day_to_string, day);
   * (local_day_to_string+2)='\0';
    insert_stringToString(string, local_day_to_string, local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(local_day_to_string)/sizeof(*local_day_to_string)) - 1);

    /*Placing punctuation marks*/
    insert_stringToString(string, *(string_punctuation + 1), local_ins_index, *(string_punctuation_size + 1));
    local_ins_index = local_ins_index + *(string_punctuation_size + 1);

    /* Placing year no. */
    /* The pointer *(*(arr + i ) + j ) is equivalent to subscript expression arr[i][j] */

    convert_DecToChar(*(local_year_to_string), (year/100));
    *(*(local_year_to_string)+2)='\0';

    convert_DecToChar(*(local_year_to_string+1), (year%100));
    *(*(local_year_to_string+1)+2)='\0';

    insert_stringToString(string, *(local_year_to_string+0), local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(*(local_year_to_string))/sizeof(*(*(local_year_to_string)))));

    insert_stringToString(string, *(local_year_to_string+1), local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(*(local_year_to_string + 1))/sizeof(*(*(local_year_to_string + 1)))));
    
    /* Placing punctuation marks */
    insert_stringToString(string, *(string_punctuation + 2), local_ins_index, *(string_punctuation_size + 2));
    local_ins_index = local_ins_index + *(string_punctuation_size + 2);

    /* Inserting the day */
    insert_stringToString(string, (int8_t *)(week_days + weekday),local_ins_index,*(week_days_str_size + weekday));
}

/**
 * @brief   **Packing messages into a specific format**
 *
 * The following function receives an array of data size specified by size, larger than 0 bytes but no more than
 * 7, the function appends a first byte where the most significant nibble will be always zero and the less 
 * significant nibble will indicate the number of bytes after that it returns through a pointer 8 bytes with the
 * message packet in CAN-TP format. Function returns the array with the append byte using the same data 
 * parameter, not matter the size indicated by the size parameter, but in case size larger than 7, the rest of values
 * will be ignored. 
 *
 * @param[out]   data a pointer that receives the address where the array with the values to be sorted is located
 * @param[in]    size array size
 *
 * @retval  None
 *
 * @note User must guarantee array pointed by data has at least a size of 8 bytes.
 */
void CanTp_SingleFrameTx( uint8_t *data, uint8_t size )
{
    const uint8_t can_frame_size = 8;
    uint8_t local_data[can_frame_size];
    
    /* move to shift one position right the array elements */
    arrayCopy(data, local_data,can_frame_size, 1);
    arrayCopy(local_data, data, can_frame_size, 0);

    /* Insert the first data element */
    /* Set the MSN will always be zero */
    /* Set the LSN to the number of */
    if (size > 7)
    {
        size = 7;
    }
    else
    {
        /* Do nothing */
    }
    *data = size & (~0xFFF8);
}

/**
 * @brief   **Provide a brief fucntion description (just one line)**
 *
 * The function receives an array of 8 bytes of data with CAN-TP format where the first byte indicate if it was 
 * a single frame and the number of valid bytes received. Function must validate if it was a valid single frame and 
 * after that remove the first byte and return the number of valid bytes received using parameter size 
 *
 * @param[out]  data a pointer that receives the address where the array with the values to be sorted is located
 * @param[in]   size array size
 *
 * @retval  None
 * 
 */
uint8_t CanTp_SingleFrameRx( uint8_t *data, uint8_t *size )
{
    const uint8_t can_frame_size = 8;
    uint8_t local_data[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};

    uint8_t local_validation = CAN_SING_FRAME_INVALID;
    /* We are taking out the value of size from the CAN frame */
    *size = *data;
    if(*data <= 0x07)
    {
        *data = 0;
        local_validation = CAN_SING_FRAME_VALID;
        arrayCopy(data, local_data, can_frame_size, -1);
        arrayCopy(local_data, data, can_frame_size, 0);
    }
    else
    {
        /* Do nothing */
    }
    return local_validation;
}

/**
 * @brief   **Print array of 16bits elements**
 *
 * Print all the elements in the given array
 *
 * @param[in]   array a pointer that receives the address where the array with the values to be sorted is located
 * @param[in]   size array size
 *
 * @retval  None
 */
void print_array16Bits(uint16_t *array, uint8_t size)
{
    for (int8_t i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}

/**
 * @brief   **Print array of 8bits elements**
 *
 * Print all the elements in the given array
 *
 * @param[in]   array a pointer that receives the address where the array with the values to be sorted is located
 * @param[in]   size array size
 *
 * @retval  None
 */
void print_array8Bits(uint8_t *array, uint8_t size)
{
    for (int8_t i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}

/**
 * @brief   **A function that copies an array to another array**
 *
 * The function should copy the contents of one array and place it in another array in such a way that after calling
 * the function both arrays have the same elements.
 *
 * @param[in]   arrayA  pointer that receives the address of the array with the information to copy
 * @param[out]  arrayB  pointer that receives the address of the array to which to copy the information
 * @param[in]   size  the size of the array to copy
 * @param[in]   shift  the position in ArrayA to copy ArrayB, if the shift is not necessary write a 0.
 *
 * @retval  None
 * 
 */
void arrayCopy( uint8_t *arrayA, uint8_t *arrayB, uint8_t size, int8_t shift )
{
    uint8_t abs_shift = get_absoluteVal(shift);
    for(uint8_t i = 0; i< (size - abs_shift); i++)
    {
        if(shift < 0)
        {                  
            *(arrayB + i) = *(arrayA + i + abs_shift);
        }
        else 
        /*if (shift >= 0)*/
        {
            *(arrayB + i + shift) = *(arrayA + i);
        }
    }
}

/**
 * @brief   **Un-Packing bytes to serialize messages**
 *
 * takes a structure with the elements below and place them byte by byte into an array made of 7 bytes, information 
 * shall be place in the following order: (Where word0 is the less significant byte of word element and word3 is the
 * most significant byte, same with hword0 and hword1).
 *
 * @param[in]   message a pointer that receives the address where the struct with the data to un-pack is located
 * @param[out]  array a pointer that receives the address where the array with the un-packing data is located
 *
 * @retval  None
 *
 */
void unpackingBytes( Struct_Pack *message, uint8_t *array )
{
    union
    {
        uint8_t local_byte_array[8];
        Struct_Pack local_message;        
    } local_union;
    
    local_union.local_message.word = message->word;
    local_union.local_message.byte = message->byte;
    local_union.local_message.hword = message->hword;

    local_union.local_byte_array[5] = local_union.local_byte_array[6];
    local_union.local_byte_array[6] = local_union.local_byte_array[7];
    
    insert_stringToString((int8_t *)array, (int8_t *)local_union.local_byte_array,0,CALCUTATE_SIZE(local_union.local_byte_array));
}

/**
 * @brief   **Packing bytes from a serial message**
 *
 *  takes an array made of 11 bytes and place that information into a defined structured, information shall be place
 * in the following order: (Where word0 is the less significant byte of word element and word3 is the most 
 * significant byte, same with hword0 and hword1).
 *
 * @param[out]  message a pointer that receives the address where the struct with the data to pack is located
 * @param[in]   array a pointer that receives the address where the array with the packing data is located
 *
 * @retval  None
 * 
 */
void PackingBytes( uint8_t *array, Struct_Pack_11bits *message )
{
    union
    {
        uint8_t local_byte_array[12];
        Struct_Pack_11bits local_message;
    } local_union;
    
    uint8_t local_array_aux[]=
    {
        *(array),*(array+1),*(array+2),*(array+3),
        *(array+7),*(array+8),*(array+9),*(array+10),
        *(array+4),0,
        *(array+5),*(array+6)
    };

    insert_stringToString((int8_t *)local_union.local_byte_array, (int8_t *)local_array_aux,0,CALCUTATE_SIZE(local_array_aux));
    *message = local_union.local_message;
}