#include "stm32f2xx.h"

/* IO pin mappings */
#define mSLI2C_SCL_HI GPIO_SetBits(GPIOA, GPIO_Pin_9);
#define mSLI2C_SCL_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_9);
#define mSLI2C_SDA_HI GPIO_SetBits(GPIOA, GPIO_Pin_10);
#define mSLI2C_SDA_LOW GPIO_ResetBits(GPIOA, GPIO_Pin_10);
#define mSLI2C_SCL_IN GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9)
#define mSLI2C_SDA_IN GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10)

/* Functions */
void sli2c_sendCmd(u8 slave_adr, u8 cmd);
void sli2c_writeByte(u8 slave_adr, u8 word_adr, u8 data);
void sli2c_writeBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size);
unsigned char sli2c_readByte(u8 slave_adr, u8 word_adr);
void sli2c_readBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size);
void sli2c_readBlockCA(u8 slave_adr, u8 data[], u8 data_size, u8 is_clk_stretch);
