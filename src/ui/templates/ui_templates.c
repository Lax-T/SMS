#include "ui/glib.h"
#include "ui/icons.h"
#include "ui/fonts.h"
#include "ui/templates/ui_templates.h"
#include "ui/templates/tpl_components.h"
#include "ui/views/menus.h"


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
		gl_drawIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 19);
	gl_printString("in", ARIAL_10PTB);
	gl_setCursor(17, 32);
	gl_printFString("%|02sc", &(ui_ctx->in_temp), DIGITAL_44PX);
	gl_setCursor(75, 73);
	gl_drawIcon(ICO_DOT_3x3);
	gl_setCursor(82, 57);
	gl_printFString("%uc", &(ui_ctx->in_temp_fract), DIGITAL_19PX);
	gl_setCursor(85, 22);
	gl_printFString("%uc", &(ui_ctx->in_rh), DIGITAL_25PX);
	gl_setCursor(97, 61);
	gl_drawIcon(ICO_DEGREE_C15);
	gl_setCursor(119, 37);
	gl_printString("%", ARIAL_10PTB);

	/* Remote RHT */
	if ((ui_ctx->rm1_temp) < 0) {
		gl_setCursor(0, 115);
		gl_drawIcon(ICO_MINUS_12x6);
	}
	gl_setCursor(0, 83);
	gl_printString("out", ARIAL_10PTB);
	gl_setCursor(17, 96);
	gl_printFString("%|02sc", &(ui_ctx->rm1_temp), DIGITAL_44PX);
	gl_setCursor(75, 137);
	gl_drawIcon(ICO_DOT_3x3);
	gl_setCursor(82, 121);
	gl_printFString("%uc", &(ui_ctx->rm1_temp_fract), DIGITAL_19PX);
	gl_setCursor(85, 86);
	gl_printFString("%uc", &(ui_ctx->rm1_rh), DIGITAL_25PX);
	gl_setCursor(97, 125);
	gl_drawIcon(ICO_DEGREE_C15);
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

/* LIST MENU template */
void _tpl_listMenu(struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	u8 i, x, y;
	struct MenuList *menu_list;
	/* Clear buffer */
	gl_clearBuffer();
	/* Get current menu list */
	menu_list = m_getNestedMenuList(view_ctx->view_modifier, view_ctx->b_reg, view_ctx->data_array);
	/* Draw lines */
	gl_setCursor(0, 16);
	gl_drawHLine(2, 128);
	/* Title */
	gl_setCursor(0, 0);
	gl_printString(menu_list->title, ARIAL_12PTB);
	/* Items */
	x = 9;
	y = 22;
	for (i=0; i < menu_list->len; i++) {
		gl_setCursor(x, y);
		gl_printString(menu_list->items[i]->title, ARIAL_12PTB);
		y += 20;
	}

	/* Cursor */
	x = 0;
	y = 21 + (20 * view_ctx->a_reg);
	gl_setCursor(x, y);
	gl_drawIcon(ICO_ARR_RIGHT_7x14);

	/* Refresh */
	gl_refreshLCD();
}


const u8 _set_datetime_x_lookup[] = {16, 61, 88, 40, 67};
const u8 _set_datetime_y_lookup[] = {72, 72, 72, 158, 158};
/* DATE/TIME set template */
void _tpl_setDateTime(struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	u8 i, temp, x, y;
	/* Clear buffer */
	gl_clearBuffer();
	/* Draw lines */
	gl_setCursor(0, 32);
	gl_drawHLine(2, 128);
	/* Title */
	gl_setCursor(0, 0);
	gl_printString("Налаштування", ARIAL_12PTB);
	gl_setCursor(0, 16);
	gl_printString("дати і часу", ARIAL_12PTB);
	/* Display all edited parameters parameters */
	gl_setCursor(18, 74);
	temp = vgh_getParam(0, view_ctx);
	gl_printFString("2%03uc", &(temp), ARIAL_12PTB);
	gl_shiftCursotRight(3);
	gl_printString(":", ARIAL_12PTB);
	gl_shiftCursotRight(2);
	temp = vgh_getParam(1, view_ctx) + 1;
	gl_printFString("%02uc", &(temp), ARIAL_12PTB);
	gl_shiftCursotRight(3);
	gl_printString(":", ARIAL_12PTB);
	gl_shiftCursotRight(2);
	temp = vgh_getParam(2, view_ctx) + 1;
	gl_printFString("%02uc", &(temp), ARIAL_12PTB);

	/* Display day of week according to entered date */
	gl_setCursor(26, 116);
	temp = dt_getDayOfWeek(vgh_getParam(0, view_ctx), vgh_getParam(1, view_ctx) + 1, vgh_getParam(2, view_ctx) + 1);
	tplc_printDOWFull(temp, ARIAL_12PTB);

	/* Highlight currently edited parameter */
	gl_setCursor(42, 160);
	temp = vgh_getParam(3, view_ctx);
	gl_printFString("%02uc", &(temp), ARIAL_12PTB);
	gl_shiftCursotRight(3);
	gl_printString(":", ARIAL_12PTB);
	gl_shiftCursotRight(2);
	temp = vgh_getParam(4, view_ctx);
	gl_printFString("%02uc", &(temp), ARIAL_12PTB);

	/* Highlight edited parameter */
	x = _set_datetime_x_lookup[view_ctx->a_reg];
	y = _set_datetime_y_lookup[view_ctx->a_reg];
	gl_setCursor(x, y);
	if (view_ctx->a_reg == 0) {
		gl_drawInvertedRect(39, 16);
		gl_setCursor(x + 11, y - 10);
		gl_drawIcon(ICO_ARR_UP_16x8);
		gl_setCursor(x + 11, y + 18);
		gl_drawIcon(ICO_ARR_DOWN_16x8);
	}
	else {
		gl_drawInvertedRect(21, 16);
		gl_setCursor(x + 2, y - 10);
		gl_drawIcon(ICO_ARR_UP_16x8);
		gl_setCursor(x + 2, y + 18);
		gl_drawIcon(ICO_ARR_DOWN_16x8);
	}

	/* Refresh */
	gl_refreshLCD();
}

/* TEMPLATES INDEX AND ACCESS */
/* Template renderer index */
void (*_tpl_rendererIndex[])(struct ViewContext *view_ctx, struct UIContext *ui_ctx) = {
		_tpl_home, _tpl_listMenu, _tpl_setDateTime
};

/* Main invocation method - render template by ID */
void tpl_renderTemplate(u8 template_id, struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	(*_tpl_rendererIndex[(template_id - 1)])(view_ctx, ui_ctx);
}




