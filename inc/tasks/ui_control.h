#include "globals.h"
#include "misc/datetime.h"

#ifndef UI_CONTROL_STRUCT_DEF_
#define UI_CONTROL_STRUCT_DEF_
/* Holds common UI context.
 * Not intended to be modified by Event handlers and view render functions. */
struct UIContext {
	struct DateTime current_dt;
	u8 view_id;
	u8 view_modifier;
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
#endif

void uic_taskUIControl(void *arg);
