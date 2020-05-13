#include <globals.h>

#define LCD_TOTAL_PAGES 16
#define LCD_TOTAL_ROWS 128
#define LCD_TOTAL_COLUMNS 240

void gl_clearBuffer();
void gl_refreshLCD();
void gl_setCursor(u8 x, u8 y);
void gl_mergeTile(u8 tile[]);
void gl_printString(char *string, u8 font_id);
void gl_drawHLine (u8 line_width, u8 line_len);
void gl_printFString(char *string, void *val, u8 font_id);
void gl_displayIcon(u8 icon_id);
