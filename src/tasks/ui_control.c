#include "tasks/ui_control.h"
#include "ui/views/views_control.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "ui/glib.h"
#include "ui/led_control.h"
#include "drivers/UC1608X_driver.h"
#include "drivers/touch_key_driver.h"
#include "drivers/lcd_backlight.h"
#include "misc/task_messaging.h"

extern QueueHandle_t xUIQueue;

void _uic_checkQueue(struct UIContext *ui_context);

/* UI control task */
void uic_taskUIControl(void *arg) {
	u8 devider = 0;
	u8 key;
	struct UIContext ui_context;
	struct ViewContext view_context;

	/* Power on initialize */
	/* GLCD initialization */
	uc_initController();
	gl_clearBuffer();
	gl_refreshLCD();
	uc_lcdOn();
	lcdbl_setBacklight(0x12);
	/* Led controllers initialization */
	lc_init();
	lc_setBacklightGroupValue(10);

	lc_setAmbientBrt(2);
	lc_setAmbientGroupValue(240, 120, 2);

	lc_setSecondBrt(8);
	lc_setSecondValue(0);

	lc_setTimeBrt(6);
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

	vc_setHomeView(&ui_context);
	//tpl_home(ui_context, view_context);

	while(1) {
		_uic_checkQueue(&ui_context);
		key = tk_scanKeys();
		if (key != 0) { // TODO: test code
			vc_handleEvet(key, &ui_context);
			ui_context.rm1_temp = key;
		}


		devider++;
		if (devider >= 5) {
			devider = 0;
			/* Temporary code to update LEDs */
			lc_setSecondValue(ui_context.current_dt.second);
			lc_setTimeValue(ui_context.current_dt.hour, ui_context.current_dt.minute);
			lc_refresh();
			/* And GLCD */
			vc_handleEvet(veDATA_UPDATED, &ui_context);
			//tpl_home(ui_context, view_context);
		}
		// Sleep
		vTaskDelay(5);
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

		case mtPRESSURE:
			ui_context->pressure = 0x0000 | ((0x0000 | message.payload[0]) << 8) | message.payload[1];
			break;

		case mtAIR_QUALITY:
			ui_context->in_eco2 = 0x0000 | ((0x0000 | message.payload[0]) << 8) | message.payload[1];
			ui_context->in_tvoc = 0x0000 | ((0x0000 | message.payload[2]) << 8) | message.payload[3];
			break;

		case mtAMB_LIGHT_LEVEL: // TODO: test code
			ui_context->rm1_rh = (u8)(message.payload[0] / 2.6);
			break;
		}
	}
}




