#include "misc/datetime.h"

/* DateTime object to an array */
void serializeDateTime(struct DateTime *date_time, u8 buffer[]) {
	buffer[0] = date_time->second;
	buffer[1] = date_time->minute;
	buffer[2] = date_time->hour;
	buffer[3] = date_time->dow;
	buffer[4] = date_time->day;
	buffer[5] = date_time->month;
	buffer[6] = date_time->year;
}

/* Array to a DateTime object */
void deSerializeDateTime(u8 buffer[], struct DateTime *date_time) {
	date_time->second = buffer[0];
	date_time->minute = buffer[1];
	date_time->hour = buffer[2];
	date_time->dow = buffer[3];
	date_time->day = buffer[4];
	date_time->month = buffer[5];
	date_time->year = buffer[6];
}
