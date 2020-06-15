#include "drivers/aux_i2c.h"
#include "delays.h"
#include "globals.h"
#include "macros.h"

void auxi2c_Start();
void auxi2c_Stop();
void auxi2c_SAck();
void auxi2c_MAck();
void auxi2c_MNAck();
void auxi2c_TXByte(unsigned char data);
unsigned char auxi2c_RXByte(u8 is_clk_stretch);

/* Protocol level */
void auxi2c_sendCmd(u8 slave_adr, u8 cmd) {
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Do the work */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	auxi2c_TXByte(cmd);
	auxi2c_SAck();
	auxi2c_Stop();
}

void auxi2c_writeByte(u8 slave_adr, u8 word_adr, u8 data) {
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Do the work */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	auxi2c_TXByte(word_adr);
	auxi2c_SAck();
	auxi2c_TXByte(data);
	auxi2c_SAck();
	auxi2c_Stop();
}

void auxi2c_writeBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size) {
	u8 i;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Send slave and word address */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	auxi2c_TXByte(word_adr);
	auxi2c_SAck();
	/* Send data */
	for (i=0; i < data_size; i++) {
		auxi2c_TXByte(data[i]);
		auxi2c_SAck();
	}
	/* Done */
	auxi2c_Stop();
}

unsigned char auxi2c_readByte(u8 slave_adr, u8 word_adr) {
	u8 data;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Set read address */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	auxi2c_TXByte(word_adr);
	auxi2c_SAck();
	/* Set read bit */
	slave_adr = slave_adr | 0x01;
	/* Restart and read byte */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	data = auxi2c_RXByte(FALSE);
	auxi2c_MNAck();
	auxi2c_Stop();
	return data;
}

void auxi2c_readBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size) {
	u8 i;
	/* Shift address and set write bit */
	slave_adr = (slave_adr << 1) & 0xFE;
	/* Set read address */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	auxi2c_TXByte(word_adr);
	auxi2c_SAck();
	/* Set read bit */
	slave_adr = slave_adr | 0x01;
	/* Restart and read */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	/* Read first byte */
	data[0] = auxi2c_RXByte(FALSE);
	/* Read second and next bytes */
	for (i=1; i < data_size; i++) {
		auxi2c_MAck();
		data[i] = auxi2c_RXByte(FALSE);
	}
	/* Finalize transaction by NAck and Stop */
	auxi2c_MNAck();
	auxi2c_Stop();
}

/* Read block without setting address (current address read). */
void auxi2c_readBlockCA(u8 slave_adr, u8 data[], u8 data_size, u8 is_clk_stretch) {
	u8 i;
	/* Shift address and set read bit */
	slave_adr = (slave_adr << 1) | 0x01;
	/* Restart and read */
	auxi2c_Start();
	auxi2c_TXByte(slave_adr);
	auxi2c_SAck();
	/* Read first byte */
	data[0] = auxi2c_RXByte(is_clk_stretch);
	/* Read second and next bytes */
	for (i=1; i < data_size; i++) {
		auxi2c_MAck();
		data[i] = auxi2c_RXByte(is_clk_stretch);
	}
	/* Finalize transaction by NAck and Stop */
	auxi2c_MNAck();
	auxi2c_Stop();
}

/* Hardware level */
void auxi2c_Start() {
	mAUXI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void auxi2c_Stop() {
	mAUXI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
}

void auxi2c_SAck() {
	mAUXI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void auxi2c_MAck() {
	mAUXI2C_SDA_LOW;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SDA_HI;
	uSDelay(USDELAY_CALC(3));
}

void auxi2c_MNAck() {
	mAUXI2C_SDA_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_HI;
	uSDelay(USDELAY_CALC(6));
	mAUXI2C_SCL_LOW;
	uSDelay(USDELAY_CALC(6));
}

void auxi2c_TXByte(unsigned char data) {
	char i = 0;
	for (i=0; i < 8; i++) {
		if (CHECK_BIT(data, 7)) {
			mAUXI2C_SDA_HI;
		}
		else {
			mAUXI2C_SDA_LOW;
		}
		uSDelay(USDELAY_CALC(3));
		mAUXI2C_SCL_HI;
		uSDelay(USDELAY_CALC(6));
		mAUXI2C_SCL_LOW;
		uSDelay(USDELAY_CALC(3));
		data = data << 1;
	}
	uSDelay(USDELAY_CALC(3));
}

unsigned char auxi2c_RXByte(u8 is_clk_stretch) {
	unsigned char data=0;
	u16 cs_counter = 0;
	char i = 0;

	/* If required, check if SCL pin is released (clock stretching) */
	if (is_clk_stretch) {
		mAUXI2C_SCL_HI;
		uSDelay(USDELAY_CALC(6));
		while((mAUXI2C_SCL_IN == 0) && (cs_counter < 20000)) {
			uSDelay(USDELAY_CALC(50));
			cs_counter++;
		}
		uSDelay(USDELAY_CALC(6));
	}
	/* Continue read */
	for (i=0; i < 8; i++) {
		data = data << 1;
		mAUXI2C_SCL_HI;
		uSDelay(USDELAY_CALC(3));
		if (mAUXI2C_SDA_IN) {
			data = data | 0x01;
		}
		uSDelay(USDELAY_CALC(3));
		mAUXI2C_SCL_LOW;
		uSDelay(USDELAY_CALC(6));
	}
	return data;
}
