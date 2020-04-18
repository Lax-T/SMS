#include <globals.h>

/* Holds common UI context.
 * Not intended to be modified by Event handlers and view render functions. */
struct UIContext {
	u8 view_id;
	u8 sub_view_id;
	s8 in_temp;
	u8 in_temp_fract;
	u8 in_rh;
	u16 pressure;
	u16 in_tvoc;
	u16 in_eco2;
	s8 rm1_temp;
	u8 rm1_temp_fract;
	u8 rm1_rh;
};


/* View specific context shared between Event handler and view render handler function.
 * Can be modified. */
struct ViewContext {

};



void sys_taskUIControl(void *arg);
