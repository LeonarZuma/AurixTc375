#include <stdio.h>
#include <stdint.h>
#include "Phase1.h"

const uint8_t week_days[8][10] = 
{
    "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday", "Sunday"
};

const uint8_t year_months[13][13] =
{
    "January", "February", "March",
        "April", "May", "June", 
        "July", "August", "September",
        "October", "November", "December"
};

const uint8_t year_months_str_size[]= {7,8,5,5,3,4,4,6,9,7,8,8};
const uint8_t week_days_str_size[]= {6,8,9,8,6,8,6};

/* Declaring the private functions */
static void add_stringToString(int8_t *string_dst, const int8_t *string_src, uint16_t ins_index, const uint8_t string_src_size)
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

uint16_t array_largestElement( uint16_t *array, uint8_t size )
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
    add_stringToString(string, alarm_string, 0, sizeof(alarm_string)/sizeof(*alarm_string));
    convert_DecToChar(string + 6, hours);
    *(string+8) = ':';
    convert_DecToChar((string + 9), minutes);
    *(string+11) = '\0';
}

void set_dateString( int8_t *string, uint8_t month, uint8_t day, uint16_t year, uint8_t weekday)
{
    uint8_t local_ins_index = 0;
    int8_t local_day_to_string[3];
    int8_t local_year_to_string[3][2];
    const int8_t string_punctuation[][2]={" ",", "," "};
    const int8_t string_punctuation_size[] = {1,2,1};
    
    /* This substraction are done to correct the start to make 0 of the first element selected*/
    month--;
    weekday--;
    
    /* Inserting the month */
    add_stringToString(string, (int8_t *)(year_months + month),local_ins_index,*(year_months_str_size + month));

    local_ins_index = *(year_months_str_size + month);

    /* Placing punctuation marks */
    add_stringToString(string, *(string_punctuation), local_ins_index, *(string_punctuation_size));
    local_ins_index = local_ins_index + *(string_punctuation_size);
    
    /* Placing date no. */
    convert_DecToChar(local_day_to_string, day);
   * (local_day_to_string+2)='\0';
    add_stringToString(string, local_day_to_string, local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(local_day_to_string)/sizeof(*local_day_to_string)) - 1);

    /*Placing punctuation marks*/
    add_stringToString(string, *(string_punctuation + 1), local_ins_index, *(string_punctuation_size + 1));
    local_ins_index = local_ins_index + *(string_punctuation_size + 1);

    /* Placing year no. */
    /* The pointer *(*(arr + i ) + j ) is equivalent to subscript expression arr[i][j] */

    convert_DecToChar(*(local_year_to_string), (year/100));
    *(*(local_year_to_string)+2)='\0';

    convert_DecToChar(*(local_year_to_string+1), (year%100));
    *(*(local_year_to_string+1)+2)='\0';

    add_stringToString(string, *(local_year_to_string+0), local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(*(local_year_to_string))/sizeof(*(*(local_year_to_string)))));

    add_stringToString(string, *(local_year_to_string+1), local_ins_index, 2);
    local_ins_index = local_ins_index + ((sizeof(*(local_year_to_string + 1))/sizeof(*(*(local_year_to_string + 1)))));
    
    /* Placing punctuation marks */
    add_stringToString(string, *(string_punctuation + 2), local_ins_index, *(string_punctuation_size + 2));
    local_ins_index = local_ins_index + *(string_punctuation_size + 2);

    /* Inserting the day */
    add_stringToString(string, (int8_t *)(week_days + weekday),local_ins_index,*(week_days_str_size + weekday));
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

void array_print(uint16_t *array, uint8_t size)
{
    for (int8_t i = 0; i<=size; i++)
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