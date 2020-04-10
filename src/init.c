#include "init.h"
#include "stm32f2xx.h"

GPIO_InitTypeDef GPIOInit;
TIM_TimeBaseInitTypeDef  TIMInit;
DAC_InitTypeDef DACInit;
ADC_InitTypeDef ADCInit;

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef timerPWM;

void init() {

	// Enable peripheral clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 , ENABLE);

	/*
	// Set system clock to HSI > PLL x4 (16 MHz)
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_4);
	RCC_PLLCmd(ENABLE);
	// If PLL is not starting with internal RC something is really wrong...
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	*/

	/*
	// PORT A init
	GPIOInit.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInit.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOA, &GPIOInit);

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
	GPIOInit.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_Init(GPIOD, &GPIOInit);

	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_OType= GPIO_OType_PP;
	GPIOInit.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_13;
	GPIOInit.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIOInit);

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

	TIM_TimeBaseStructure.TIM_Period  = 0x0002;
	TIM_TimeBaseStructure.TIM_Prescaler = (1)-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4, ENABLE);

	timerPWM.TIM_OCMode = TIM_OCMode_PWM1;
	timerPWM.TIM_OutputState = TIM_OutputState_Enable;
	timerPWM.TIM_Pulse = 0x0001;
	timerPWM.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &timerPWM);

	/*
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	*/
}

