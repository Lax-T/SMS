
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

/* AUX I2C bus */
#define AUXI2C_SCL_PIN GPIO_Pin_14
#define AUXI2C_SCL_PORT GPIOD
#define AUXI2C_SDA_PIN GPIO_Pin_15
#define AUXI2C_SDA_PORT GPIOD

/* DS3231 square waveform output (SQW) (MCU in) */
#define SQW_IN_PIN GPIO_Pin_11
#define SQW_IN_PORT GPIOA

/* Touch keys */
#define TK_SYNC_135_PIN GPIO_Pin_6
#define TK_SYNC_135_PORT GPIOD
#define TK_SYNC_24_PIN GPIO_Pin_4
#define TK_SYNC_24_PORT GPIOD
#define TK_BACK_PIN GPIO_Pin_7
#define TK_BACK_PORT GPIOD
#define TK_LEFT_PIN GPIO_Pin_5
#define TK_LEFT_PORT GPIOD
#define TK_OK_PIN GPIO_Pin_3
#define TK_OK_PORT GPIOD
#define TK_RIGHT_PIN GPIO_Pin_2
#define TK_RIGHT_PORT GPIOD
#define TK_OPT_PIN GPIO_Pin_1
#define TK_OPT_PORT GPIOD

/* LCD backlight (DAC1) */
#define LCDBL_PORT GPIOA
#define LCDBL_PIN GPIO_Pin_4

/* Functions */
void init();
unsigned char clkInit();
