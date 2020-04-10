#include "stm32f2xx.h"
#include <ui/led_control.h>
#include <drivers/TLC5955_driver.h>

/* Defaults */
#define DEFAULT_DOT_CORR 0x60 // Aprox. 75%
#define DEFAULT_GLOBAL_BRT 0x60 // Aprox. 50%
#define DEFAULT_BRIGHTNESS 0x80 // Aprox. 50%


/* Flags */
#define fBAR_GR_UPDATED 0x01
#define fAMBI_GR_UPDATED 0x02
#define fKBL_GR_UPDATED 0x04
#define fSEC_GR_UPDATED 0x08
#define fTIME_GR_UPDATED 0x10
#define fDOT_CORR_UPDATED 0x20 // Indicates that dot correction was set and default is not needed
#define fSEC_VAL_CHANGED 0x40 // Indicates that second value (not brightness) changed

/* Macros */
/* Second LEDs anode groups */
#define mSLED_GROUP1_ON GPIO_ResetBits(GPIOE, GPIO_Pin_11);
#define mSLED_GROUP1_OFF GPIO_SetBits(GPIOE, GPIO_Pin_11);

#define mSLED_GROUP2_ON GPIO_ResetBits(GPIOB, GPIO_Pin_2);
#define mSLED_GROUP2_OFF GPIO_SetBits(GPIOB, GPIO_Pin_2);

#define mSLED_GROUP3_ON GPIO_ResetBits(GPIOE, GPIO_Pin_7);
#define mSLED_GROUP3_OFF GPIO_SetBits(GPIOE, GPIO_Pin_7);

#define mSLED_GROUP4_ON GPIO_ResetBits(GPIOB, GPIO_Pin_0);
#define mSLED_GROUP4_OFF GPIO_SetBits(GPIOB, GPIO_Pin_0);

#define mSLED_GROUP5_ON GPIO_ResetBits(GPIOB, GPIO_Pin_1);
#define mSLED_GROUP5_OFF GPIO_SetBits(GPIOB, GPIO_Pin_1);

#define mSLED_GROUP6_ON GPIO_ResetBits(GPIOE, GPIO_Pin_8);
#define mSLED_GROUP6_OFF GPIO_SetBits(GPIOE, GPIO_Pin_8);

#define mSLED_GROUP7_ON GPIO_ResetBits(GPIOE, GPIO_Pin_9);
#define mSLED_GROUP7_OFF GPIO_SetBits(GPIOE, GPIO_Pin_9);

#define mSLED_GROUP8_ON GPIO_ResetBits(GPIOE, GPIO_Pin_10);
#define mSLED_GROUP8_OFF GPIO_SetBits(GPIOE, GPIO_Pin_10);

/* STRUCT definitions */
struct BarGroup {
	u8 brightness;
	u8 led_values[27]; // 1R, 1G, 1B...9B
};

struct AmbiGroup {
	u8 brightness;
	u8 led_values[21]; // 1R, 1G, 1B...7B
};

struct KBBacklightGroup {
	u8 brightness;
	u8 led_values[5];
};

struct SecondsGroup {
	u8 brightness;
	u8 value;
};

struct TimeGroup {
	u8 brightness;
	u8 hour;
	u8 minute;
};

struct BarGroup gslc_bar = {DEFAULT_BRIGHTNESS};
struct AmbiGroup gslc_ambi = {DEFAULT_BRIGHTNESS};
struct KBBacklightGroup gslc_kb_backlight = {DEFAULT_BRIGHTNESS};
struct SecondsGroup gslc_seconds = {DEFAULT_BRIGHTNESS};
struct TimeGroup gslc_time = {DEFAULT_BRIGHTNESS};

struct TLCConfig gslc_tlc_config = {
		(0x00 | TLC_DISPRPT_ON | TLC_TIMRST_OFF | TLC_DATARFSH_OFF),
		DEFAULT_GLOBAL_BRT,
		TLC_MAXCURR_8
};

u16 glc_gs_buffer[48 * CHAINED_DEVICES_N] = {};
u8 glc_flags = 0;

void lc_offAllAnodeGroups();
void lc_resetBuffer();

/* SECONDS group

Seconds hardware matrix organization
A - anode, output controlled by MCU, C - cathode, driver IC output
   C1 C2 C3 C4 C5 C6 C7 C8
A1 1  2  3  4  5  6  7  8
A2 9  10 11 12 13 14 15 16
A3 17 18 19 20 21 22 23 24
A4 25 26 27 28 29 30 31 32
A5 33 34 35 36 37 38 39 40
A6 41 42 43 44 45 46 47 48
A7 49 50 51 52 53 54 55 56
A8 57 58 59 00
*/
/* Set second value to display */
void lc_setSecondValue(u8 second) {
	gslc_seconds.value = second;
	glc_flags = glc_flags | fSEC_GR_UPDATED | fSEC_VAL_CHANGED;
}

/* Set second group brightness */
void lc_setSecondBrt(u8 brt) {
	gslc_seconds.brightness = brt;
	glc_flags |= fSEC_GR_UPDATED;
}

/* Turn on specific seconds anode group based on seconds value. */
void lc_onAnodeGroup(struct SecondsGroup sec_grp) {
	u8 anode_group = 255;
	/* Check if seconds value is within range,
	 *  otherwise group number will be 255 and all outputs OFF by default */
	if (sec_grp.value <= 59) {
		/* Zero is exceptional case and requires 8th anode group */
		if (sec_grp.value == 0) {
			anode_group = 8;
		} else {
			anode_group = ((sec_grp.value - 1) / 8) + 1;
		}
	}
	switch (anode_group) {
	case 1:
		mSLED_GROUP1_ON;
		break;
	case 2:
		mSLED_GROUP2_ON;
		break;
	case 3:
		mSLED_GROUP3_ON;
		break;
	case 4:
		mSLED_GROUP4_ON;
		break;
	case 5:
		mSLED_GROUP5_ON;
		break;
	case 6:
		mSLED_GROUP6_ON;
		break;
	case 7:
		mSLED_GROUP7_ON;
		break;
	case 8:
		mSLED_GROUP8_ON;
		break;
	default:
		lc_offAllAnodeGroups();
	}
}

/* Turn off all seconds anode groups */
void lc_offAllAnodeGroups() {
	mSLED_GROUP1_OFF;
	mSLED_GROUP2_OFF;
	mSLED_GROUP3_OFF;
	mSLED_GROUP4_OFF;
	mSLED_GROUP5_OFF;
	mSLED_GROUP6_OFF;
	mSLED_GROUP7_OFF;
	mSLED_GROUP8_OFF;
}

/* Turn output on, depending on what second to display. Other outs OFF */
/* LUT for fast lookup */
static u16 lclut_sled_cath[] = {
		SLED_CGROUP_1, SLED_CGROUP_2, SLED_CGROUP_3, SLED_CGROUP_4,
		SLED_CGROUP_5, SLED_CGROUP_6, SLED_CGROUP_7, SLED_CGROUP_8};

void lc_updateSecondsBuffer(struct SecondsGroup sec_grp) {
	u8 i;
	u8 on_out = 255;
	/* Calculate LED brightness */
	u16 grayscale_val = sec_grp.brightness * 255;
	/* Check if seconds value is within range */
	if (sec_grp.value <= 59) {
		/* Determine what out should be on */
		/* Zero is exceptional case and requires 4th group*/
		if (sec_grp.value == 0) {
			on_out = 3; // -1 because we will be using LUT
		}
		else if ((sec_grp.value % 8) == 0 ) {
			/* If MOD 8 == 0, than this would be last, 8th group. */
			on_out = 7; // -1 because we will be using LUT
		} else {
			on_out = (sec_grp.value % 8) - 1;  // -1 because we will be using LUT
		}
	}
	/* Iterate all 8 channels, turn all off except the one needed */
	for (i=0; i < 8; i++) {
		/* Output (cathode group) that should be turned on - set to non zero value. */
		if (i == on_out) {
			glc_gs_buffer[lclut_sled_cath[i]] = grayscale_val;
		} else {
			glc_gs_buffer[lclut_sled_cath[i]] = 0;
		}
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* HOUR and MINUTES group */
/* Set time value to display */
void lc_setTimeValue (u8 hour, u8 minute) {
	gslc_time.hour = hour;
	gslc_time.minute = minute;
	glc_flags |= fTIME_GR_UPDATED;
}
/* Set time group brightness */
void lc_setTimeBrt (u8 brt) {
	gslc_time.brightness = brt;
	glc_flags |= fTIME_GR_UPDATED;
}

/* Hour "tens" segment [A to G] to buffer pointer LUT */
static u16 lclut_hour10_segm_ptr[] = {
		HOUR1_LED_A, HOUR1_LED_B, HOUR1_LED_C, HOUR1_LED_D, HOUR1_LED_E, HOUR1_LED_F, HOUR1_LED_G
};
/* Hour "ones" segment [A to G] to buffer pointer LUT */
static u16 lclut_hour1_segm_ptr[] = {
		HOUR2_LED_A, HOUR2_LED_B, HOUR2_LED_C, HOUR2_LED_D, HOUR2_LED_E, HOUR2_LED_F, HOUR2_LED_G
};
/* Minute "tens" segment [A to G] to buffer pointer LUT */
static u16 lclut_minute10_segm_ptr[] = {
		MINUTE1_LED_A, MINUTE1_LED_B, MINUTE1_LED_C, MINUTE1_LED_D,
		MINUTE1_LED_E, MINUTE1_LED_F, MINUTE1_LED_G,
};
/* Minute "ones" segment [A to G] to buffer pointer LUT */
static u16 lclut_minute1_segm_ptr[] = {
		MINUTE2_LED_A, MINUTE2_LED_B, MINUTE2_LED_C, MINUTE2_LED_D,
		MINUTE2_LED_E, MINUTE2_LED_F, MINUTE2_LED_G,
};
/* Number to turned on segment LUT. 0xABCDEFGx (A-MSB, G-LSB)*/
static u8 lclut_seg_pattern[] = {
		0xFC, 0X60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, // 0 - 9
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00  // 16th dash symbol
};

/* Update buffer according to time (hour and minute) value to be displayed. */
void lc_updateTimeBuffer(struct TimeGroup time_grp) {
	u8 i, hour10, hour1, minute10, minute1;
	/* Calculate LED brightness */
	u16 grayscale_val = time_grp.brightness * 255;
	/* Calculate time values */
	/* Check if hour value is within range,
	 then calculate 10/1 values and get segment patterns for each number */
	if (time_grp.hour <= 23) {
		hour10 = lclut_seg_pattern[(time_grp.hour / 10)];
		hour1 = lclut_seg_pattern[(time_grp.hour % 10)];
	} else {
		hour10 = lclut_seg_pattern[17]; // All segments off
		hour1 = lclut_seg_pattern[17]; // All segments off
	}
	/* Check if minute value is within range and calculate 10/1 values */
	if (time_grp.minute <= 59) {
		minute10 = lclut_seg_pattern[(time_grp.minute / 10)];
		minute1 = lclut_seg_pattern[(time_grp.minute % 10)];
	} else {
		minute10 = lclut_seg_pattern[17]; // All segments off
		minute1 = lclut_seg_pattern[17]; // All segments off
	}
	/* Iterate (virtually) segments from A to G and determine
	 if it should be ON for particular hour/minute number */
	for (i=0; i < 7; i++) { // because 7 segments
		/* Check if segment A, B... should be turned on. */
		if (hour10 & (0x80 >> i)) {
			/* Segment should be on - set GS value */
			glc_gs_buffer[lclut_hour10_segm_ptr[i]] = grayscale_val; // Get sgm pointer and set value
		} else {
			/* If no - set 0 */
			glc_gs_buffer[lclut_hour10_segm_ptr[i]] = 0;
		}

		if (hour1 & (0x80 >> i)) {
			/* Segment should be on - set GS value */
			glc_gs_buffer[lclut_hour1_segm_ptr[i]] = grayscale_val;
		} else {
			/* If no - set 0 */
			glc_gs_buffer[lclut_hour1_segm_ptr[i]] = 0;
		}

		if (minute10 & (0x80 >> i)) {
			/* Segment should be on - set GS value */
			glc_gs_buffer[lclut_minute10_segm_ptr[i]] = grayscale_val;
		} else {
			/* If no - set 0 */
			glc_gs_buffer[lclut_minute10_segm_ptr[i]] = 0;
		}

		if (minute1 & (0x80 >> i)) {
			/* Segment should be on - set GS value */
			glc_gs_buffer[lclut_minute1_segm_ptr[i]] = grayscale_val;
		} else {
			/* If no - set 0 */
			glc_gs_buffer[lclut_minute1_segm_ptr[i]] = 0;
		}
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* KEYS BACKLIGHT group */
/* Set backlight value to each channel individually */
void lc_setBacklightValues(u8 bl_values[5]) {
	u8 i;
	/* Copy values */
	for (i=0; i < 5; i++) {
		gslc_kb_backlight.led_values[i] = bl_values[i];
	}
	glc_flags |= fKBL_GR_UPDATED;
}

/* Set same value to all backlight channels. */
void lc_setBacklightGroupValue(u8 val) {
	u8 i;
	for (i=0; i < 5; i++) {
		gslc_kb_backlight.led_values[i] = val;
	}
	glc_flags |= fKBL_GR_UPDATED;
}

/* Set backlight group brightness */
void lc_setBacklightBrt(u8 brt) {
	gslc_kb_backlight.brightness = brt;
	glc_flags |= fKBL_GR_UPDATED;
}

/* Led n to buffer pointer LUT */
static u16 lclut_kbl_leds[] = {
	KBL_LED_1, KBL_LED_2, KBL_LED_3, KBL_LED_4, KBL_LED_5
};

/* Update ambient LEDs buffer according to values/brightness set. */
void lc_updateBacklightBuffer(struct KBBacklightGroup bl_group) {
	u16 buffer_ptr;
	u8 i;
	/* Iterate all LEDs, calculate and set new buffer values
	 based on LED val and group brightness. */
	for (i=0; i < 5; i++) {
		buffer_ptr = lclut_kbl_leds[i];
		glc_gs_buffer[buffer_ptr] = bl_group.led_values[i] * bl_group.brightness;
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* BAR group */
/* Set RGB values to each LED bar channel individually.
 Data (array) format: {1R, 1G, 1B.....9B} */
void lc_setBarValues(u8 bar_values[27]) {
	u8 i;
	/* Plain copy */
	for (i=0; i < 27; i++) {
		gslc_bar.led_values[i] = bar_values[i];
	}
	glc_flags |= fBAR_GR_UPDATED;
}

/* Set same RGB value to all bar LED channels. */
void lc_setBarGroupValue(u8 r_val, u8 g_val, u8 b_val) {
	u8 i;
	/* Set same R, G and B value for each LED */
	for (i=0; i < 27; i++) {
		gslc_bar.led_values[i++] = r_val;
		gslc_bar.led_values[i++] = g_val;
		gslc_bar.led_values[i] = b_val;
	}
	glc_flags |= fBAR_GR_UPDATED;
}

/* Set bar group brightness. */
void lc_setBarBrt(u8 brt) {
	gslc_bar.brightness = brt;
	glc_flags |= fBAR_GR_UPDATED;
}

/* BAR LEDs (LED number) to buffer pointer LUT */
static u16 lclut_bar_leds[] = {
		BAR_LED_1R, BAR_LED_1G, BAR_LED_1B, BAR_LED_2R, BAR_LED_2G, BAR_LED_2B,
		BAR_LED_3R, BAR_LED_3G, BAR_LED_3B, BAR_LED_4R, BAR_LED_4G, BAR_LED_4B,
		BAR_LED_5R, BAR_LED_5G, BAR_LED_5B, BAR_LED_6R, BAR_LED_6G, BAR_LED_6B,
		BAR_LED_7R, BAR_LED_7G, BAR_LED_7B, BAR_LED_8R, BAR_LED_8G, BAR_LED_8B,
		BAR_LED_9R, BAR_LED_9G, BAR_LED_9B
};

/* Calculate and update BAR LEDs buffer according to values/brightness set */
void lc_updateBarBuffer(struct BarGroup bar_group) {
	u16 buff_ptr;
	u8 i;
	/* Iterate and calculate value for each LED (channel) */
	for (i=0; i < 27; i++) {
		buff_ptr = lclut_bar_leds[i];
		glc_gs_buffer[buff_ptr] = bar_group.led_values[i] * bar_group.brightness;
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* AMBIENT group */
/* Set RGB values to each ambient channel individually.
 Data (array) format: {1R, 1G, 1B.....7B} */
void lc_setAmbientValues(u8 amb_values[21]) {
	u8 i;
	/* Plain copy */
	for (i=0; i < 21; i++) {
		gslc_ambi.led_values[i] = amb_values[i];
	}
	glc_flags |= fAMBI_GR_UPDATED;

}

/* Set same RGB value to all ambient LED channels. */
void lc_setAmbientGroupValue(u8 r_val, u8 g_val, u8 b_val) {
	u8 i;
	/* Set same R, G and B value for each LED */
	for (i=0; i < 21; i++) {
		gslc_ambi.led_values[i++] = r_val;
		gslc_ambi.led_values[i++] = g_val;
		gslc_ambi.led_values[i] = b_val;
	}
	glc_flags |= fAMBI_GR_UPDATED;
}

/* Set ambient group brightness. */
void lc_setAmbientBrt(u8 brt) {
	gslc_ambi.brightness = brt;
	glc_flags |= fAMBI_GR_UPDATED;
}

/* Ambient LEDs (LED number) to buffer pointer LUT */
static u16 lclut_ambient_leds[] = {
	AMBI_LED_1R, AMBI_LED_1G, AMBI_LED_1B, AMBI_LED_2R, AMBI_LED_2G, AMBI_LED_2B,
	AMBI_LED_3R, AMBI_LED_3G, AMBI_LED_3B, AMBI_LED_4R, AMBI_LED_4G, AMBI_LED_4B,
	AMBI_LED_5R, AMBI_LED_5G, AMBI_LED_5B, AMBI_LED_6R, AMBI_LED_6G, AMBI_LED_6B,
	AMBI_LED_7R, AMBI_LED_7G, AMBI_LED_7B
};

/* Calculate and update ambient LEDs buffer according to values/brightness set */
void lc_updateAmbientBuffer(struct AmbiGroup amb_group) {
	u16 buff_ptr;
	u8 i;
	/* Iterate and calculate value for each LED (channel) */
	for (i=0; i < 21; i++) {
		buff_ptr = lclut_ambient_leds[i];
		glc_gs_buffer[buff_ptr] = amb_group.led_values[i] * amb_group.brightness;
	}
}
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

/* GLOBAL functions */
/* Initialization */
void lc_init() {
	/* Clear buffer */
	lc_resetBuffer();
	/* Turn off all anodes */
	lc_offAllAnodeGroups();
	/* Send clear buffer to ICs */
	tlc_updateGSAll(glc_gs_buffer);
	/* Check if dot correction was set before init, if not - set default value. */
	if ((glc_flags & fDOT_CORR_UPDATED) == 0) {
		u16 i;
		for (i=0; i < (48 * CHAINED_DEVICES_N); i++) {
			gslc_tlc_config.dot_corr[i] = DEFAULT_DOT_CORR;
		}
	}
	/* Update ICs configuration */
	lc_updateDriversConfig();
	/* Clear all flags */
	glc_flags = 0;
}

/* Update/recalculate buffer and send to ICs */
void lc_refresh() {
	if (glc_flags & fSEC_GR_UPDATED) {
		lc_updateSecondsBuffer(gslc_seconds);
		glc_flags &= ~fSEC_GR_UPDATED;
	}
	if (glc_flags & fTIME_GR_UPDATED) {
		lc_updateTimeBuffer(gslc_time);
		glc_flags &= ~fTIME_GR_UPDATED;
	}
	if (glc_flags & fKBL_GR_UPDATED) {
		lc_updateBacklightBuffer(gslc_kb_backlight);
		glc_flags &= ~fKBL_GR_UPDATED;
	}
	if (glc_flags & fBAR_GR_UPDATED) {
		lc_updateBarBuffer(gslc_bar);
		glc_flags &= ~fBAR_GR_UPDATED;
	}
	if (glc_flags & fAMBI_GR_UPDATED) {
		lc_updateAmbientBuffer(gslc_ambi);
		glc_flags &= ~fAMBI_GR_UPDATED;
	}

	/* Before sending data to driver ICs, check if seconds value changed
	 and second ANODE group needs to changed also. This is to avoid ghosting or flickering*/
	if (glc_flags & fSEC_VAL_CHANGED) {
		lc_offAllAnodeGroups();
		tlc_updateGSAll(glc_gs_buffer);
		lc_onAnodeGroup(gslc_seconds);
		glc_flags &= ~fSEC_VAL_CHANGED;
	}
	else {
		tlc_updateGSAll(glc_gs_buffer);
	}
}

/* Set new dot correction values */
void lc_setDotCorrectionAll(u8 corection_set[]) {
	u16 i;
	for (i=0; i < (48 * CHAINED_DEVICES_N); i++) {
		gslc_tlc_config.dot_corr[i] = corection_set[i];
	}
	glc_flags |= fDOT_CORR_UPDATED;
}

/* Send updated configuration ICs */
void lc_updateDriversConfig() {
	tlc_updateConfigALL(gslc_tlc_config);
}

/* Set all channels OFF (clear buffer) */
void lc_resetBuffer() {
	u16 i;

	for (i=0; i < (48 * CHAINED_DEVICES_N); i++) {
		glc_gs_buffer[i] = 0;
	}
}

/* Configure GS timer and enable clock output */
void _enableGrayscaleClock() {

}


