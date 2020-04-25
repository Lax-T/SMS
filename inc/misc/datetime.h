#include "globals.h"

/* Date object */
struct Date {
	u8 year;
	u8 month;
	u8 day;
	u8 dow;
};

/* Time object */
struct Time {
	u8 hour;
	u8 minute;
	u8 second;
};

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

