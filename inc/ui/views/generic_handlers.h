#include "ui/views/views_control.h"

void vgh_listMenuUp(struct ViewContext *view_context);
void vgh_listMenuDown(struct ViewContext *view_context);
void vgh_listMenuEnter(struct ViewContext *view_context);
void vgh_listMenuReturn(struct ViewContext *view_context);
u16 vgh_listMenuGetAction(struct ViewContext *view_context);

void vgh_setMultParams(u8 params[], u8 len, struct ViewContext *view_context);
void vgh_setParam(u8 val, u8 position, struct ViewContext *view_context);
void vgh_setMultParamLimiters(u8 limiters[], u8 len, struct ViewContext *view_context);
void vgh_setParamLimiter(u8 val, u8 position, struct ViewContext *view_context);
void vgh_setParamAndLimiter(u8 val, u8 limiter, u8 position, struct ViewContext *view_context);
void vgh_incParam(u8 position, struct ViewContext *view_context);
void vgh_decParam(u8 position, struct ViewContext *view_context);
u8 vgh_getParam(u8 position, struct ViewContext *view_context);

