#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

/* Declaring the private functions */
void insert_stringToString(int8_t *string_dst, int8_t *string_src, uint16_t ins_index, uint8_t string_src_size)
{
    int8_t i = 0;
    for(; i < (string_src_size); i++)
    {
        *(string_dst + ins_index + i) = *(string_src + i);
    }
    *(string_dst + ins_index + i) = '\0';
}
static void convert_DecToChar(int8_t *dec_value_string, uint8_t dec_value)
{
    *dec_value_string = (dec_value / 10) + ASCII_NO_OFFSET;
    *(dec_value_string + 1) = (dec_value % 10) + ASCII_NO_OFFSET;
}
static void array_swapElements(uint16_t *element_src, uint16_t *element_dst)
{
    uint16_t local_swap_auxiliar;

    local_swap_auxiliar = *element_dst;
    *element_dst = *element_src;
    *element_src = local_swap_auxiliar;
}

static uint8_t get_absoluteVal(int8_t value)
{
    return (value > 0) ? value : (value * (-1));
}

/* Declaring all the public functions */

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

uint16_t get_arrayLargestElement( uint16_t *array, uint8_t size )
{
    uint16_t local_largest_val = 0;
    for (int8_t i=0; i<size; i++)
    {
        if (*(array+i) > local_largest_val)
        {
            local_largest_val = *(array + i);
        }
    }
    return local_largest_val;
}

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
                local_is_high_flag = FALSE;
                local_correction_index++;
            }
            else
            {
                local_is_high_flag = TRUE;
                if(high_elements>0)
                {
                    array_swapElements((array + cycle), (array +cycle+ high_elements));
                    local_is_high_flag = FALSE;
                    high_elements = 0;
                    local_correction_index = cycle + 1;
                }
            }
        }
    }
}

void convert_timeToString( int8_t *string, uint8_t hours, uint8_t minutes, uint8_t seconds )
{
    convert_DecToChar(string, hours);
    *(string+2) = ':';
    convert_DecToChar((string+3), minutes);
    *(string+5) = ':';
    convert_DecToChar((string+6), seconds);
    *(string+8) = '\0';
}

void set_alarmString( int8_t *string, uint8_t hours, uint8_t minutes)
{
    int8_t alarm_string[] = "ALARM=";
    insert_stringToString(string, alarm_string, 0, sizeof(alarm_string)/sizeof(*alarm_string));
    convert_DecToChar(string + 6, hours);
    *(string+8) = ':';
    convert_DecToChar((string + 9), minutes);
    *(string+11) = '\0';
}

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
    *data = size & (~0xFF00);
}

uint8_t CanTp_SingleFrameRx( uint8_t *data, uint8_t *size )
{
    const uint8_t can_frame_size = 8;
    uint8_t local_data[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};

    uint8_t local_validation = CAN_SING_FRAME_INVALID;
    /* We are taking out the value of size from the CAN frame */
    *size = *data;
    *data = 0;
    if(!(*data & 0xF0))
    {
        if (*data <= 7)
        {
            local_validation = CAN_SING_FRAME_VALID;
            arrayCopy(data, local_data, can_frame_size, -1);
            arrayCopy(local_data, data, can_frame_size, 0);
        }
    }
    return local_validation;
}

void print_array16Bits(uint16_t *array, uint8_t size)
{
    for (int8_t i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}

void print_array8Bits(uint8_t *array, uint8_t size)
{
    for (int8_t i = 0; i<size; i++)
    {
        printf("%hu ",*(array + i));    
    }
    printf("\n");
}

void arrayCopy( uint8_t *arrayA, uint8_t *arrayB, uint8_t size, int8_t shift )
{
    uint8_t abs_shift = get_absoluteVal(shift);
    for(uint8_t i = 0; i< (size - abs_shift); i++)
    {
        if(shift < 0)
        {                  
            *(arrayB + i) = *(arrayA + i + abs_shift);
        }
        else if (shift >= 0)
        {
            *(arrayB + i + shift) = *(arrayA + i);
        }
    }
}

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

void PackingBytes( uint8_t *array, Struct_Pack_11bits *message )
{
    uint8_t local_array_aux[]= 
        {    
            *(array),*(array+1),*(array+2),*(array+3),
            *(array+7),*(array+8),*(array+9),*(array+10),
            *(array+4),
            *(array+5),*(array+6)
        };

    /*
    uint8_t local_array_aux[]= 
        {    
            *(array+3),*(array+2),*(array+1),*(array),
            *(array+10),*(array+9),*(array+8),*(array+7),
            *(array+4),
            *(array+6),*(array+5)
        };
    */

    union
    {
        uint8_t local_byte_array[11];
        Struct_Pack_11bits local_message;        
    } local_union;

    insert_stringToString((int8_t *)local_union.local_byte_array, (int8_t *)local_array_aux,0,CALCUTATE_SIZE(local_array_aux));
    *message = local_union.local_message;
}