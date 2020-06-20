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

/* Check and return 1 (True) if year is leap. Starting from 2000 (assumed as 0) */
u8 dt_isLeapYear(u8 year) {
	if (year == 0) {
		return TRUE;
	}
	if ((year % 4) == 0 && year != 100) { // 2100 is not a leap year
		return TRUE;
	}
	return FALSE;
}

/* Days in month lookup array */
const u8 _dt_days_in_month_lookup[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* Return number of days in particular year/month */
u8 dt_getDaysInMonth(u8 year, u8 month) {
	if (month == 2) {
		if (dt_isLeapYear(year) == TRUE) {
			return 29;
		} else {
			return 28;
		}
	}
	return _dt_days_in_month_lookup[month - 1];
}

/* Calculate day of week for a given date */
u8 dt_getDayOfWeek(u8 year, u8 month, u8 day) {
	u16 total_days = 0;
	u8 i;
	/* If year less than 100 */
	if (year < 100) {
		/* Account days in years */
		if (year > 0) {
			total_days += ((year - 1) / 4) + 1; // +1 because 0 year is leap
		}
		total_days += 365 * year;
		/* Account days in months */
		for (i=1; i<month; i++) {
			total_days += dt_getDaysInMonth(year, i);
		}
		/* Account days in current month */
		total_days += day + 4; // +4 because 01.01.2000 starts from Saturday (first DoW offset)
	}
	/* If year 100 and higher */
	else {
		/* Account days in years */
		if (year > 100) {
			total_days += (year - 101) / 4;
		}
		total_days += 365 * (year - 100);
		/* Account days in months */
		for (i=1; i<month; i++) {
			total_days += dt_getDaysInMonth(year, i);
		}
		/* Account days in current month */
		total_days += day + 3; // +3 because 01.01.2100 starts from Friday (first DoW offset)
	}
	return (total_days % 7) + 1;
}



