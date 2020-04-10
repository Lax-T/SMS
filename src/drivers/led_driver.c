#include <drivers/led_driver.h>
#include "macros.h"
#include "main.h"

static unsigned short gs_data[48] = {
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911,
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911, //16
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911, //24
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911,
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911,
		1911, 1911, 1911, 1911, 1911, 1911, 1911, 1911
};

static unsigned short gs_comm[48] = {
		0x9600, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0x0000, 0x5FFF, 0xFE49,
		//0x0000, 0x4000, 0x0000,
		0x0, 0x0, 0x0, 0x0, 0x0,
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};


void ldr_sendBit(unsigned char bit) {
	if (bit) {
		mLDR_DATA_HI;
	} else {
		mLDR_DATA_LO;
	}
	mLDR_CLK_HI;
	mLDR_CLK_LO;
}

void ldr_sendByte(unsigned char data) {
	unsigned char i;

	for (i=0;i<8;i++) {
		if (MASK_BIT(data, 0x80)) {
			mLDR_DATA_HI;
		}
		else {
			mLDR_DATA_LO;
		}
		mLDR_CLK_HI;
		mLDR_CLK_LO;
		data = data << 1;
	}
}

void ldr_sendShort(unsigned short data) {
	unsigned char i;

	for (i=0;i<16;i++) {
		if (MASK_BIT(data, 0x8000)) {
			mLDR_DATA_HI;
		}
		else {
			mLDR_DATA_LO;
		}
		mLDR_CLK_HI;
		mLDR_CLK_LO;
		data = data << 1;
	}
}

void ldr_latch() {
	mLDR_LAT_HI;
	mLDR_LAT_LO;
}

void ldr_testRun() {
	unsigned char i;

	ldr_sendBit(1);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_comm[i]);
	}
	ldr_sendBit(1);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_comm[i]);
	}
	ldr_latch();

	ldr_sendBit(1);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_comm[i]);
	}
	ldr_sendBit(1);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_comm[i]);
	}
	ldr_latch();

	ldr_sendBit(0);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_data[i]);
	}
	ldr_sendBit(0);
	for (i=0;i<48;i++) {
		ldr_sendShort(gs_data[i]);
	}
	ldr_latch();

}
