#include <tasks/ui_control.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* Main system task */
void sys_taskUIControl(void *arg) {

	while(1) {

		// Sleep
		vTaskDelay(10);
	}
}
