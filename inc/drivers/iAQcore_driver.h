#include "globals.h"

#ifndef AQ_DATA_
#define AQ_DATA_

/* Air quality values object */
struct AQData {
	u16 co2;
	u16 tvoc;
};

#endif


void iaq_readAQDAta(struct AQData *aq_data);
