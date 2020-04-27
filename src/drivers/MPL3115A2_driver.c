#include "globals.h"
#include "drivers/MPL3115A2_driver.h"

/* I2C addressing */
#define MPL_SLA_ADR 0x60
#define MPL_CTR_REG_ADR 0x26
#define MPL_DATA_REG_ADR 0x01
#define MPL_MEASURE_CMD 0x32 // Single measure, 64x oversample

/* Measure pressure command. */
void mpl_measurePressure() {
	sli2c_writeByte(MPL_SLA_ADR, MPL_CTR_REG_ADR, MPL_MEASURE_CMD);
}

/* Read pressure value */
u16 mpl_readPressure() {
	u8 buff[3];
	unsigned long value = 0;
	/* Read RAW value from IC */
	sli2c_readBlock(MPL_SLA_ADR, MPL_DATA_REG_ADR, buff, 3);
	/* Calculate pressure pressure mmHg. */
	value = value | buff[0];
	value = value << 8;
	value = value | buff[1];
	value = value << 8;
	value = value | buff[2];
	value = value >> 6;
	return (unsigned short)(value / 133.322);
}

