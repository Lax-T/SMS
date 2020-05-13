#include "globals.h"
#include "ui/views/views_control.h"
#include "tasks/ui_control.h"


void vcm_resetViewsStack(struct ViewContext *view_ctx);
void vcm_setView(u8 view_id, u8 view_modifier, struct ViewContext *view_ctx, struct UIContext *ui_ctx);
void vcm_enterView(u8 view_id, u8 view_modifier, struct ViewContext *view_ctx, struct UIContext *ui_ctx);
void vcm_returnToPrevView(struct ViewContext *view_ctx, struct UIContext *ui_ctx);
u8 vcm_executeEvent(u8 event_code, struct ViewContext *view_ctx, struct UIContext *ui_ctx);
