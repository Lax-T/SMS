#include "stm32f2xx.h"
#include "globals.h"

/* Pin definitions */
#define mBTN_SYNC_135_ON GPIO_SetBits(GPIOD, GPIO_Pin_6);
#define mBTN_SYNC_135_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_6);
#define mBTN_SYNC_24_ON GPIO_SetBits(GPIOD, GPIO_Pin_4);
#define mBTN_SYNC_24_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_4);

#define mBTN_IN_BACK GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_7)
#define mBTN_IN_LEFT GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5)
#define mBTN_IN_OK GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3)
#define mBTN_IN_RIGHT GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)
#define mBTN_IN_OPT GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1)

/* Key definitions */
#define BACK_KEY 1
#define LEFT_KEY 2
#define OK_KEY 3
#define RIGHT_KEY 4
#define OPT_KEY 5
#define BACK_KEY_LP 6
#define OK_KEY_LP 8
#define OPT_KEY_LP 10
#define LP_KEYN_OFFSET 5

/* Alternative function definitions */
#define TK_NO_AF 0
#define TK_AF_LPRESS 1
#define TK_AF_REPEAT 2

/* Alternative steps */
#define ALT_DELAY 0
#define REPEAT_DELAY 1
#define WAIT_RELEASE 2

/* Struct definitions */
#ifndef TOUCH_KEYS_STATE_STRUCT_DEF_
#define TOUCH_KEYS_STATE_STRUCT_DEF_
/* Holds touch keyboard scan status */
struct TouchKeysState {
	u8 alt_functions[5];
	u8 alt_step;
	u8 last_pressed;
	u8 counter;
};

#endif

/* Function definitions */
u8 tk_scanKeys();




