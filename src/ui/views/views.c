#include "ui/templates/ui_templates.h"
#include "ui/views/views.h"
#include "ui/views/views_control.h"
#include "ui/views/generic_handlers.h"
#include "ui/views/control_methods.h"
#include "ui/views/menus.h"


/* VIEW METHODS */
/* Home view handler */
u8 _vw_homeView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	switch (event_id) {
		case veOPT_BTN:
			vcm_enterView(vMENU, midMAIN_MENU, view_context, ui_context);
			break;
		default:
			break;
	}
	return 0;
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
	switch (event_id) {
		case veBACK_BTN:
			vcm_returnToPrevView(view_context, ui_context);
			break;
		case veLEFT_BTN:
			vgh_listMenuUp(view_context);
			break;
		case veRIGHT_BTN:
			vgh_listMenuDown(view_context);
			break;
		case veVIEW_ENTER:
			view_context->a_reg = 0;
			view_context->b_reg = 0;
			break;
		default:
			break;
	}
	return 0;
}
/* Menu view meta info */
const struct ViewMeta vw_MenuViewMeta = {
		tplLIST_MENU,
		vNONE,
		vmARR_SIZE_6,
		_vw_menuView,
		0
};

/* Default view handler */
u8 _vw_defaultView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
	return 0;
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
		&vw_DefaultViewMeta, &vw_HomeViewMeta, &vw_MenuViewMeta
};

/* Provides access to views meta objects */
struct ViewMeta *vw_getViewMeta(u8 view_id) {
	return _vw_ViewsMetaIndex[view_id];
}

