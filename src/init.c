#include "init.h"
#include "stm32f2xx.h"

GPIO_InitTypeDef GPIOInit;
TIM_TimeBaseInitTypeDef  TIMInit;
DAC_InitTypeDef DACInit;
ADC_InitTypeDef ADCInit;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef timerPWM;


/* System clock configuration */
unsigned char clkInit() {
	u8 status = 0;
	u16 pll_delay = 0;

	/* First, ensure that running on internal 16MHz RC clock. */
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	/* Disable PLL (to be able to reconfigure later)*/
	RCC_PLLCmd(DISABLE);
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);
	/* Wait for HSE to stabilize */
	if (RCC_WaitForHSEStartUp() == SUCCESS) {
		/* When HSE ready, configure PLL
		Clock: HSE, VCO: 2*192 = 384MHZ, SYSCLK: 384/4 = 96MHz, USB/SDIO/RNG: 384/8 = 48MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE, (HSE_CRYSTAL_MHZ / 2), 192, 4, 8);
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);
		/* Wait for PLL to stabilize. */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
			pll_delay++;
			if (pll_delay >= 4000) { // Approximately 8...10mS
				/* If PLL didn't stabilize within timeout, set error flag and break; */
				status |= RCC_PLL_FAIL;
				break;
			}
		}
		/* Check if PLL actually stabilized. */
		if (status == RCC_CLOCK_OK) { // All flags clear (0)
			/* Set Flash memory latency */
			FLASH_SetLatency(FLASH_Latency_3); // 4 CPU cycles
			/* Configure AHB clock */
			RCC_HCLKConfig(RCC_SYSCLK_Div1); // 96MHz
			/* Configure High Speed APB2 clock */
			RCC_PCLK2Config(RCC_HCLK_Div2); // 48MHZ
			/* Configure Low Speed APB1 clock */
			RCC_PCLK1Config(RCC_HCLK_Div4); // 24MHz
			/* Switch system clock to PLL */
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		}
		/* If PLL did not stabilize, leave HSI (16MHz) as clock source and return error code */
		return status;

	} else {
		/* If HSE did not stabilize, set error flag */
		status |= RCC_HSE_FAIL;
		/* Run PLL from HSI, Clock: HSI, VCO: 2*192 = 384MHZ, SYSCLK: 384/4 = 96MHz, USB/SDIO/RNG: 384/8 = 48MHz */
		RCC_PLLConfig(RCC_PLLSource_HSI, 8, 192, 4, 8);
		/* Enable PLL */
		RCC_PLLCmd(ENABLE);
		/* Wait for PLL to stabilize. */
		while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
			pll_delay++;
			if (pll_delay >= 4000) { // Approximately 8...10mS
				/* If PLL didn't stabilize within timeout, set error flag and break; */
				status |= RCC_PLL_FAIL;
				break;
			}
		}
		/* Check if PLL actually stabilized. */
		if ((status & ~RCC_HSE_FAIL) == RCC_CLOCK_OK) { // All flags, except RCC_HSE_FAIL clear
			/* Set Flash memory latency */
			FLASH_SetLatency(FLASH_Latency_3); // 4 CPU cycles
			/* Configure AHB clock */
			RCC_HCLKConfig(RCC_SYSCLK_Div1); // 96MHz
			/* Configure High Speed APB2 clock */
			RCC_PCLK2Config(RCC_HCLK_Div2); // 48MHZ
			/* Configure Low Speed APB1 clock */
			RCC_PCLK1Config(RCC_HCLK_Div4); // 24MHz
			/* Switch system clock to PLL */
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		}
		/* If PLL did not stabilize, leave HSI (16MHz) as clock source and return error code. */
		return status;
	}
}

void init() {

	/* Enable peripheral clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	/* PORT A init */
	GPIOInit.GPIO_Mode = GPIO_Mode_IN;
	GPIOInit.GPIO_Pin = SQW_IN_PIN;
	GPIO_Init(GPIOA, &GPIOInit);

	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_OType= GPIO_OType_OD;
	GPIOInit.GPIO_Pin = SLI2C_SCL_PIN | SLI2C_SDA_PIN;
	GPIOInit.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA, &GPIOInit);
	/* Set HI slow I2C bus SCL/SDA lines. */
	GPIO_SetBits(GPIOA, SLI2C_SCL_PIN);
	GPIO_SetBits(GPIOA, SLI2C_SDA_PIN);

	/*
	// PORT A init
	GPIOInit.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIOInit.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOInit);

	GPIO_ResetBits(GPIOA, GPIO_Pin_12); // DISP clock low
	GPIO_ResetBits(GPIOA, GPIO_Pin_11); // DISP driver latch low
	GPIO_SetBits(GPIOA, GPIO_Pin_3); // DAC SYNC high
	GPIO_SetBits(GPIOA, GPIO_Pin_5); // DAC CLOCK high
	GPIO_SetBits(GPIOA, GPIO_Pin_6); // DAC SYNC high
	*/

	/*
	// PORT B init
	GPIOInit.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIOInit.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	GPIO_SetBits(GPIOB, GPIO_Pin_14); // DISP OE high (output disable)
	GPIO_ResetBits(GPIOB, GPIO_Pin_13); // DISP register latch low
	GPIO_SetBits(GPIOB, GPIO_Pin_2); // ADC CS HI
	GPIO_ResetBits(GPIOB, GPIO_Pin_1); // ADC CLK LOW
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); // FAN OFF
	GPIO_ResetBits(GPIOB, GPIO_Pin_7); // OUT OFF

	GPIOInit.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIOInit.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;  // EEPROM SDA, SCL
	GPIOInit.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIOInit);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	*/

	// PORT B init
	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_OType= GPIO_OType_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_8 |
			GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInit);

	// PORT D init
	GPIOInit.GPIO_Mode = GPIO_Mode_IN;
	GPIOInit.GPIO_Pin = TK_BACK_PIN | TK_LEFT_PIN | TK_OK_PIN | TK_RIGHT_PIN | TK_OPT_PIN;
	GPIO_Init(GPIOD, &GPIOInit);

	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_OType= GPIO_OType_PP;
	GPIOInit.GPIO_Pin = TK_SYNC_135_PIN | TK_SYNC_24_PIN | GPIO_Pin_8 | GPIO_Pin_13;
	GPIOInit.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIOInit);

	GPIO_SetBits(TK_SYNC_135_PORT, TK_SYNC_135_PIN);
	GPIO_SetBits(TK_SYNC_24_PORT, TK_SYNC_24_PIN);

	// PORT E init
	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_OType= GPIO_OType_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIOInit);

	// GCLOCK
	GPIOInit.GPIO_Mode = GPIO_Mode_AF;
	GPIOInit.GPIO_OType= GPIO_OType_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_12;
	GPIOInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIOInit);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);


	// TIMER 6 init - delays counter
	TIMInit.TIM_Period  = 0xffff;
	TIMInit.TIM_Prescaler = (1)-1;
	TIMInit.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMInit.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIMInit);
	TIM_Cmd(TIM6, ENABLE);


	// ADC init
	/*
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	ADCInit.ADC_Mode = ADC_Mode_Independent;
	ADCInit.ADC_ScanConvMode = DISABLE;
	ADCInit.ADC_ContinuousConvMode = DISABLE;
	ADCInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADCInit.ADC_DataAlign = ADC_DataAlign_Right;
	ADCInit.ADC_NbrOfChannel = 1;
	ADC_Init ( ADC1, &ADCInit);

	ADC_Cmd (ADC1, ENABLE);  //enable ADC1*/

	TIM_TimeBaseStructure.TIM_Period  = 0x0003;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4, ENABLE);

	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_Pulse = 0x0002;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &timerPWM);

	/*
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	*/
}

