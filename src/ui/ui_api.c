#include "ui/ui_api.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "misc/task_messaging.h"

extern QueueHandle_t xSBMQueue;

/* API function to update system time (RTC) */
void uiapi_setSystemDateTime(struct DateTime *date_time) {
	struct StandardQueueMessage message;
	/* Set message properties and serialize DateTime */
	message.type = mtDATE_TIME;
	message.sender = msUI;
	serializeDateTime(date_time, message.payload);
	/* Send message */
	xQueueSend(xSBMQueue, (void *) &message, 0);
}
