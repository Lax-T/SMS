#include "drivers/iAQcore_driver.h"

/* I2C addressing */
#define IAQ_SLA_ADR 0x5A

/* Read air quality data */
void iaq_readAQDAta(struct AQData *aq_data) {
	u8 buff[9];

	/* Read RAW value from IC */
	sli2c_readBlockCA(IAQ_SLA_ADR, buff, 9, TRUE);
	/* Calculate CO2 */
	aq_data->co2 = (buff[0] * 256) + buff[1];
	/* Calculate TVOC */
	aq_data->tvoc = (buff[7] * 256) + buff[8];
}
