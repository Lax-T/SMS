#include "stm32f2xx.h"

/* IO pin mappings */
#define mAUXI2C_SCL_HI GPIO_SetBits(GPIOD, GPIO_Pin_14);
#define mAUXI2C_SCL_LOW GPIO_ResetBits(GPIOD, GPIO_Pin_14);
#define mAUXI2C_SDA_HI GPIO_SetBits(GPIOD, GPIO_Pin_15);
#define mAUXI2C_SDA_LOW GPIO_ResetBits(GPIOD, GPIO_Pin_15);
#define mAUXI2C_SCL_IN GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14)
#define mAUXI2C_SDA_IN GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15)

/* Functions */
void auxi2c_sendCmd(u8 slave_adr, u8 cmd);
void auxi2c_writeByte(u8 slave_adr, u8 word_adr, u8 data);
void auxi2c_writeBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size);
unsigned char auxi2c_readByte(u8 slave_adr, u8 word_adr);
void auxi2c_readBlock(u8 slave_adr, u8 word_adr, u8 data[], u8 data_size);
void auxi2c_readBlockCA(u8 slave_adr, u8 data[], u8 data_size, u8 is_clk_stretch);

