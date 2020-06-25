#include "ui/glib.h"
#include "ui/icons.h"
#include "ui/fonts.h"
#include "ui/templates/tpl_components.h"


/* Print short day of week */
/*
const char txt_mon_short[] = "Mon";
const char txt_tue_short[] = "Tue";
const char txt_wed_short[] = "Wed";
const char txt_thu_short[] = "Thu";
const char txt_fri_short[] = "Fri";
const char txt_sat_short[] = "Sat";
const char txt_sun_short[] = "Sun";
const char *txt_set_dow_short[] = {txt_mon_short, txt_tue_short, txt_wed_short, txt_thu_short, txt_fri_short, txt_sat_short, txt_sun_short};
*/
const char* const txt_set_dow_short_2[] = {
		 "Пон", "Вів", "Сер", "Чет", "Пят", "Суб", "Нед"
};

void tplc_printDOWShort(u8 dow, u8 font) {
	/* If out of range - do nothing */
	if ((dow < 1) || (dow > 8)) {
		return;
	}
	gl_printString(txt_set_dow_short_2[dow-1], font);
}

/* Print days of week */
const char* const txt_set_dow_full[] = {
		 "Понеділок", "Вівторок", "Середа", "Четвер", "П'ятниця", "Субота", "Неділя"
};

void tplc_printDOWFull(u8 dow, u8 font) {
	/* If out of range - do nothing */
	if ((dow < 1) || (dow > 8)) {
		return;
	}
	gl_printString(txt_set_dow_full[dow-1], font);
}
