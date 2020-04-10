#include <globals.h>

/* Holds common UI context.
 * Not intended to be modified by Event handlers and view render functions. */
struct UIContext {
	u8 view_id;
	u8 sub_view_id;
};


/* View specific context shared between Event handler and view render handler function.
 * Can be modified. */
struct ViewContext {
	u8 var_1;
	u8 var_2;
	u16 var_a;
	u16 var_b;
};



void sys_taskUIControl(void *arg);
