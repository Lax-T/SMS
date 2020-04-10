#include <ui/fonts/arial12b.h>

static u8 chr_arial12b_blank[] = {0x0a, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; //   0x20 (32)
static u8 chr_arial12b_33[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // ! 0x21 (33)
static u8 chr_arial12b_34[] = {0x07, 0x11,
	0x00, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // " 0x22 (34)
static u8 chr_arial12b_35[] = {0x08, 0x11,
	0x00, 0x1b, 0x1b, 0x1b, 0x7f, 0x7f, 0x36, 0x36, 0x7f, 0x7f, 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00,
	0x00}; // # 0x23 (35)
static u8 chr_arial12b_36[] = {0x08, 0x11,
	0x08, 0x1c, 0x3e, 0x6b, 0x68, 0x78, 0x3c, 0x1e, 0x0f, 0x6b, 0x6b, 0x3e, 0x1c, 0x08, 0x00, 0x00,
	0x00}; // $ 0x24 (36)
static u8 chr_arial12b_37[] = {0x0f, 0x11,
	0x00, 0x78, 0xcc, 0xcc, 0xcc, 0xcd, 0x79, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x60, 0x60, 0xc0, 0x80, 0x80, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00,
	0x00, 0x00}; // % 0x25 (37)
static u8 chr_arial12b_38[] = {0x0c, 0x11,
	0x00, 0x1f, 0x3f, 0x31, 0x31, 0x1f, 0x1e, 0x36, 0x67, 0x63, 0x61, 0x3f, 0x1e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x40, 0x60, 0xc0, 0xe0, 0xf0, 0x20, 0x00, 0x00,
	0x00, 0x00}; // & 0x26 (38)
static u8 chr_arial12b_39[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // ' 0x27 (39)
static u8 chr_arial12b_40[] = {0x05, 0x11,
	0x00, 0x18, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30, 0x30, 0x18,
	0x00}; // ( 0x28 (40)
static u8 chr_arial12b_41[] = {0x04, 0x11,
	0x00, 0xc0, 0x60, 0x60, 0x60, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60, 0xc0,
	0x00}; // ) 0x29 (41)
static u8 chr_arial12b_42[] = {0x05, 0x11,
	0x00, 0x20, 0xf8, 0x20, 0xd8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // * 0x2a (42)
static u8 chr_arial12b_43[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // + 0x2b (43)
static u8 chr_arial12b_44[] = {0x03, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x20, 0x40,
	0x00}; // , 0x2c (44)
static u8 chr_arial12b_45[] = {0x05, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // - 0x2d (45)
static u8 chr_arial12b_46[] = {0x03, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // . 0x2e (46)
static u8 chr_arial12b_47[] = {0x04, 0x11,
	0x00, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00,
	0x00}; // / 0x2f (47)
static u8 chr_arial12b_48[] = {0x08, 0x11,
	0x00, 0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // 0 0x30 (48)
static u8 chr_arial12b_49[] = {0x06, 0x11,
	0x00, 0x0c, 0x1c, 0x3c, 0x6c, 0x4c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00,
	0x00}; // 1 0x31 (49)
static u8 chr_arial12b_50[] = {0x08, 0x11,
	0x00, 0x3c, 0x7e, 0xe3, 0xc3, 0x03, 0x06, 0x0e, 0x1c, 0x38, 0x60, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00}; // 2 0x32 (50)
static u8 chr_arial12b_51[] = {0x08, 0x11,
	0x00, 0x3e, 0x7f, 0xc3, 0x03, 0x1e, 0x1e, 0x07, 0x03, 0xc3, 0xe7, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // 3 0x33 (51)
static u8 chr_arial12b_52[] = {0x08, 0x11,
	0x00, 0x06, 0x0e, 0x0e, 0x1e, 0x36, 0x36, 0x66, 0xc6, 0xff, 0xff, 0x06, 0x06, 0x00, 0x00, 0x00,
	0x00}; // 4 0x34 (52)
static u8 chr_arial12b_53[] = {0x08, 0x11,
	0x00, 0x7e, 0x7e, 0x60, 0xe0, 0xfc, 0xfe, 0xc7, 0x03, 0xc3, 0xe7, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // 5 0x35 (53)
static u8 chr_arial12b_54[] = {0x08, 0x11,
	0x00, 0x3e, 0x7f, 0x63, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0x63, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // 6 0x36 (54)
static u8 chr_arial12b_55[] = {0x08, 0x11,
	0x00, 0xff, 0xff, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x18, 0x38, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
	0x00}; // 7 0x37 (55)
static u8 chr_arial12b_56[] = {0x08, 0x11,
	0x00, 0x3c, 0x7e, 0xc3, 0xc3, 0xc3, 0x7e, 0x7e, 0xc3, 0xc3, 0xc3, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // 8 0x38 (56)
static u8 chr_arial12b_57[] = {0x08, 0x11,
	0x00, 0x3c, 0x7e, 0xc6, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b, 0x03, 0xc6, 0xfe, 0x7c, 0x00, 0x00, 0x00,
	0x00}; // 9 0x39 (57)
static u8 chr_arial12b_58[] = {0x04, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
	0x00}; // : 0x3a (58)
static u8 chr_arial12b_59[] = {0x04, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x10, 0x10, 0x20,
	0x00}; // ; 0x3b (59)
static u8 chr_arial12b_60[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x01, 0x07, 0x1e, 0x78, 0xe0, 0x78, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00}; // < 0x3c (60)
static u8 chr_arial12b_61[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // = 0x3d (61)
static u8 chr_arial12b_62[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x1e, 0x07, 0x1e, 0x78, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00}; // > 0x3e (62)
static u8 chr_arial12b_63[] = {0x09, 0x11,
	0x00, 0x1e, 0x3f, 0x71, 0x61, 0x03, 0x07, 0x0e, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // ? 0x3f (63)
static u8 chr_arial12b_64[] = {0x10, 0x11,
	0x00, 0x03, 0x0f, 0x1c, 0x39, 0x37, 0x76, 0x6c, 0x6c, 0x6c, 0x6c, 0x6f, 0x37, 0x38, 0x1c, 0x0f,
	0x03, 0x00, 0xf0, 0xfc, 0x0e, 0xde, 0xfb, 0x3b, 0x33, 0x33, 0x33, 0x76, 0xfc, 0xb8, 0x03, 0x0e,
	0xfc, 0xf0}; // @ 0x40 (64)
static u8 chr_arial12b_65[] = {0x0b, 0x11,
	0x00, 0x0e, 0x0e, 0x1b, 0x1b, 0x1b, 0x31, 0x31, 0x3f, 0x7f, 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x60, 0x00, 0x00,
	0x00, 0x00}; // A 0x41 (65)
static u8 chr_arial12b_66[] = {0x0b, 0x11,
	0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0xe0, 0x60, 0x60, 0xc0, 0x80, 0x00, 0x00,
	0x00, 0x00}; // B 0x42 (66)
static u8 chr_arial12b_67[] = {0x0b, 0x11,
	0x00, 0x0f, 0x3f, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x3f, 0x0f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xc0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xc0, 0x80, 0x00, 0x00,
	0x00, 0x00}; // C 0x43 (67)
static u8 chr_arial12b_68[] = {0x0b, 0x11,
	0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00}; // D 0x44 (68)
static u8 chr_arial12b_69[] = {0x0a, 0x11,
	0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00,
	0x00, 0x00}; // E 0x45 (69)
static u8 chr_arial12b_70[] = {0x09, 0x11,
	0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // F 0x46 (70)
static u8 chr_arial12b_71[] = {0x0b, 0x11,
	0x00, 0x0f, 0x3f, 0x30, 0x60, 0x60, 0x60, 0x63, 0x63, 0x60, 0x30, 0x3f, 0x0f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xc0, 0xe0, 0x40, 0x00, 0x00, 0xe0, 0xe0, 0x60, 0xe0, 0xc0, 0x80, 0x00, 0x00,
	0x00, 0x00}; // G 0x47 (71)
static u8 chr_arial12b_72[] = {0x0b, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00,
	0x00, 0x00}; // H 0x48 (72)
static u8 chr_arial12b_73[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // I 0x49 (73)
static u8 chr_arial12b_74[] = {0x08, 0x11,
	0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xc3, 0xe7, 0x7e, 0x3c, 0x00, 0x00, 0x00,
	0x00}; // J 0x4a (74)
static u8 chr_arial12b_75[] = {0x0b, 0x11,
	0x00, 0x60, 0x60, 0x61, 0x63, 0x66, 0x6f, 0x7b, 0x71, 0x61, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe0, 0x60, 0x00, 0x00,
	0x00, 0x00}; // K 0x4b (75)
static u8 chr_arial12b_76[] = {0x09, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // L 0x4c (76)
static u8 chr_arial12b_77[] = {0x0c, 0x11,
	0x00, 0x70, 0x70, 0x78, 0x78, 0x68, 0x6d, 0x6d, 0x6d, 0x67, 0x67, 0x67, 0x62, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x70, 0x70, 0xf0, 0xf0, 0xb0, 0xb0, 0xb0, 0xb0, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00,
	0x00, 0x00}; // M 0x4d (77)
static u8 chr_arial12b_78[] = {0x0b, 0x11,
	0x00, 0x60, 0x70, 0x78, 0x78, 0x6c, 0x66, 0x66, 0x63, 0x61, 0x61, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xe0, 0xe0, 0x60, 0x00, 0x00,
	0x00, 0x00}; // N 0x4e (78)
static u8 chr_arial12b_79[] = {0x0b, 0x11,
	0x00, 0x0f, 0x3f, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x3f, 0x0f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00}; // O 0x4f (79)
static u8 chr_arial12b_80[] = {0x0a, 0x11,
	0x00, 0x7f, 0x7f, 0x61, 0x60, 0x61, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // P 0x50 (80)
static u8 chr_arial12b_81[] = {0x0b, 0x11,
	0x00, 0x0f, 0x3f, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x66, 0x33, 0x3f, 0x0e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0, 0xc0, 0xc0, 0x60, 0x00,
	0x00, 0x00}; // Q 0x51 (81)
static u8 chr_arial12b_82[] = {0x0c, 0x11,
	0x00, 0x7f, 0x7f, 0x60, 0x60, 0x60, 0x7f, 0x7f, 0x63, 0x61, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xc0, 0xe0, 0x60, 0xe0, 0xc0, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0x70, 0x00, 0x00,
	0x00, 0x00}; // R 0x52 (82)
static u8 chr_arial12b_83[] = {0x0a, 0x11,
	0x00, 0x1f, 0x3f, 0x61, 0x60, 0x78, 0x3f, 0x0f, 0x01, 0x60, 0x71, 0x3f, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00}; // S 0x53 (83)
static u8 chr_arial12b_84[] = {0x0a, 0x11,
	0x00, 0xff, 0xff, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // T 0x54 (84)
static u8 chr_arial12b_85[] = {0x0b, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x3f, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xc0, 0x80, 0x00, 0x00,
	0x00, 0x00}; // U 0x55 (85)
static u8 chr_arial12b_86[] = {0x0b, 0x11,
	0x00, 0xc0, 0xc0, 0x60, 0x60, 0x31, 0x31, 0x31, 0x1b, 0x1b, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x60, 0x60, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // V 0x56 (86)
static u8 chr_arial12b_87[] = {0x0f, 0x11,
	0x00, 0xc3, 0xe3, 0x63, 0x66, 0x66, 0x36, 0x36, 0x36, 0x1c, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x86, 0x86, 0x8c, 0xcc, 0xcc, 0xd8, 0xd8, 0xd8, 0x78, 0x70, 0x70, 0x70, 0x00, 0x00,
	0x00, 0x00}; // W 0x57 (87)
static u8 chr_arial12b_88[] = {0x0a, 0x11,
	0x00, 0x60, 0x71, 0x31, 0x1b, 0x1f, 0x0e, 0x0e, 0x1f, 0x1b, 0x31, 0x71, 0x60, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x00, 0x00,
	0x00, 0x00}; // X 0x58 (88)
static u8 chr_arial12b_89[] = {0x0a, 0x11,
	0x00, 0xc0, 0xe1, 0x61, 0x33, 0x33, 0x1e, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // Y 0x59 (89)
static u8 chr_arial12b_90[] = {0x09, 0x11,
	0x00, 0x7f, 0x7f, 0x03, 0x06, 0x0e, 0x0c, 0x18, 0x38, 0x30, 0x60, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // Z 0x5a (90)
static u8 chr_arial12b_91[] = {0x05, 0x11,
	0x00, 0x78, 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x78,
	0x00}; // [ 0x5b (91)
static u8 chr_arial12b_92[] = {0x04, 0x11,
	0x00, 0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
	0x00}; // \ 0x5c (92)
static u8 chr_arial12b_93[] = {0x04, 0x11,
	0x00, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0,
	0x00}; // ] 0x5d (93)
static u8 chr_arial12b_94[] = {0x08, 0x11,
	0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // ^ 0x5e (94)
static u8 chr_arial12b_95[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x00}; // _ 0x5f (95)
static u8 chr_arial12b_96[] = {0x03, 0x11,
	0x00, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00}; // ` 0x60 (96)
static u8 chr_arial12b_97[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x0f, 0x3f, 0x73, 0x63, 0x7f, 0x3d, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
	0x00, 0x00}; // a 0x61 (97)
static u8 chr_arial12b_98[] = {0x09, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x6e, 0x7f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x7f, 0x6e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // b 0x62 (98)
static u8 chr_arial12b_99[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x1e, 0x3f, 0x73, 0x60, 0x60, 0x60, 0x73, 0x3f, 0x1e, 0x00, 0x00, 0x00,
	0x00}; // c 0x63 (99)
static u8 chr_arial12b_100[] = {0x09, 0x11,
	0x00, 0x01, 0x01, 0x01, 0x1d, 0x3f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x3f, 0x1d, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // d 0x64 (100)
static u8 chr_arial12b_101[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x63, 0x7f, 0x7f, 0x60, 0x73, 0x3e, 0x1c, 0x00, 0x00, 0x00,
	0x00}; // e 0x65 (101)
static u8 chr_arial12b_102[] = {0x06, 0x11,
	0x00, 0x3c, 0x7c, 0x60, 0xf8, 0xf8, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // f 0x66 (102)
static u8 chr_arial12b_103[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x1d, 0x3f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x3f, 0x1d, 0x61, 0x7f, 0x3f,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x00, 0x00}; // g 0x67 (103)
static u8 chr_arial12b_104[] = {0x09, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x6f, 0x7f, 0x71, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // h 0x68 (104)
static u8 chr_arial12b_105[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // i 0x69 (105)
static u8 chr_arial12b_106[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0, 0xc0,
	0x00}; // j 0x6a (106)
static u8 chr_arial12b_107[] = {0x08, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x63, 0x66, 0x6c, 0x7c, 0x7c, 0x76, 0x66, 0x63, 0x63, 0x00, 0x00, 0x00,
	0x00}; // k 0x6b (107)
static u8 chr_arial12b_108[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // l 0x6c (108)
static u8 chr_arial12b_109[] = {0x0d, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x6e, 0x7f, 0x73, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0xf8, 0x98, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00,
	0x00, 0x00}; // m 0x6d (109)
static u8 chr_arial12b_110[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x6f, 0x7f, 0x71, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // n 0x6e (110)
static u8 chr_arial12b_111[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x1e, 0x3f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x3f, 0x1e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // o 0x6f (111)
static u8 chr_arial12b_112[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x6e, 0x7f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x7f, 0x6e, 0x60, 0x60, 0x60,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // p 0x70 (112)
static u8 chr_arial12b_113[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x1d, 0x3f, 0x73, 0x61, 0x61, 0x61, 0x73, 0x3f, 0x1d, 0x01, 0x01, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x00}; // q 0x71 (113)
static u8 chr_arial12b_114[] = {0x06, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x6c, 0x7c, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00,
	0x00}; // r 0x72 (114)
static u8 chr_arial12b_115[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x3e, 0x7f, 0x63, 0x78, 0x3e, 0x0f, 0x63, 0x7f, 0x3e, 0x00, 0x00, 0x00,
	0x00}; // s 0x73 (115)
static u8 chr_arial12b_116[] = {0x05, 0x11,
	0x00, 0x20, 0x60, 0x60, 0xf8, 0xf8, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x38, 0x00, 0x00, 0x00,
	0x00}; // t 0x74 (116)
static u8 chr_arial12b_117[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x63, 0x7f, 0x3d, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
	0x00, 0x00}; // u 0x75 (117)
static u8 chr_arial12b_118[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x36, 0x36, 0x36, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00,
	0x00}; // v 0x76 (118)
static u8 chr_arial12b_119[] = {0x0d, 0x11,
	0x00, 0x00, 0x00, 0x00, 0xc7, 0xc7, 0x67, 0x6d, 0x6d, 0x6d, 0x38, 0x38, 0x38, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0xb0, 0xb0, 0xb0, 0xe0, 0xe0, 0xe0, 0x00, 0x00,
	0x00, 0x00}; // w 0x77 (119)
static u8 chr_arial12b_120[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x63, 0x77, 0x36, 0x1c, 0x1c, 0x1c, 0x36, 0x77, 0x63, 0x00, 0x00, 0x00,
	0x00}; // x 0x78 (120)
static u8 chr_arial12b_121[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0x63, 0x63, 0x36, 0x36, 0x3e, 0x1c, 0x1c, 0x18, 0x78, 0x70,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // y 0x79 (121)
static u8 chr_arial12b_122[] = {0x08, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x06, 0x0e, 0x1c, 0x38, 0x30, 0x7f, 0x7f, 0x00, 0x00, 0x00,
	0x00}; // z 0x7a (122)
static u8 chr_arial12b_123[] = {0x03, 0x11,
	0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
	0x00}; // { 0x7b (123)
static u8 chr_arial12b_124[] = {0x06, 0x11,
	0x00, 0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x1c, 0x1c, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xe0,
	0x00}; // | 0x7c (124)
static u8 chr_arial12b_125[] = {0x09, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x7f, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00}; // } 0x7d (125)
static u8 chr_arial12b_126[] = {0x04, 0x11,
	0x00, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00,
	0x00}; // ~ 0x7e (126)

static u8 *font_arial12b[] = {chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_33, chr_arial12b_34, chr_arial12b_35, chr_arial12b_36, chr_arial12b_37, chr_arial12b_38, chr_arial12b_39,
	chr_arial12b_40, chr_arial12b_41, chr_arial12b_42, chr_arial12b_43, chr_arial12b_44, chr_arial12b_45, chr_arial12b_46, chr_arial12b_47, chr_arial12b_48, chr_arial12b_49,
	chr_arial12b_50, chr_arial12b_51, chr_arial12b_52, chr_arial12b_53, chr_arial12b_54, chr_arial12b_55, chr_arial12b_56, chr_arial12b_57, chr_arial12b_58, chr_arial12b_59,
	chr_arial12b_60, chr_arial12b_61, chr_arial12b_62, chr_arial12b_63, chr_arial12b_64, chr_arial12b_65, chr_arial12b_66, chr_arial12b_67, chr_arial12b_68, chr_arial12b_69,
	chr_arial12b_70, chr_arial12b_71, chr_arial12b_72, chr_arial12b_73, chr_arial12b_74, chr_arial12b_75, chr_arial12b_76, chr_arial12b_77, chr_arial12b_78, chr_arial12b_79,
	chr_arial12b_80, chr_arial12b_81, chr_arial12b_82, chr_arial12b_83, chr_arial12b_84, chr_arial12b_85, chr_arial12b_86, chr_arial12b_87, chr_arial12b_88, chr_arial12b_89,
	chr_arial12b_90, chr_arial12b_91, chr_arial12b_92, chr_arial12b_93, chr_arial12b_94, chr_arial12b_95, chr_arial12b_96, chr_arial12b_97, chr_arial12b_98, chr_arial12b_99,
	chr_arial12b_100, chr_arial12b_101, chr_arial12b_102, chr_arial12b_103, chr_arial12b_104, chr_arial12b_105, chr_arial12b_106, chr_arial12b_107, chr_arial12b_108, chr_arial12b_109,
	chr_arial12b_110, chr_arial12b_111, chr_arial12b_112, chr_arial12b_113, chr_arial12b_114, chr_arial12b_115, chr_arial12b_116, chr_arial12b_117, chr_arial12b_118, chr_arial12b_119,
	chr_arial12b_120, chr_arial12b_121, chr_arial12b_122, chr_arial12b_123, chr_arial12b_124, chr_arial12b_125, chr_arial12b_126, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank,
	chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank, chr_arial12b_blank};

u8* getArial12ptBPtr() {
	return font_arial12b;
}
