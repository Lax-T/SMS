#include <globals.h>

#define CHAINED_DEVICES_N 2

/* FUNC REG BITS */
/* When this bit is 0, the auto display repeat function is disabled.
Each constant-current output is turned on and off for one display period.
When this bit is 1, each output repeats the PWM control every 65,536 GSCLKs. */
#define TLC_DISPRPT_ON 0x01
#define TLC_DISPRPT_OFF 0x00
/* When this bit is 0, the GS counter is not reset and the outputs are not forced off even
367 TMGRST when a LAT rising edge is input for a GS data write.
When this bit is 1, the GS counter is reset to 0 and all outputs are forced off at the
LAT rising edge for a GS data write. Afterwards, PWM control resumes from the next
GSCLK rising edge.*/
#define TLC_TIMRST_ON 0x02
#define TLC_TIMRST_OFF 0x00
/* When this bit is 0, the auto data refresh function is disabled. The data in the common
shift register are copied to the GS data latch at the next LAT rising edge for a GS N/A data write.
DC data in the control data latch are copied to the DC data latch at the 368 RFRESH (no default
same time. value) When this bit is 1, the auto data refresh function is enabled.
The data in the common shift register are copied to the GS data latch
at the 65,536th GSCLK after the LAT rising edge for a GS data write.
DC data in the control data latch are copied to the DC data latch at the same time. */
#define TLC_DATARFSH_ON 0x04
#define TLC_DATARFSH_OFF 0x00
/* When this bit is 0, the conventional PWM control mode is selected.
If the TLC5955 is 369 ESPWM used for multiplexing a drive,
the conventional PWM mode should be selected to prevent excess on or off switching.
When this bit is 1, ES-PWM control mode is selected.*/
#define TLC_ESPWM_ON 0x08
#define TLC_ESPWM_OFF 0x00
/* LED short detection (LSD) detects a fault caused by a shorted LED by comparing the
OUTXn voltage to the LSD detection threshold voltage.
The threshold voltage is 370 LSDVLT selected by this bit.
When this bit is 0, the LSD voltage is VCC x 70%. When this bit is 1,
the LSD voltage is VCC x 90%. */
#define TLC_LSDVLT_90 0x10
#define TLC_LSDVLT_70 0x00
/* Max current settings (mA) */
#define TLC_MAXCURR_3 0x00
#define TLC_MAXCURR_8 0x01
#define TLC_MAXCURR_11 0x02
#define TLC_MAXCURR_16 0x03
#define TLC_MAXCURR_19 0x04
#define TLC_MAXCURR_24 0x05
// 27 and 32 options disabled for safety
//#define TLC_MAXCURR_27 0x06
//#define TLC_MAXCURR_32 0x07

/* Driver IC configuration values. */
struct TLCConfig {
	u8 func_reg;
	u8 brightness;
	u8 max_current;
	u8 dot_corr[CHAINED_DEVICES_N * 48];
};

void tlc_updateConfigALL(struct TLCConfig config);
void tlc_updateGSAll(u16 *buffer);




