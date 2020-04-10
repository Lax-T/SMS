#include "tasks/system.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"

/* Main system task */
void sys_taskSystem(void *arg) {
	unsigned char x = 0;

	while(1) {

		if (x) {
			mSLED_GREEN_OFF;
			x = 0;
		} else {
			mSLED_GREEN_ON;
			x = 1;
		}

		// Sleep
		vTaskDelay(1);
	}
}
