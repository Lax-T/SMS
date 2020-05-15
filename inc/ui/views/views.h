#include "globals.h"
#include "tasks/ui_control.h"
#include "ui/views/views_control.h"

/* Array sizes SET */
#define vmARR_SIZE_0 0
#define vmARR_SIZE_2 2
#define vmARR_SIZE_4 4
#define vmARR_SIZE_6 6
#define vmARR_SIZE_8 8
#define vmARR_SIZE_10 10
#define vmARR_SIZE_12 12
#define vmARR_SIZE_14 14
#define vmARR_SIZE_16 16
#define vmARR_SIZE_18 18
#define vmARR_SIZE_20 20
#define vmARR_SIZE_22 22
#define vmARR_SIZE_24 24
#define vmARR_SIZE_26 26
#define vmARR_SIZE_28 28
#define vmARR_SIZE_30 30
#define vmARR_SIZE_32 32

/* Flags */
#define flDEFER_TPL_RENDER 0x01 // Disable auto template render for view

typedef u8 (*ViewHandler)(u8 event_id, struct ViewContext *view_context, struct UIContext *ui_context);

/* Struct definitions */
#ifndef VIEW_META_STRUCT_DEF_
#define VIEW_META_STRUCT_DEF_
/* Holds view meta info */
struct ViewMeta {
	u8 template_id;
	u8 parent_view;
	u8 arr_size;
	ViewHandler method;
	u8 flags;
};
#endif

/* Functions */
struct ViewMeta *vw_getViewMeta(u8 view_id);

