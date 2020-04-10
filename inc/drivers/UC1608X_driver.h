#include "stm32f2xx.h"

/*
 * CS - PB8
 * RST - PB9
 * DI - PE0
 * CLK - PB3
 * DATA - PB5
 *
 */

#define GLCD_PAGES 16
#define GLCD_COLUMNS 240

#define SPI_CS_PORT GPIOB
#define SPI_CS_PIN GPIO_Pin_8
#define SPI_CS_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_8);
#define SPI_CS_HI GPIO_SetBits(GPIOB, GPIO_Pin_8);

#define RESET_PORT GPIOB
#define RESET_PIN GPIO_Pin_9
#define RESET_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_9);
#define RESET_HI GPIO_SetBits(GPIOB, GPIO_Pin_9);

#define SPI_DAT_INSTR_PORT GPIOE
#define SPI_DAT_INSTR_PIN GPIO_Pin_0
#define SPI_SEND_INSTR GPIO_ResetBits(GPIOE, GPIO_Pin_0);
#define SPI_SEND_DATA GPIO_SetBits(GPIOE, GPIO_Pin_0);

#define SPI_CLK_PORT GPIOB
#define SPI_CLK_PIN GPIO_Pin_3
#define SPI_CLK_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_3);
#define SPI_CLK_HI GPIO_SetBits(GPIOB, GPIO_Pin_3);

#define SPI_DATA_PORT GPIOB
#define SPI_DATA_PIN GPIO_Pin_5
#define SPI_DATA_LOW GPIO_ResetBits(GPIOB, GPIO_Pin_5);
#define SPI_DATA_HI GPIO_SetBits(GPIOB, GPIO_Pin_5);

void uc_initController();
void uc_lcdOn();
void uc_setWriteAddress(unsigned char page, unsigned char column);
void uc_writeSingle(unsigned char data);
void uc_writeArray(u8 *arr, u8 length);
void uc_writeFullBuffer(u8 buffer[][GLCD_COLUMNS]);

