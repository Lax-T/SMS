#include "drivers/DS3231_driver.h"
#include "drivers/slow_i2c.h"

#define DS_SLA_ADR 0x68
#define DS_CONF_REG_ADR 0x0E
#define DS_CONF_REG_VAL 0x00

unsigned char _rtc_BCDToDec(u8 bcd);
unsigned char _rtc_DecToBCD(u8 dec);

/* At each power on, checks RTC IC configuration register */
void rtc_ponInit() {
	u8 conf_reg = sli2c_readByte(DS_SLA_ADR, DS_CONF_REG_ADR);
	/* Check if conf register is 0x00 - all default, plus 1Hz SQW signal generation */
	if (conf_reg != DS_CONF_REG_VAL) {
		sli2c_writeByte(DS_SLA_ADR, DS_CONF_REG_ADR, DS_CONF_REG_VAL);
	}
}

/* Read current date and time from RTC IC */
void rtc_readDateTime(struct DateTime *date_time) {
	u8 buffer[7];
	/* Read RAW values from RTC IC */
	sli2c_readBlock(DS_SLA_ADR, 0, buffer, 7);
	/* Parse RAW values */
	date_time->second = _rtc_BCDToDec(buffer[0]); // Seconds
	date_time->minute = _rtc_BCDToDec(buffer[1]); // Minutes
	date_time->hour = _rtc_BCDToDec(buffer[2] & 0x3F); // Hour, blank 12/24H bit
	date_time->dow = buffer[3] & 0x07; // Day of week
	date_time->day = _rtc_BCDToDec(buffer[4]); // Day
	date_time->month = _rtc_BCDToDec(buffer[5] & 0x7F); // Month, blank century bit
	date_time->year = _rtc_BCDToDec(buffer[6]); // Year
	/* If century bit is set, add 100 to year register */
	if ((buffer[5] & 0x80) != 0) {
		date_time->year += 100;
	}
}

/* Set date and time to RTC IC */
void rtc_setDateTime(struct DateTime *date_time) {
	u8 buffer[7];
	/* Encode DateTime values to IC BCD format,
	blank unused bits to avoid IC hang in case of error in higher level code. */
	buffer[0] = _rtc_DecToBCD(date_time->second) & 0x7F;
	buffer[1] = _rtc_DecToBCD(date_time->minute) & 0x7F;
	buffer[2] = _rtc_DecToBCD(date_time->hour) & 0x3F;
	buffer[3] = _rtc_DecToBCD(date_time->dow) & 0x07;
	buffer[4] = _rtc_DecToBCD(date_time->day) & 0x3F;
	buffer[5] = _rtc_DecToBCD(date_time->month) & 0x1F;
	/* If year > 100, set century bit and subtract 100 from year */
	if (date_time->year >= 100) {
		buffer[5] |= 0x80; // Set century bit
		buffer[6] = _rtc_DecToBCD(date_time->year - 100);
	}
	else {
		buffer[6] = _rtc_DecToBCD(date_time->year);
	}
	/* Write values to IC */
	sli2c_writeBlock(DS_SLA_ADR, 0, buffer, 7);
}

/* Misc functions */
/* Converts BCD number from RTC IC to normal char */
unsigned char _rtc_BCDToDec(u8 bcd) {
	u8 v_10;
	v_10 = (bcd >> 4) & 0x0F;
	return (v_10 * 10) + (bcd & 0x0F);
}

/* Convert char to BCD format */
unsigned char _rtc_DecToBCD(u8 dec) {
	u8 v_10;
	v_10 = (dec / 10) << 4;
	return (dec % 10) | v_10;
}
