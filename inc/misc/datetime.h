#include "globals.h"

#ifndef DATE_DEF_
#define DATE_DEF_
/* Date object */
struct Date {
	u8 year;
	u8 month;
	u8 day;
	u8 dow;
};
#endif

#ifndef TIME_DEF_
#define TIME_DEF_
/* Time object */
struct Time {
	u8 hour;
	u8 minute;
	u8 second;
};
#endif

#ifndef DATETIME_DEF_
#define DATETIME_DEF_
/* Combined DateTime object */
struct DateTime {
	u8 year;
	u8 month;
	u8 day;
	u8 dow;
	u8 hour;
	u8 minute;
	u8 second;
};
#endif

void serializeDateTime(struct DateTime *date_time, u8 buffer[]);
void deSerializeDateTime(u8 buffer[], struct DateTime *date_time);
