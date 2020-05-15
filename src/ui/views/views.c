#include <ui/templates/ui_templates.h>
#include "ui/views/views.h"
#include "ui/views/views_control.h"


/* VIEW METHODS */
/* Home view */
u8 _vw_homeView(u8 event_id,  struct ViewContext *view_context, struct UIContext *ui_context) {
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

/* Default view */
u8 _vw_defaultView(u8 event_id,  struct ViewContext *iew_context, struct UIContext *ui_context) {
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
		&vw_DefaultViewMeta, &vw_HomeViewMeta
};

/* Provides access to views meta objects */
struct ViewMeta *vw_getViewMeta(u8 view_id) {
	return _vw_ViewsMetaIndex[view_id];
}

