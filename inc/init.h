
#define HSE_CRYSTAL_MHZ 8

#define RCC_CLOCK_OK 0
#define RCC_HSE_FAIL 0x01
#define RCC_PLL_FAIL 0x02

/* IO definitions */
/* Slow I2C bus */
#define SLI2C_SCL_PIN GPIO_Pin_9
#define SLI2C_SCL_PORT GPIOA
#define SLI2C_SDA_PIN GPIO_Pin_10
#define SLI2C_SDA_PORT GPIOA

/* DS3231 square waveform output (SQW) (MCU in) */
#define SQW_IN_PIN GPIO_Pin_11
#define SQW_IN_PORT GPIOA

/* Functions */
void init();
unsigned char clkInit();
