#include "tasks/ui_control.h"
#include "ui/ui_templates.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "ui/glib.h"
#include "ui/led_control.h"
#include "drivers/UC1608X_driver.h"
#include "misc/task_messaging.h"

extern QueueHandle_t xUIQueue;

void _uic_checkQueue(struct UIContext *ui_context);

/* UI control task */
void uic_taskUIControl(void *arg) {
	struct UIContext ui_context;
	struct ViewContext view_context;

	/* Power on initialize */
	/* GLCD initialization */
	uc_initController();
	gl_clearBuffer();
	gl_refreshLCD();
	uc_lcdOn();
	/* Led controllers initialization */
	lc_init();
	lc_setBacklightGroupValue(10);

	lc_setAmbientBrt(2);
	lc_setAmbientGroupValue(240, 120, 2);

	lc_setSecondBrt(15);
	lc_setSecondValue(0);

	lc_setTimeBrt(40);
	lc_setTimeValue(0, 0);

	lc_refresh();

	ui_context.in_temp = 0;
	ui_context.in_temp_fract = 0;
	ui_context.in_rh = 0;
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
		_uic_checkQueue(&ui_context);

		/* Temporary code to update LEDs */
		lc_setSecondValue(ui_context.current_dt.second);
		lc_setTimeValue(ui_context.current_dt.hour, ui_context.current_dt.minute);
		lc_refresh();
		/* And GLCD */
		tpl_home(ui_context, view_context);

		// Sleep
		vTaskDelay(20);
	}
}

/* Check and handle messages from UI queue. */
void _uic_checkQueue(struct UIContext *ui_context) {
	struct StandardQueueMessage message;
	struct DateTime *date_time = &(ui_context->current_dt);
	/* Read messages from queue */
	while(xQueueReceive(xUIQueue, &(message), 0)) {
		switch (message.type) {
		/* Handle message with new DateTime */
		case mtDATE_TIME:
			/* Deserialize to UI context */
			deSerializeDateTime(message.payload, date_time);
			break;

		case mtINT_TEMP:
			ui_context->in_temp = message.payload[0];
			ui_context->in_temp_fract = message.payload[1];
			break;

		case mtINT_HUM:
			ui_context->in_rh = message.payload[0];
			break;
		}
	}
}




