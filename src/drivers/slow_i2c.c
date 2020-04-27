#include "drivers/slow_i2c.h"
#include "delays.h"
#include "globals.h"
#include "macros.h"

void sli2c_Start();
void sli2c_Stop();
void sli2c_SAck();
void sli2c_MAck();
void sli2c_MNAck();
void sli2c_TXByte(unsigned char data);
unsigned char sli2c_RXByte();

/* Protocol level */
void sli2c_sendCmd(u8 slave_adr, u8 cmd) {
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Do the work */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	sli2c_TXByte(cmd);
	sli2c_SAck();
	sli2c_Stop();
}

void sli2c_writeByte(u8 slave_adr, u8 word_adr, u8 data) {
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Do the work */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	sli2c_TXByte(word_adr);
	sli2c_SAck();
	sli2c_TXByte(data);
	sli2c_SAck();
	sli2c_Stop();
}

void sli2c_writeBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size) {
	u8 i;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Send slave and word address */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	sli2c_TXByte(word_adr);
	sli2c_SAck();
	/* Send data */
	for (i=0; i < data_size; i++) {
		sli2c_TXByte(data[i]);
		sli2c_SAck();
	}
	/* Done */
	sli2c_Stop();
}

unsigned char sli2c_readByte(u8 slave_adr, u8 word_adr) {
	u8 data;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Set read address */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	sli2c_TXByte(word_adr);
	sli2c_SAck();
	/* Set read bit */
	slave_adr = slave_adr | 0x01;
	/* Restart and read byte */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	data = sli2c_RXByte();
	sli2c_MNAck();
	sli2c_Stop();
	return data;
}

void sli2c_readBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size) {
	u8 i;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Set read address */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	sli2c_TXByte(word_adr);
	sli2c_SAck();
	/* Set read bit */
	slave_adr = slave_adr | 0x01;
	/* Restart and read */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	/* Read first byte */
	data[0] = sli2c_RXByte();
	/* Read second and next bytes */
	for (i=1; i < data_size; i++) {
		sli2c_MAck();
		data[i] = sli2c_RXByte();
	}
	/* Finalize transaction by NAck and Stop */
	sli2c_MNAck();
	sli2c_Stop();
}

/* Read block without setting address (current address read). */
void sli2c_readBlockCA(u8 slave_adr, u8 data[], u8 data_size) {
	u8 i;
	/* Shift address and set read bit */
	slave_adr = (slave_adr << 1) | 0x01;
	/* Restart and read */
	sli2c_Start();
	sli2c_TXByte(slave_adr);
	sli2c_SAck();
	/* Read first byte */
	data[0] = sli2c_RXByte();
	/* Read second and next bytes */
	for (i=1; i < data_size; i++) {
		sli2c_MAck();
		data[i] = sli2c_RXByte();
	}
	/* Finalize transaction by NAck and Stop */
	sli2c_MNAck();
	sli2c_Stop();
}

/* Hardware level */
void sli2c_Start() {
	mSLI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void sli2c_Stop() {
	mSLI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
}

void sli2c_SAck() {
	mSLI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void sli2c_MAck() {
	mSLI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SDA_HI;
	uSDelay(USDELAY_CALC(3));
}

void sli2c_MNAck() {
	mSLI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mSLI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void sli2c_TXByte(unsigned char data) {
	char i = 0;
	for (i=0; i < 8; i++) {
		if (CHECK_BIT(data, 7)) {
			mSLI2C_SDA_HI;
		}
		else {
			mSLI2C_SDA_LOW;
		}
		uSDelay(USDELAY_CALC(3));
		mSLI2C_SCL_HI;
		uSDelay(USDELAY_CALC(6));
		mSLI2C_SCL_LOW;
		uSDelay(USDELAY_CALC(3));
		data = data << 1;
	}
	uSDelay(USDELAY_CALC(3));
}

unsigned char sli2c_RXByte() {
	unsigned char data=0;
	char i = 0;
	for (i=0; i < 8; i++) {
		data = data << 1;
		mSLI2C_SCL_HI;
		uSDelay(USDELAY_CALC(3));
		if (mSLI2C_SDA_IN) {
			data = data | 0x01;
		}
		uSDelay(USDELAY_CALC(3));
		mSLI2C_SCL_LOW;
		uSDelay(USDELAY_CALC(6));
	}
	return data;
}
