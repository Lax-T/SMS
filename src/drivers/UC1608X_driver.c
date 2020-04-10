#include <drivers/UC1608X_driver.h>
#include "delays.h"
#include "macros.h"
#include <globals.h>

//#define CM_MR_TC 0x24 // 128 lines, no temp co
#define CM_MR_TC 0x25 // 128 lines, -0.05 temp co
#define CM_POWER_CTRL 0x2F // Internal VLCD, loading 60 - 90
#define CM_LCD_MAPPING 0xC1 // MSB data first
#define CM_LCD_BIAS 0xE9 // Bias ratio 11.3
#define CM_SET_GAIN_RATIO 0x81 // Init gain set (double byte cm)
#define CM_GAIN_POT_RATIO 0x94 // Gain 2, Pot - mid range
#define CM_START_LINE 0x40 // Start line - 0

#define CM_LCD_ON 0xAF
#define CM_ALL_POINTS_ON 0xA5
#define CM_INVERT 0xA7

void resetController();
void spiCSLow();
void spiCSHi();
void spiTxByte(unsigned char data);
void sendCommand(unsigned char data);
void initCommandSequnce();
void uc_initController();
void uc_setWriteAddress(unsigned char page, unsigned char column);
void uc_writeSingle(unsigned char data);
void uc_writeArray(u8 *arr, u8 length);
void sendData(unsigned char data);


void uc_initController() {
	resetController();
	initCommandSequnce();
}

void uc_lcdOn() {
	spiCSHi();
	sendCommand(CM_LCD_ON);
	//sendCommand(CM_INVERT);
	spiCSLow();
}

void uc_setWriteAddress(unsigned char page, unsigned char column) {
	spiCSHi();
	sendCommand(page | 0xB0); // Set page
	sendCommand(column & 0x0F); // Set LSB column address
	sendCommand((column >> 4) | 0x10); // Set MSB column address
	spiCSLow();
}

void uc_writeSingle(unsigned char data) {
	spiCSHi();
	sendData(data);
	spiCSLow();
}

void uc_writeArray(u8 *arr, u8 length) {
	u8 i = 0;
	spiCSHi();
	SPI_SEND_DATA;
	/* Check if length does not exceed  */
	if (length > GLCD_COLUMNS) {
		length = GLCD_COLUMNS;
	}
	/* Write data */
	for (i=0; i < length; i++) {
		spiTxByte(arr[i]);
	}
	spiCSLow();
}

/* Write entire graphic memory from buffer 2D array. */
void uc_writeFullBuffer(u8 buffer[][GLCD_COLUMNS]) {
	u8 page, col;
	for (page=0; page < GLCD_PAGES; page++) {
		uc_setWriteAddress(page, 0);
		spiCSHi();
		for (col=0; col < GLCD_COLUMNS; col++) {
			sendData(buffer[page][col]);
		}
		spiCSLow();
	}
}

void initCommandSequnce() {
	spiCSHi();
	sendCommand(CM_MR_TC); // 5
	sendCommand(CM_POWER_CTRL);
	sendCommand(CM_LCD_MAPPING); // 16
	sendCommand(CM_LCD_BIAS); // 19
	sendCommand(CM_SET_GAIN_RATIO); // 9
	sendCommand(CM_GAIN_POT_RATIO);
	sendCommand(CM_START_LINE); // 8
	spiCSLow();
}

void sendCommand(unsigned char data) {
	SPI_SEND_INSTR;
	spiTxByte(data);
	uSDelay(1000);

}

void sendData(unsigned char data) {
	SPI_SEND_DATA;
	spiTxByte(data);
}

void resetController() {
	mSDelay(200);
	RESET_LOW;
	mSDelay(2);
	RESET_HI;
	mSDelay(2);
}

void spiCSLow() {
	SPI_CS_LOW;
	uSDelay(1000);
}

void spiCSHi() {
	SPI_CS_HI;
	uSDelay(1000);
}

void spiTxByte(unsigned char data) {
	SPI_CLK_LOW;
	unsigned char bit_counter = 0;
	for (bit_counter=0; bit_counter < 8; bit_counter++) {
		if (CHECK_BIT(data, 7)) {
			SPI_DATA_HI;
		}
		else {
			SPI_DATA_LOW;
		}
		uSDelay(400);
		SPI_CLK_HI;
		uSDelay(400);
		SPI_CLK_LOW;
		data = data << 1;
	}
	uSDelay(400);
}



