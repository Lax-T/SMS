#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "tasks/slow_bus_master.h"
#include "drivers/DS3231_driver.h"
#include "misc/datetime.h"
#include "misc/task_messaging.h"

extern QueueHandle_t xUIQueue;

/* Subtasks micro scheduler */
#define SBM_RTC_SET_FLAG 0x01
#define SBM_RTC_READ_FLAG 0x02
#define SBM_RHT_RUN_FLAG 0x04
#define SBM_AIRP_RUN_FLAG 0x08
#define SBM_IAQ_RUN_FLAG 0x10

struct SBMuSchedule {
	u16 rht_counter;
	u16 iaq_counter;
	u16 airp_counter;
};

void _smb_readTime();

/* Slow I2C bus master task */
void sbm_taskSlowBusMaster(void *arg) {
	u8 sqw_state = 0;
	u8 run_flags = 0;
	/* Give some time for powering up. */
	vTaskDelay(10);
	rtc_ponInit();

	//xQueueSend(xQueueUIEvent, (void *) &ui_message, 0);
	//xQueueReceive(xQueueSysEvent, &(sys_message), 0)
	/* Task main loop */
	while(1) {
		/*if (mSQW_IN) { // TODO: test code, remove
			mSLED_RED_ON;
		} else {
			mSLED_RED_OFF;
		}*/

		/* Check SQW pin. Date and time readout from RTC IC is synced with 1Hz SQW pulses. */
		if ((sqw_state == 0) && mSQW_IN) {
			sqw_state = 1;
			/* Set read run flag */
			run_flags |= SBM_RTC_READ_FLAG;
		} else if (mSQW_IN == 0) {
			sqw_state = 0;
		}

		/* Check and run */
		if (run_flags != 0) {
			/* Read time from RTC */
			mSLED_RED_ON;
			_smb_readTime();
			run_flags &= ~SBM_RTC_READ_FLAG;
			mSLED_RED_OFF;
		}

		/* Sleep 100mS */
		vTaskDelay(10);
	}
}

/* Read time subtask */
void _smb_readTime() {
	struct DateTime date_time;
	struct StandardQueueMessage message;
	/* Read from RTC IC */
	rtc_readDateTime(&date_time);
	/* Set message properties and serialize DateTime */
	message.type = mtDATE_TIME;
	message.sender = msSL_BUS_MASTER;
	serializeDateTime(&date_time, message.payload);
	/* Send message */
	xQueueSend(xUIQueue, (void *) &message, 0);
}




