#include "stm32f2xx.h"
#include <drivers/TLC5955_driver.h>

#define DATA 0
#define COMMAND 1

#define mLDR_CLK_HI GPIO_SetBits(GPIOB, GPIO_Pin_13);
#define mLDR_CLK_LO GPIO_ResetBits(GPIOB, GPIO_Pin_13);

#define mLDR_DATA_HI GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define mLDR_DATA_LO GPIO_ResetBits(GPIOB, GPIO_Pin_15);

#define mLDR_LAT_HI GPIO_SetBits(GPIOB, GPIO_Pin_12);
#define mLDR_LAT_LO GPIO_ResetBits(GPIOB, GPIO_Pin_12);

void sendBit(unsigned char bit);
void sendShort(unsigned short data);
void latch();
void sendDataSet(u16 *buffer, u16 offset );


/* Update configuration of multiple chained ICs in one transaction */
void tlc_updateConfigALL(struct TLCConfig config) {
	u8 i, g, d;
	u16 buffer[48];
	u16 dot_ptr, buffer_ptr;
	u8 func_reg = config.func_reg & 0x1F;
	u8 brightness = config.brightness & 0x7F;
	u8 max_current = config.max_current & 0x07;

	/* Set command byte */
	buffer[0] = 0x9600;
	/* Set common config values */
	buffer[24] = 0x0000 | (func_reg >> 2);
	buffer[25] = 0x0000 | (func_reg << 14) | (brightness << 7) | brightness;
	buffer[26] = 0x0000 | (brightness << 9) | (max_current << 6) | (max_current << 3) | max_current;

	/* Repeat operation twice, otherwise driver IC will ignore max current setting. */
	for (d=0; d < 2; d++) {
		/* For each IC...  */
		for (i=0; i < CHAINED_DEVICES_N; i++) {
			buffer_ptr = 27;
			/* Set dot correction data. */
			for (g=0; g < 3; g++) { // 3, because dot correction set (336 bits wide) is split into 3 sectors 112 bits (16 * 7) each.
				dot_ptr = (16 * g) + (48 * i);
				// Bits 335-320(g = 0); 223-208(g = 1); 111-96(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 9);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 2);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 5);
				// Bits 319-304(g = 0); 207-192(g = 1); 95-80(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 11);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 4);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 3);
				// Bits 303-288(g = 0); 191-176(g = 1); 79-64(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 13);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 6);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 1);
				// Bits 287-272(g = 0); 175-160(g = 1); 63-48(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 15);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 8);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 1);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 6);
				// Bits 271-256(g = 0); 159-144(g = 1); 47-32(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 10);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 3);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 4);
				// Bits 255-240(g = 0); 143-128(g = 1); 31-16(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 12);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 5);
				buffer[buffer_ptr++] |= (config.dot_corr[dot_ptr] >> 2);
				// Bits 239-224(g = 0); 127-112(g = 1); 15-0(g = 2);
				buffer[buffer_ptr] = 0x0000 | (config.dot_corr[dot_ptr++] << 14);
				buffer[buffer_ptr] |= (config.dot_corr[dot_ptr++] << 7);
				buffer[buffer_ptr++] |= config.dot_corr[dot_ptr];
			}
			/* Send prepared data set */
			sendBit(COMMAND);
			sendDataSet(buffer, 0);
		}
		/* When data to all devices is sent, latch! */
		latch();
	}
}

/* Update outs (PWM) data in multiple chained ICs in one transaction */
void tlc_updateGSAll(u16 *buffer) {
	u8 i;
	/* Send 768+1 bit (48 * 16) data set to each device and then latch. */
	for (i=0; i < CHAINED_DEVICES_N; i++) {
		sendBit(DATA);
		sendDataSet(buffer, i * 48);
	}
	latch();
}


/******** LOW LEVEL OPERATIONS ***********/
/* Send latch select bit. If 0, than next 768 bits are channel data.
 * If 0 - configuration values) */
void sendBit(unsigned char bit) {
	if (bit) {
		mLDR_DATA_HI;
	} else {
		mLDR_DATA_LO;
	}
	mLDR_CLK_HI;
	mLDR_CLK_LO;
}


void sendShort(unsigned short data) {
	unsigned char i;

	for (i=0;i<16;i++) {
		if (data & 0x8000) {
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

void latch() {
	mLDR_LAT_HI;
	mLDR_LAT_LO;
}

void sendDataSet(u16 *buffer, u16 offset ) {
	u16 i;

	for (i=0; i < 48; i++) {
		sendShort(buffer[i + offset]);
	}
}
