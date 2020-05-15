#include "ui/views/views_control.h"
#include "tasks/ui_control.h"

/* Templates */
#define tplNONE 255 // Dummy, non executable template
#define tplHOME 1

void tpl_renderTemplate(u8 template_id, struct ViewContext *view_ctx, struct UIContext *ui_ctx);
