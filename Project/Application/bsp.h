#ifndef BSP_H_
#define BSP_H_

#include "stdint.h"

typedef struct _App_TmTime
{
    uint8_t tm_sec;         /* seconds,  range 0 to 59          */
    uint8_t tm_min;         /* minutes, range 0 to 59           */
    uint8_t tm_hour;        /* hours, range 0 to 23             */
    uint8_t tm_mday;        /* day of the month, range 1 to 31  */
    uint8_t tm_mon;         /* month, range 0 to 11             */
    uint16_t tm_year;       /* years in rage 1900 2100          */
    uint8_t tm_wday;        /* day of the week, range 0 to 6    */
} App_TmTime;

typedef struct _App_Message
{
    uint8_t msg;          /*!< Store the message type to send */
    App_TmTime tm;     /*!< time and date in stdlib tm format */
} App_Message;

typedef enum
{
    SERIAL_MSG_NONE = 0,
    SERIAL_MSG_TIME,
    SERIAL_MSG_DATE,
    SERIAL_MSG_ALARM
} App_Messages;

#endif