#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "tasks/slow_bus_master.h"
#include "drivers/DS3231_driver.h"
#include "drivers/SHT21_driver.h"
#include "misc/datetime.h"
#include "misc/task_messaging.h"

extern QueueHandle_t xUIQueue;

/* Timings */
#define tSBM_TASK_PERIOD pdMS_TO_TICKS(100) // 100mS task run period in "ticks"

#define tSBM_RHT_STARTUP 50 // 5S - Time to first measurement after power-up
#define tSBM_AIRP_STARTUP 50 // 5S - Time to first measurement after power-up
/*
#define tSBM_IAQ_STARTUP 3600 // 360S - Time to first measurement after power-up
#define tSBM_RHT_PERIOD 1500 // 150S - Temperature and humidity measurement period. (actual period is 2x)
#define tSBM_AIRP_PERIOD 1200 // 120S - Air pressure measurement period
#define tSBM_IAQ_PERIOD 1200 // 120S - TVOC and eCO2 measurement period
*/
// TODO: Test timings, remove
#define tSBM_IAQ_STARTUP 360 // 360S - Time to first measurement after power-up
#define tSBM_RHT_PERIOD 50 // 150S - Temperature and humidity measurement period. (actual period is 2x)
#define tSBM_AIRP_PERIOD 120 // 120S - Air pressure measurement period
#define tSBM_IAQ_PERIOD 120 // 120S - TVOC and eCO2 measurement period

#define tSBM_TEMP_MEAS 1 // 100mS - Temperature measure time
#define tSBM_HUM_MEASURE 1 // 100mS -  Humidity measure time

/* Steps */
#define sSBM_RHT_MTEMP 0
#define sSBM_RHT_RTEMP 1
#define sSBM_RHT_MHUM 2
#define sSBM_RHT_RHUM 3

/* Subtasks micro schedule */
#define flSBM_RTC_SET 0x01
#define flSBM_RTC_READ 0x02
#define flSBM_RHT_RUN 0x04
#define flSBM_AIRP_RUN 0x08
#define flSBM_IAQ_RUN 0x10

/* Struct definitions */
struct SBMSubTask {
	u8 step;
	u16 counter;
};

struct SBMContext {
	struct SBMSubTask rht;
	u8 flags;
};

void _smb_readTime();
void _sbm_runRHT(struct SBMContext *context);
void _sbm_updateCounters(struct SBMContext *context);

/* Slow I2C bus master task */
void sbm_taskSlowBusMaster(void *arg) {
	u8 sqw_state = 0;
	struct SBMContext context = {{sSBM_RHT_MTEMP, tSBM_RHT_STARTUP}, 0};
	/* Give some time for power up. */
	vTaskDelay(pdMS_TO_TICKS(100));
	rtc_ponInit();

	//xQueueSend(xQueueUIEvent, (void *) &ui_message, 0);
	//xQueueReceive(xQueueSysEvent, &(sys_message), 0)
	/* Task main loop */
	while(1) {
		/* Check SQW pin. Date and time readout from RTC IC is synced with 1Hz SQW pulses. */
		if ((sqw_state == 0) && mSQW_IN) {
			sqw_state = 1;
			/* Set read run flag */
			context.flags |= flSBM_RTC_READ;
		} else if (mSQW_IN == 0) {
			sqw_state = 0;
		}

		/* Update subtask counters and set run flags if required. */
		_sbm_updateCounters(&context);

		/* Check flags and run scheduled subtasks. */
		if ((context.flags & flSBM_RTC_READ) != 0) {
			/* Read time from RTC */
			_smb_readTime();
			context.flags &= ~flSBM_RTC_READ;
		}
		if ((context.flags & flSBM_RHT_RUN) != 0) {
			/* Run RHT sub task */
			_sbm_runRHT(&context);
			context.flags &= ~flSBM_RHT_RUN;
		}

		/* Sleep 100mS */
		vTaskDelay(tSBM_TASK_PERIOD);
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

/* Set time subtask */
void _sbm_setTime() {

}

/* Read temperature/humidity subtask */
void _sbm_runRHT(struct SBMContext *context) {
	struct StandardQueueMessage message;
	float temp;
	u8 hum;

	switch (context->rht.step) {
		case sSBM_RHT_MTEMP:
			/* Send temperature measure command */
			sht_measureTemp();
			/* Set measure timeout and next step */
			context->rht.counter = tSBM_TEMP_MEAS;
			context->rht.step = sSBM_RHT_RTEMP;
			break;

		case sSBM_RHT_RTEMP:
			/* Read temperature value */
			temp = sht_readTemp();
			/* Send message(s) with updated temperature value. */
			message.type = mtINT_TEMP;
			message.sender = msSL_BUS_MASTER;
			decomposeTemp(temp, message.payload);
			//message.payload[0] = (unsigned char)temp; // Decimal part
			//message.payload[1] = (unsigned char)((temp - message.payload[0]) * 10); // Fraction part
			/* Send message */
			xQueueSend(xUIQueue, (void *) &message, 0);
			/* Set timeout and next step */
			context->rht.counter = tSBM_RHT_PERIOD;
			context->rht.step = sSBM_RHT_MHUM;
			break;

		case sSBM_RHT_MHUM:
			/* Send humidity measure command */
			sht_measureHumidity();
			/* Set measure timeout and next step */
			context->rht.counter = tSBM_HUM_MEASURE;
			context->rht.step = sSBM_RHT_RHUM;
			break;

		case sSBM_RHT_RHUM:
			/* Read humidity value */
			hum = sht_readHumidity();
			/* Send message(s) with updated humidity value. */
			message.type = mtINT_HUM;
			message.sender = msSL_BUS_MASTER;
			message.payload[0] = hum;
			/* Send message */
			xQueueSend(xUIQueue, (void *) &message, 0);
			/* Set timeout and next step */
			context->rht.counter = tSBM_RHT_PERIOD;
			context->rht.step = sSBM_RHT_MTEMP;
			break;
	}
}

/* Read air pressure subtask */
void _sbm_runAIRP() {

}

/* Read air quality/eCO2 subtask */
void _sbm_runiAQ() {

}

/* Count time and set run flags */
void _sbm_updateCounters(struct SBMContext *context) {
	if (context->rht.counter > 0) {
		context->rht.counter--;
		if (context->rht.counter == 0) {
			context->flags |= flSBM_RHT_RUN;
		}
	}
}




