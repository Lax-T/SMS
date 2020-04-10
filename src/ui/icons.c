#include <ui/icons.h>

static u8 ico_degre_c15[] = {0x0f, 0x0f,
	0x78, 0xcc, 0xcc, 0xcc, 0xcd, 0x79, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0xfe, 0xc6, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc6, 0xfe, 0x7c}; // Degree celsius sign 15px


static u8 *icons[] = {ico_degre_c15};

u8* ico_getIcon(u8 icon_id) {
	return icons[icon_id];
}
