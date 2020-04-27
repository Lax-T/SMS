#include "globals.h"

#ifndef STANDARD_MESSAGE_DEF_
#define STANDARD_MESSAGE_DEF_
/* Standard queue message */
struct StandardQueueMessage {
    u8 type;
    u8 sender;
    u8 payload[8];
};

#endif

/* Senders */
#define msSL_BUS_MASTER 0
#define msSYSTEM 1
#define msUI 2

/* Message types */
#define mtDATE_TIME 0
#define mtINT_TEMP 1
#define mtINT_HUM 2
#define mtPRESSURE 3

void decomposeTemp(float temp, u8 buffer[]);