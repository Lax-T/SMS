#include <ui/fonts/digital25px.h>

static u8 chr_digital25px_blank[] = {0x0e, 0x19,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; //   0x20 (32)
static u8 chr_digital25px_46[] = {0x09, 0x19,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x00, 0x00}; // . 0x2e (46)
static u8 chr_digital25px_47[] = {0x0c, 0x19,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // / 0x2f (47)
static u8 chr_digital25px_48[] = {0x0e, 0x19,
	0x3f, 0x3f, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x00, 0xc0, 0xe0, 0xe0,
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x3f, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0x0c, 0x00, 0x0c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 0 0x30 (48)
static u8 chr_digital25px_49[] = {0x0e, 0x19,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0x0c, 0x00, 0x0c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x0c,
	0x00, 0x00}; // 1 0x31 (49)
static u8 chr_digital25px_50[] = {0x0e, 0x19,
	0x3f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0xdf, 0xe0, 0xe0,
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x3f, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0xec, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0,
	0xf0, 0xf0}; // 2 0x32 (50)
static u8 chr_digital25px_51[] = {0x0e, 0x19,
	0x3f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0xec, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 3 0x33 (51)
static u8 chr_digital25px_52[] = {0x0e, 0x19,
	0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0xec, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x0c,
	0x00, 0x00}; // 4 0x34 (52)
static u8 chr_digital25px_53[] = {0x0e, 0x19,
	0x3f, 0x3f, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 5 0x35 (53)
static u8 chr_digital25px_54[] = {0x0e, 0x19,
	0x3f, 0x3f, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0xdf, 0xe0, 0xe0,
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x3f, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 6 0x36 (54)
static u8 chr_digital25px_55[] = {0x0e, 0x19,
	0x3f, 0x3f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0x0c, 0x00, 0x0c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x0c,
	0x00, 0x00}; // 7 0x37 (55)
static u8 chr_digital25px_56[] = {0x0e, 0x19,
	0x3f, 0x3f, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0xdf, 0xe0, 0xe0,
	0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x3f, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0xec, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 8 0x38 (56)
static u8 chr_digital25px_57[] = {0x0e, 0x19,
	0x3f, 0x3f, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0x3f, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x3f, 0xf0, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c,
	0x1c, 0x1c, 0x1c, 0x1c, 0xec, 0xf0, 0xec, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xec,
	0xf0, 0xf0}; // 9 0x39 (57)
static u8 chr_digital25px_58[] = {0x09, 0x19,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // : 0x3a (58)

static u8 *font_digital25px[] = {chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_46, chr_digital25px_47, chr_digital25px_48, chr_digital25px_49,
	chr_digital25px_50, chr_digital25px_51, chr_digital25px_52, chr_digital25px_53, chr_digital25px_54, chr_digital25px_55, chr_digital25px_56, chr_digital25px_57, chr_digital25px_58, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank,
	chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank, chr_digital25px_blank};


u8* getDigital25pxPtr() {
	return font_digital25px;
}

