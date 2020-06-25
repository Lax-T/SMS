#include "ui/templates/ui_templates.h"
#include "ui/views/views.h"
#include "ui/views/views_control.h"
#include "ui/views/generic_handlers.h"
#include "ui/views/control_methods.h"
#include "ui/views/menus.h"
#include "ui/ui_api.h"
#include "misc/datetime.h"


/* VIEW METHODS */
/* Home view handler */
u8 _vw_homeView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	switch (event_id) {
		case veOPT_BTN:
			vcm_enterView(vMENU, midMAIN_MENU, view_context, ui_context);
			break;
		default:
			return 0;
	}
	return 1;
}
/* Home view meta info */
const struct ViewMeta vw_HomeViewMeta = {
		tplHOME,
		vNONE,
		vmARR_SIZE_0,
		_vw_homeView,
		0
};

/* Menu view handler */
u8 _vw_menuView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	u16 act;
	switch (event_id) {
		/*case veBACK_BTN:
			vcm_returnToPrevView(view_context, ui_context);
			break;*/
		case veLEFT_BTN:
			vgh_listMenuUp(view_context);
			break;
		case veRIGHT_BTN:
			vgh_listMenuDown(view_context);
			break;
		case veOK_BTN:
			if (vgh_listMenuGetAction(view_context) == mGO_SUB_MENU) {
				vgh_listMenuEnter(view_context);
			}
			else if (vgh_listMenuGetAction(view_context) > 0) {
				act = vgh_listMenuGetAction(view_context);
				vcm_enterView((u8)(act >> 8), (u8)(act & 0x00FF), view_context, ui_context);
			}
			break;
		case veBACK_BTN:
			if (view_context->b_reg > 0) {
				vgh_listMenuReturn(view_context);
			}
			else {
				vcm_returnToPrevView(view_context, ui_context);
			}
			break;
		case veVIEW_ENTER:
			view_context->a_reg = 0;
			view_context->b_reg = 0;
			break;
		default:
			return 0;
	}
	return 1;
}
/* Menu view meta info */
const struct ViewMeta vw_MenuViewMeta = {
		tplLIST_MENU,
		vDEFAULT,
		vmARR_SIZE_6,
		_vw_menuView,
		0
};

/* Date/Time set view handler */
u8 _vw_dateTimeSetView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	u8 temp;
	struct DateTime date_time;
	switch (event_id) {
		case veLEFT_BTN:
			vgh_decParam(view_context->a_reg, view_context);
			break;
		case veRIGHT_BTN:
			vgh_incParam(view_context->a_reg, view_context);
			break;
		case veOK_BTN:
			if (view_context->a_reg == 1) {
				/* When Year and Month entered, update day limit */
				temp = dt_getDaysInMonth(vgh_getParam(0, view_context), vgh_getParam(1, view_context) + 1);
				vgh_setParamLimiter(temp - 1, 2, view_context);
				/* Check if current day value is within range */
				if (vgh_getParam(2, view_context) >= temp) {
					vgh_setParam(temp - 1, 2, view_context);
				}
				view_context->a_reg++;
			}
			else if (view_context->a_reg == 4) {
				/* Set new DateTime value */
				date_time.year = vgh_getParam(0, view_context);
				date_time.month = vgh_getParam(1, view_context) + 1;
				date_time.day = vgh_getParam(2, view_context) + 1;
				date_time.hour = vgh_getParam(3, view_context);
				date_time.minute = vgh_getParam(4, view_context);
				date_time.second = 0;
				date_time.dow = dt_getDayOfWeek(date_time.year, date_time.month, date_time.day);
				uiapi_setSystemDateTime(&date_time);
				/* Return to the menu */
				vcm_returnToPrevView(view_context, ui_context);
			}
			else {
				view_context->a_reg++;
			}
			break;
		case veVIEW_ENTER:
			/* Load current Date/Time values */
			vgh_setParamAndLimiter(ui_context->current_dt.year, 199, 0, view_context);
			vgh_setParamAndLimiter(ui_context->current_dt.month, 11, 1, view_context); // 11 because 0 is included
			vgh_setParamAndLimiter(ui_context->current_dt.day, 30, 2, view_context);
			vgh_setParamAndLimiter(ui_context->current_dt.hour, 23, 3, view_context);
			vgh_setParamAndLimiter(ui_context->current_dt.minute, 59, 4, view_context);
			view_context->a_reg = 0; // Currently edited value
			break;
		default:
			return 0;
	}
	return 1;
}
/* Date/Time set view meta info */
const struct ViewMeta vw_dateTimeSetViewMeta = {
		tplDATETIME_SET,
		vDEFAULT,
		vmARR_SIZE_10,
		_vw_dateTimeSetView,
		0
};

/* Default view handler */
u8 _vw_defaultView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	switch (event_id) {
		case veBACK_BTN:
			vcm_returnToPrevView(view_context, ui_context);
			break;
		default:
			return 0;
	}
	return 1;
}
/* Default view meta info */
const struct ViewMeta vw_DefaultViewMeta = {
		tplNONE,
		vNONE,
		vmARR_SIZE_0,
		_vw_defaultView,
		0
};


/* VIEWS INDEX AND ACCESS */
/* Views index */
const struct ViewMeta *_vw_ViewsMetaIndex[] = {
		&vw_DefaultViewMeta, &vw_HomeViewMeta, &vw_MenuViewMeta, &vw_dateTimeSetViewMeta
};

/* Provides access to views meta objects */
struct ViewMeta *vw_getViewMeta(u8 view_id) {
	return _vw_ViewsMetaIndex[view_id];
}

