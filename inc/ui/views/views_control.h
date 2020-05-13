#include "globals.h"
#include "tasks/ui_control.h"

/* View events to handle */
#define veBACK_BTN 1
#define veLEFT_BTN 2
#define veOK_BTN 3
#define veRIGHT_BTN 4
#define veOPT_BTN 5
#define veVIEW_ENTER 10
#define veVIEW_EXIT 11
#define veVIEW_RETURN_TO 12
#define veDATA_READY 20
#define veDATA_UPDATED 21
#define veINTERRUPTED 22

/* Views */
#define vNONE 255 // Dummy, non executable view
#define vDEFAULT 0 // Default (system) view
#define vHOME 1

/* Flags */
#define fUI_RECURSION_ERR 0x01
#define fUI_STACK_OVERFL 0x02
#define fUI_ARR_STACK_OVERFL 0x04
#define fUI_ARR_STACK_DISPOS 0x08 // Array stack zero disposition error

/* MISC */
#define UI_STACK_SIZE 48
#define UI_ARR_STACK_SIZE 256
#define UI_VIEW_ARR_SIZE 32
#define UI_VIEW_ARGS_SIZE 2
#define UI_MAX_EVENT_RECURSION 6

/* Structures definitions */
#ifndef VIEW_STACK_STRUCT_DEF_
#define VIEW_STACK_STRUCT_DEF_
/* Holds views stack */
struct ViewsStack {
	/* stack_pointer: current value is used to values of current view!
	For the next view, this value is incremented. */
	u8 stack_pointer;
	u8 id_stack[UI_STACK_SIZE];
	u8 modifier_stack[UI_STACK_SIZE];
	u8 a_reg_stack[UI_STACK_SIZE];
	u8 b_reg_stack[UI_STACK_SIZE];
	u16 x_reg_stack[UI_STACK_SIZE];
	u16 y_reg_stack[UI_STACK_SIZE];
	u8 arr_sizes_stack[UI_STACK_SIZE];
	u16 arr_offset;
	u8 arr_stack[UI_ARR_STACK_SIZE];
};
#endif

#ifndef VIEW_SYSTEM_STRUCT_DEF_
#define VIEW_SYSTEM_STRUCT_DEF_
/* Holds views system data (aka protected data) */
struct ViewsSystem {
	u8 recursion_cnt;
	u8 error_flags;
};
#endif

#ifndef VIEW_CONTEXT_STRUCT_DEF_
#define VIEW_CONTEXT_STRUCT_DEF_
/* View specific context shared between Event handler and view render handler function. */
struct ViewContext {
	u8 view_id;
	u8 view_modifier;
	u8 a_reg;
	u8 b_reg;
	u16 x_reg;
	u16 y_reg;
	u8 data_array[UI_VIEW_ARR_SIZE];
	u8 args[UI_VIEW_ARGS_SIZE];
	u8 return_args[UI_VIEW_ARGS_SIZE];
	struct ViewsSystem system;
	struct ViewsStack stack;
};
#endif

/* Function definitions */
void vc_setHomeView(struct UIContext *ui_ctx);
void vc_handleEvet(u8 event_id, struct UIContext *ui_ctx);

