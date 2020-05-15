#include "ui/glib.h"
#include "ui/icons.h"
#include "ui/fonts.h"
#include "ui/templates/ui_templates.h"
#include "ui/templates/tpl_components.h"


/* HOME template (main screen) */
void _tpl_home(struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
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
	if ((ui_ctx->in_temp) < 0) {
		gl_setCursor(0, 51);
		gl_displayIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 19);
	gl_printString("in", ARIAL_10PTB);
	gl_setCursor(17, 32);
	gl_printFString("%|02sc", &(ui_ctx->in_temp), DIGITAL_44PX);
	gl_setCursor(75, 73);
	gl_displayIcon(ICO_DOT_3x3);
	gl_setCursor(82, 57);
	gl_printFString("%uc", &(ui_ctx->in_temp_fract), DIGITAL_19PX);
	gl_setCursor(85, 22);
	gl_printFString("%uc", &(ui_ctx->in_rh), DIGITAL_25PX);
	gl_setCursor(97, 61);
	gl_displayIcon(ICO_DEGREE_C15);
	gl_setCursor(119, 37);
	gl_printString("%", ARIAL_10PTB);

	/* Remote RHT */
	if ((ui_ctx->rm1_temp) < 0) {
		gl_setCursor(0, 115);
		gl_displayIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 83);
	gl_printString("out", ARIAL_10PTB);
	gl_setCursor(17, 96);
	gl_printFString("%|02sc", &(ui_ctx->rm1_temp), DIGITAL_44PX);
	gl_setCursor(75, 137);
	gl_displayIcon(ICO_DOT_3x3);
	gl_setCursor(82, 121);
	gl_printFString("%uc", &(ui_ctx->rm1_temp_fract), DIGITAL_19PX);
	gl_setCursor(85, 86);
	gl_printFString("%uc", &(ui_ctx->rm1_rh), DIGITAL_25PX);
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
	gl_printFString("%04us", &(ui_ctx->in_eco2), DIGITAL_19PX);
	gl_setCursor(101, 160);
	gl_printString("ppm", ARIAL_10PTB);

	gl_setCursor(0, 184);
	gl_printString("TVOC", ARIAL_10PTB);
	gl_setCursor(51, 175);
	gl_printFString("%03us", &(ui_ctx->in_tvoc), DIGITAL_19PX);
	gl_setCursor(101, 184);
	gl_printString("ppb", ARIAL_10PTB);

	gl_setCursor(0, 208);
	gl_printString("AIRP", ARIAL_10PTB);
	gl_setCursor(51, 199);
	gl_printFString("%03us", &(ui_ctx->pressure), DIGITAL_19PX);
	gl_setCursor(101, 208);
	gl_printString("mm", ARIAL_10PTB);

	/* Bottom status bar */
	gl_setCursor(0, 226);
	gl_printFString("%02uc", &(ui_ctx->current_dt.day), ARIAL_12PTB);
	gl_printFString(".%02uc", &(ui_ctx->current_dt.month), ARIAL_12PTB);
	gl_printFString(".2%03uc", &(ui_ctx->current_dt.year), ARIAL_12PTB);
	gl_setCursor(94, 226);
	tplc_printDOWShort(ui_ctx->current_dt.dow, ARIAL_12PTB);

	/* Refresh */
	gl_refreshLCD();
}

/* Template renderer index */
void (*_tpl_rendererIndex[])(struct ViewContext *view_ctx, struct UIContext *ui_ctx) = {
		_tpl_home};

/* Main invocation method - render template by ID */
void tpl_renderTemplate(u8 template_id, struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	(*_tpl_rendererIndex[(template_id - 1)])(view_ctx, ui_ctx);
}



