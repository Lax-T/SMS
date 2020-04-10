

/* LED driver IC channels mapping
 * ICn1 B15-R0: buffer 0 - 47, ICn0 B15-R0: buffer 48 - 95
 */
// LED bar
#define BAR_LED_1R 19 // G9
#define BAR_LED_1G 20 // R9
#define BAR_LED_1B 18 // B9

#define BAR_LED_2R 7 // G13
#define BAR_LED_2G 8 // R13
#define BAR_LED_2B 6 // B13

#define BAR_LED_3R 4 // G14
#define BAR_LED_3G 5 // R14
#define BAR_LED_3B 3 // B14

#define BAR_LED_4R 16 // G10
#define BAR_LED_4G 17 // R10
#define BAR_LED_4B 15 // B10

#define BAR_LED_5R 1 // G15
#define BAR_LED_5G 2 // R15
#define BAR_LED_5B 0 // B15

#define BAR_LED_6R 13 // G11
#define BAR_LED_6G 14 // R11
#define BAR_LED_6B 12 // B11

#define BAR_LED_7R 24 // B7
#define BAR_LED_7G 26 // R7
#define BAR_LED_7B 25 // G7

#define BAR_LED_8R 36 // B3
#define BAR_LED_8G 38 // R3
#define BAR_LED_8B 37 // G3

#define BAR_LED_9R 27 // B6
#define BAR_LED_9G 29 // R6
#define BAR_LED_9B 28 // G6

// AMBIENT LEDs
#define AMBI_LED_1R 91 // G1 - 0
#define AMBI_LED_1G 92 // R1 - 0
#define AMBI_LED_1B 90 // B1 - 0

#define AMBI_LED_2R 88 // G2 - 0
#define AMBI_LED_2G 89 // R2 - 0
#define AMBI_LED_2B 87 // B2 - 0

#define AMBI_LED_3R 76 // G6 - 0
#define AMBI_LED_3G 77 // R6 - 0
#define AMBI_LED_3B 75 // B6 - 0

#define AMBI_LED_4R 85 // G3 - 0
#define AMBI_LED_4G 86 // R3 - 0
#define AMBI_LED_4B 84 // B3 - 0

#define AMBI_LED_5R 73 // G7 - 0
#define AMBI_LED_5G 74 // R7 - 0
#define AMBI_LED_5B 72 // B7 - 0

#define AMBI_LED_6R 60 // B11 - 0
#define AMBI_LED_6G 62 // R11 - 0
#define AMBI_LED_6B 61 // G11 - 0

#define AMBI_LED_7R 48 // B15 - 0
#define AMBI_LED_7G 50 // R15 - 0
#define AMBI_LED_7B 49 // G15 - 0

// KB BACKLIGHT LEDs
#define KBL_LED_1 23 // R8
#define KBL_LED_2 22 // G8
#define KBL_LED_3 9 // B12
#define KBL_LED_4 11 // R12
#define KBL_LED_5 10 // G12

// SECOND LEDs
#define SLED_CGROUP_1 81 // B4
#define SLED_CGROUP_2 83 // R4
#define SLED_CGROUP_3 82 // G4
#define SLED_CGROUP_4 93 // B0
#define SLED_CGROUP_5 95 // R0
#define SLED_CGROUP_6 94 // G0
#define SLED_CGROUP_7 78 // B5
#define SLED_CGROUP_8 80 // R5

// MINUTE LEDs
#define MINUTE1_LED_A 32 // R5
#define MINUTE1_LED_B 30 // B5
#define MINUTE1_LED_C 46 // G0
#define MINUTE1_LED_D 47 // R0
#define MINUTE1_LED_E 45 // B0
#define MINUTE1_LED_F 35 // R4
#define MINUTE1_LED_G 34 // G4

#define MINUTE2_LED_A 44 // R1
#define MINUTE2_LED_B 43 // G1
#define MINUTE2_LED_C 41 // R2
#define MINUTE2_LED_D 40 // G2
#define MINUTE2_LED_E 39 // B2
#define MINUTE2_LED_F 31 // G5
#define MINUTE2_LED_G 42 // B1

// HOUR LEDs
#define HOUR1_LED_A 66 // B9 - 0
#define HOUR1_LED_B 54 // B13 - 0
#define HOUR1_LED_C 56 // R13 - 0
#define HOUR1_LED_D 67 // G9 - 0
#define HOUR1_LED_E 59 // R12 - 0
#define HOUR1_LED_F 58 // G12 - 0
#define HOUR1_LED_G 68 // R9 - 0

#define HOUR2_LED_A 65 // R10 - 0
#define HOUR2_LED_B 63 // B10 - 0
#define HOUR2_LED_C 51 // B14 - 0
#define HOUR2_LED_D 55 // G13 - 0
#define HOUR2_LED_E 53 // R14 - 0
#define HOUR2_LED_F 64 // G10 - 0
#define HOUR2_LED_G 52 // G14 - 0

void lc_init();
void lc_refresh();
void lc_updateDriversConfig();

void lc_setSecondValue(u8 second);
void lc_setSecondBrt(u8 brt);
void lc_setTimeValue (u8 hour, u8 minute);
void lc_setTimeBrt (u8 brt);

void lc_setBacklightValues(u8 bl_values[5]);
void lc_setBacklightGroupValue(u8 val);
void lc_setBacklightBrt(u8 brt);

void lc_setBarValues(u8 bar_values[27]);
void lc_setBarGroupValue(u8 r_val, u8 g_val, u8 b_val);
void lc_setBarBrt(u8 brt);
void lc_setAmbientValues(u8 amb_values[21]);
void lc_setAmbientGroupValue(u8 r_val, u8 g_val, u8 b_val);
void lc_setAmbientBrt(u8 brt);








