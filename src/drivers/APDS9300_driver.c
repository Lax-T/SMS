#include <math.h>
#include "drivers/APDS9300_driver.h"
#include "drivers/aux_i2c.h"

/* I2C addressing */
#define APDS_SLA_ADR 0x29
#define APDS_CTRL_REG 0x80
#define APDS_PON_CMD 0x03
#define APDS_CH0_REG 0x8C
#define APDS_CH1_REG 0x8E


/* Power on initialization */
void apds_ponInit() {
	auxi2c_writeByte(APDS_SLA_ADR, APDS_CTRL_REG, APDS_PON_CMD);
}

/* Ambient light value */
u8 apds_readAmbientLight() {
	u16 val = 0;
	float log_val;
	u8 ch0_data[2];
	//u8 ch1_data[2]; // TODO: At the moment not sure about final calculation algorithm.
	/* Read Ch0 and Ch1 RAW values from IC */
	auxi2c_readBlock(APDS_SLA_ADR, APDS_CH0_REG, ch0_data, 2);
	//auxi2c_readBlock(APDS_SLA_ADR, APDS_CH1_REG, ch1_data, 2);
	/* Calculate light level */
	val = (val | ch0_data[1]) << 8;
	val |= ch0_data[0];
	log_val = (float)((log10((double)val)) * 54.944); // log10(65536) * 54.944 = `255
	if (log_val >= 255) {
		return 255;
	}
	else {
		return (u8)log_val;
	}
}
