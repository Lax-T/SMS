
#define HSE_CRYSTAL_MHZ 8

#define RCC_CLOCK_OK 0
#define RCC_HSE_FAIL 0x01
#define RCC_PLL_FAIL 0x02

void init();
unsigned char clkInit();
