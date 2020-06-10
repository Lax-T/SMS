#include "globals.h"
#include "stm32f2xx.h"
#include "drivers/lcd_backlight.h"

/* Set LCD backlight value */
void lcdbl_setBacklight(u8 bl_value) {
	DAC_SetChannel1Data(DAC_Align_8b_R, ((u16)bl_value));
}
