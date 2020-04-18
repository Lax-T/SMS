#include <tasks/ui_control.h>
#include "ui/ui_templates.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* Main system task */
void sys_taskUIControl(void *arg) {
	struct UIContext ui_context;
	struct ViewContext view_context;

	ui_context.in_temp = 24;
	ui_context.in_temp_fract = 5;
	ui_context.in_rh = 84;
	ui_context.in_eco2 = 1024;
	ui_context.in_tvoc = 223;
	ui_context.pressure = 756;
	ui_context.rm1_rh = 22;
	ui_context.rm1_temp = -8;
	ui_context.rm1_temp_fract = 3;
	ui_context.day = 18;
	ui_context.month = 4;
	ui_context.year = 20;
	ui_context.dow = 6;

	tpl_home(ui_context, view_context);

	while(1) {
		// Sleep
		vTaskDelay(100);
	}
}
