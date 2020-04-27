#include <math.h>
#include "globals.h"
#include "misc/task_messaging.h"

void decomposeTemp(float temp, u8 buffer[]) {
	/* Since standard message is defined as unsigned char, type cast is performed.
	Upon message receive it will be cast back to signed. */
	/* Decimal part */
	char dec = (char)(fabs(temp));
	if (temp < 0) {
		dec = 0 - dec;
	}
	buffer[0] = dec;
	/* Fraction part */
	temp = fabs(temp);
	buffer[1] = (unsigned char)((temp - (u16)temp) * 10);
}
