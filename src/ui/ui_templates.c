#include "tasks/ui_control.h"
#include "ui/ui_templates.h"
#include "ui/glib.h"
#include "ui/icons.h"
#include "ui/fonts.h"


static char txt_mon_short[] = "Mon";
static char txt_tue_short[] = "Tue";
static char txt_wed_short[] = "Wed";
static char txt_thu_short[] = "Thu";
static char txt_fri_short[] = "Fri";
static char txt_sat_short[] = "Sat";
static char txt_sun_short[] = "Sun";
static char *txt_set_dow_short[] = {txt_mon_short, txt_tue_short, txt_wed_short, txt_thu_short, txt_fri_short, txt_sat_short, txt_sun_short};

void _tpl_printDOWShort(u8 dow) {
	gl_printString(txt_set_dow_short[dow-1], ARIAL_12PTB);
}

void tpl_home(struct UIContext ui_context, struct ViewContext view_context) {
	/* Clear buffer */
	gl_clearBuffer();

	/* Draw lines */
	gl_setCursor(0, 16);
	gl_drawHLine(2, 128);
	gl_setCursor(0, 80);
	gl_drawHLine(2, 128);
	gl_setCursor(0, 144);
	gl_drawHLine(2, 128);
	gl_setCursor(0, 222);
	gl_drawHLine(2, 128);

	/* Top status bar */
	gl_setCursor(0, 0);
	gl_printString(" ", ARIAL_12PTB);

	/* Internal RHT */
	if (ui_context.in_temp < 0) {
		gl_setCursor(0, 51);
		gl_displayIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 19);
	gl_printString("in", ARIAL_10PTB);
	gl_setCursor(17, 32);
	gl_printFString("%|02sc", &ui_context.in_temp, DIGITAL_44PX);
	gl_setCursor(75, 73);
	gl_displayIcon(ICO_DOT_3x3);
	gl_setCursor(82, 57);
	gl_printFString("%uc", &ui_context.in_temp_fract, DIGITAL_19PX);
	gl_setCursor(85, 22);
	gl_printFString("%uc", &ui_context.in_rh, DIGITAL_25PX);
	gl_setCursor(97, 61);
	gl_displayIcon(ICO_DEGREE_C15);
	gl_setCursor(119, 37);
	gl_printString("%", ARIAL_10PTB);

	/* Remote RHT */
	if (ui_context.rm1_temp < 0) {
		gl_setCursor(0, 115);
		gl_displayIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 83);
	gl_printString("out", ARIAL_10PTB);
	gl_setCursor(17, 96);
	gl_printFString("%|02sc", &ui_context.rm1_temp, DIGITAL_44PX);
	gl_setCursor(75, 137);
	gl_displayIcon(ICO_DOT_3x3);
	gl_setCursor(82, 121);
	gl_printFString("%uc", &ui_context.rm1_temp_fract, DIGITAL_19PX);
	gl_setCursor(85, 86);
	gl_printFString("%uc", &ui_context.rm1_rh, DIGITAL_25PX);
	gl_setCursor(97, 125);
	gl_displayIcon(ICO_DEGREE_C15);
	gl_setCursor(119, 101);
	gl_printString("%", ARIAL_10PTB);

	/* Pressure, TVOC, eCO2 */
	gl_setCursor(0, 160);
	gl_printString("CO", ARIAL_10PTB);
	gl_setCursor(19, 163);
	gl_printString("2", ARIAL_10PTB);
	gl_setCursor(36, 151);
	gl_printFString("%04us", &ui_context.in_eco2, DIGITAL_19PX);
	gl_setCursor(101, 160);
	gl_printString("ppm", ARIAL_10PTB);

	gl_setCursor(0, 184);
	gl_printString("TVOC", ARIAL_10PTB);
	gl_setCursor(51, 175);
	gl_printFString("%03us", &ui_context.in_tvoc, DIGITAL_19PX);
	gl_setCursor(101, 184);
	gl_printString("ppb", ARIAL_10PTB);

	gl_setCursor(0, 208);
	gl_printString("AIRP", ARIAL_10PTB);
	gl_setCursor(51, 199);
	gl_printFString("%03us", &ui_context.pressure, DIGITAL_19PX);
	gl_setCursor(101, 208);
	gl_printString("mm", ARIAL_10PTB);

	/* Bottom status bar */
	gl_setCursor(0, 226);
	gl_printFString("%02uc", &ui_context.day, ARIAL_12PTB);
	gl_printFString(".%02uc", &ui_context.month, ARIAL_12PTB);
	gl_printFString(".2%03uc", &ui_context.year, ARIAL_12PTB);
	gl_setCursor(94, 226);
	_tpl_printDOWShort(ui_context.dow);

	/* Refresh */
	gl_refreshLCD();
}
