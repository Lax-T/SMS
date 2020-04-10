#include "stm32f2xx.h"

//Status LED
#define mSLED_RED_ON GPIO_SetBits(GPIOD, GPIO_Pin_8);
#define mSLED_RED_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_8);
#define mSLED_GREEN_ON GPIO_SetBits(GPIOD, GPIO_Pin_13);
#define mSLED_GREEN_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_13);

//
#define mBTN_SYNC_135_ON GPIO_SetBits(GPIOD, GPIO_Pin_6);
#define mBTN_SYNC_135_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_6);
#define mBTN_IN_OK GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)

// LDR
#define mLDR_CLK_HI GPIO_SetBits(GPIOB, GPIO_Pin_13);
#define mLDR_CLK_LO GPIO_ResetBits(GPIOB, GPIO_Pin_13);

#define mLDR_DATA_HI GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define mLDR_DATA_LO GPIO_ResetBits(GPIOB, GPIO_Pin_15);

#define mLDR_LAT_HI GPIO_SetBits(GPIOB, GPIO_Pin_12);
#define mLDR_LAT_LO GPIO_ResetBits(GPIOB, GPIO_Pin_12);
