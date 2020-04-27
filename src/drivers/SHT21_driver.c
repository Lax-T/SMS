#include "globals.h"
#include "drivers/SHT21_driver.h"

/* I2C addressing */
#define SHT_SLA_ADR 0x40
#define SHT_MEATEMP_CMD 0xF3
#define SHT_MEAHUM_CMD 0xF5

/* Limits */
#define SHT_MIN_RH 0
#define SHT_MAX_RH 99
#define SHT_MIN_TEMP -40.0
#define SHT_MAX_TEMP 125.0

/* Start temperature measurement */
void sht_measureTemp() {
	sli2c_sendCmd(SHT_SLA_ADR, SHT_MEATEMP_CMD);
}

/* Start humidity measurement */
void sht_measureHumidity() {
	sli2c_sendCmd(SHT_SLA_ADR, SHT_MEAHUM_CMD);
}

/* Read temperature value */
float sht_readTemp() {
	unsigned int raw_value = 0;
	float calc_value;
	u8 data[2];
	/* Read RAW temperature value (2 bytes) from current address */
	sli2c_readBlockCA(SHT_SLA_ADR, data, 2);
	/* Result conversion */
	raw_value = (raw_value | data[0]) << 8;
	raw_value = raw_value | (data[1] & 0xFC);
	calc_value = -46.85 + ((float)raw_value)/372.956977;
	/* Handle out of range conditions. */
	if (calc_value < SHT_MIN_TEMP) {
		return SHT_MIN_TEMP;
	} else if (calc_value > SHT_MAX_TEMP) {
		return SHT_MAX_TEMP;
	} else {
		return calc_value;
	}
}

/* Read humidity value */
unsigned char sht_readHumidity() {
	unsigned int raw_value = 0;
	float calc_value;
	u8 data[2];
	/* Read RAW humidity value (2 bytes) from current address */
	sli2c_readBlockCA(SHT_SLA_ADR, data, 2);
	/* Result conversion */
	raw_value = (raw_value | data[0]) << 8;
	raw_value = raw_value | (data[1] & 0xF0);
	calc_value = ((float)raw_value) / 524.288 - 6.0;
	/* Handle out of range conditions. */
	if (calc_value < SHT_MIN_RH) {
		return SHT_MIN_RH;
	} else if (calc_value > SHT_MAX_RH) {
		return SHT_MAX_RH;
	} else {
		return (unsigned char)calc_value;
	}
}
