#include "ui/views/views.h"
#include "ui/views/views_control.h"
#include "ui/views/control_methods.h"
#include "ui/templates/ui_templates.h"

#define HOME_VIEW_ID vHOME
#define HOME_VIEW_MOD 0

/* Definitions */
void _vc_syncWithUIContext(struct UIContext *ui_ctx);
void _vc_refresh(struct UIContext *ui_ctx);

/* Initialize views context */
struct ViewContext gs_vc_view_ctx = {
		.stack.stack_pointer = 0, .stack.arr_offset = 0,
		.system.recursion_cnt = 0, .system.error_flags = 0
};

/* MAIN FUNCTIONS */
/* Discard stack and force set home view */
void vc_setHomeView(struct UIContext *ui_ctx) {
	vcm_setView(HOME_VIEW_ID, HOME_VIEW_MOD, &gs_vc_view_ctx, ui_ctx);
	vcm_resetViewsStack(&gs_vc_view_ctx);
	_vc_resetRecursionCnt();
	_vc_refresh(ui_ctx);
}

/* Handle UI event (call view specific handler) and refresh GLCD (render template) */
void vc_handleEvet(u8 event_id, struct UIContext *ui_ctx) {
	vcm_executeEvent(event_id, &gs_vc_view_ctx, ui_ctx);
	_vc_resetRecursionCnt();
	_vc_refresh(ui_ctx);
}

/* Show notification for out of order event
 * TODO: implement notifications */
void vc_showNotification(u8 notification_id, struct UIContext *ui_ctx) {
	_vc_resetRecursionCnt();
	_vc_refresh(ui_ctx);
}

/* OTHER FUNCTIONS */
/* Function to sync certain values between UI and Views context */
void _vc_syncWithUIContext(struct UIContext *ui_ctx) {
	ui_ctx->view_id = gs_vc_view_ctx.view_id;
	ui_ctx->view_modifier = gs_vc_view_ctx.view_modifier;
}

/* Refresh UI (if conditions are met, render View template)
 * TODO: when actually needed, implement deferred rendering */
void _vc_refresh(struct UIContext *ui_ctx) {
	struct ViewMeta *view_meta = vw_getViewMeta(gs_vc_view_ctx.view_id);
	tpl_renderTemplate(view_meta->template_id, &gs_vc_view_ctx, ui_ctx);
}

/* Reset system recursion counter */
void _vc_resetRecursionCnt() {
	gs_vc_view_ctx.system.recursion_cnt = 0;
}

