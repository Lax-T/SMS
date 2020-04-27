#include <ui/glib.h>
#include <globals.h>
#include <drivers/UC1608X_driver.h>
#include <ui/fonts.h>
#include <math.h>
#include <stdlib.h>
#include "ui/icons.h"

#define PAGE_SIZE 8

struct Cursor {
	u8 x, y;
};

u8 g_graphic_buffer[LCD_TOTAL_PAGES][LCD_TOTAL_COLUMNS] = {};
struct Cursor g_cursor = {0, 0};

/* Clear LCD buffer array. */
void gl_clearBuffer() {
	u8 i, j;

	for (i=0; i < LCD_TOTAL_PAGES; i++) {
		for (j=0; j < LCD_TOTAL_COLUMNS; j++) {
				g_graphic_buffer[i][j] = 0;
		}
	}
}

/* Refresh GLCD (write entire memory) */
void gl_refreshLCD() {
	uc_writeFullBuffer(g_graphic_buffer);
}

/* Set cursor position. (zero point for tile merge and draw operations) */
void gl_setCursor(u8 x, u8 y) {
	g_cursor.x = x;
	g_cursor.y = y;
}

/* Merge (OR operation) tile to graphic buffer. */
void gl_mergeTile(u8 tile[]) {
	u8 tile_pages, tile_cols, page, col, page_offset, i, j, temp;
	/* First 2 bytes contain info about tile size. */
	tile_pages = tile[0] / PAGE_SIZE;
	if ((tile[0] % PAGE_SIZE) > 0) {
		tile_pages++;
	}
	tile_cols = tile[1];
	/* Calculate page and page offset */
	page = g_cursor.x / PAGE_SIZE;
	page_offset = g_cursor.x - (page * PAGE_SIZE);
	/* Iterate */
	for (i=0; i < tile_pages; i++) {
		/* Pages loop */
		/* Terminate loop if out of buffer range */
		if ((page + i) >= GLCD_PAGES) {
			break;
		}
		for (j=0; j < tile_cols; j++) {
			/* Columns loop */
			/* Set column n */
			col = g_cursor.y + j;
			/* Terminate loop if out of buffer range */
			if (col >= GLCD_COLUMNS) {
				break;
			}
			/* Get text tile byte */
			temp = tile[(i * tile_cols) + j + 2]; // Add 2 offset because first 2 bytes hold info about tile size
			if (page_offset == 0){ // If tile page is aligned
				g_graphic_buffer[page + i][col] |= temp;
			}
			else { // If tile page is NOT aligned
				g_graphic_buffer[page + i][col] |= temp >> page_offset;
				/* Check, if we will move right one more page, won't we be out of range ? */
				if ((page + i + 1) < GLCD_PAGES) {
					g_graphic_buffer[page + i + 1][col] |= temp << (PAGE_SIZE - page_offset);
				}
			}
		}
	}
}

void gl_drawHLine (u8 line_width, u8 line_len) {
	u8 page, page_offset, col, bits, i;
	/* Calculate page and page offset */
	page = g_cursor.x / PAGE_SIZE;
	page_offset = g_cursor.x - (page * PAGE_SIZE);
	/* Store current column value. */
	col = g_cursor.y;
	/* Draw in cycle until line_len is zero. With each iteration (draw cycle) this value is subtracted. */
	while(line_len > 0) {
		/* Calculate what and how many bits should be set for next iteration. */
		bits = 0xFF;
		/* If less than 8 bits need to be draw - clear some bits. */
		if (line_len < 8) {
			bits = bits << (8 - line_len);
		}
		/* Check current page offset. */
		if (page_offset != 0) {
			/* Shift bits to match x offset. */
			bits = bits >> page_offset;
			/* Track how many bits will be actually set due to offset. */
			if (line_len < (8 - page_offset)) {
				/* If offset is bigger than current line length, than all bits will be drown in this iteration. */
				line_len = 0;
			}
			else {
				line_len = line_len - (8 - page_offset);
			}
		}
		else {
			/* If offset does not have to be accounted - simply track up to 8 dots set; */
			if (line_len < 8) {
				line_len = 0;
			}
			else {
				line_len = line_len - 8;
			}
		}
		/* Page offset is only needed for first iteration */
		page_offset = 0;
		/* Depending on line width, merge bits with required number of columns. */
		for (i=0;i < line_width; i++) {
			/* Terminate loop if out of buffer range */
			if ((col + i) >= GLCD_COLUMNS) {
				break;
			}
			/* Draw in buffer */
			g_graphic_buffer[page][col + i] |= bits;
		}
		/* Go to next page. */
		page++;
		/* If OOR - finish line draw. */
		if (page >= GLCD_PAGES) {
			break;
		}
	}
}

/* Print string starting with current cursor position. */
void gl_printString(u8 *string, u8 font_id) {
	u8 i, cursor_future_pos;
	u8* tile;
	char chr;
	/* Get font */
	u8 char_offset = fnt_getCharSpacing(font_id);
	u8** font = fnt_getFont(font_id);

	for (i = 0; i < 32; i++ ) {
		chr = string[i];
		/* If end of string (0) - break */
		if (chr == 0) {
			break;
		}
		/* Get tile */
		tile = font[chr];
		/* Check if there is a place for next tile */
		if ((g_cursor.x + tile[0]) >= LCD_TOTAL_ROWS) {
			break;
		}
		/* Merge tile */
		gl_mergeTile(tile);
		/* Try to shift cursor */
		cursor_future_pos = g_cursor.x + tile[0] + char_offset;
		if (cursor_future_pos < LCD_TOTAL_ROWS) {
			gl_setCursor(cursor_future_pos, g_cursor.y);
		}
		/* If next cursor position if out of range, set to screen end and exit */
		else {
			gl_setCursor(LCD_TOTAL_ROWS - 1, g_cursor.y);
			return;
		}
	}
}

void gl_printTileRShift(u8 *tile, u8 char_offset) {
	u8 cursor_future_pos;

	/* Check if there is a place for next tile */
	if ((g_cursor.x + tile[0]) >= LCD_TOTAL_ROWS) {
		return;
	}
	/* Merge tile */
	gl_mergeTile(tile);
	/* Try to shift cursor */
	cursor_future_pos = g_cursor.x + tile[0] + char_offset;
	if (cursor_future_pos < LCD_TOTAL_ROWS) {
		gl_setCursor(cursor_future_pos, g_cursor.y);
	}
	/* If next cursor position if out of range, set to screen end and exit */
	else {
		gl_setCursor(LCD_TOTAL_ROWS - 1, g_cursor.y);
	}
}

static u32 pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};

/* Format string with char/short/float and print starting from current cursor position.
 * Formatting syntax: %[flags][width][.precision]specifier
 * flags: (space) - blank space instead of minus sign, | - always omit minus sign, 0 - print zeros if width is specified
 * width: minimum number of characters to be printed (spaces or zeros)
 * precision: number of characters printed after a decimal point (default 2)
 * specifier: uc - u_8, sc - s_8, us - u_16, ss - s_16, ui - u_32, si - s_32, f - float
 * */
void gl_printFString(char *string, void *val, u8 font_id) {
	u8 i, cursor_future_pos;
	u8* tile;
	char chr;
	/* Get font */
	u8 char_offset = fnt_getCharSpacing(font_id);
	u8** font = fnt_getFont(font_id);
	/* Formatting specific variables */
	u8 is_zpadding = 0;
	u8 minus = 0; // 0 - default, 1 - keep space, 2 - ignore minus sign
	u8 width = 0;
	u8 precision = 0;
	u8 parsing_step = 0; // 0 - flags, 1 - width, 2 - precision
	u8 n_digits = 0; // Number of digits for a given number

	for (i = 0; i < 32; i++ ) { // TODO: 32 is random limiter to protect thread from infinite loop, might be adjusted
		chr = string[i];
		/* If [%] symbol, start formatting decode. */
		if (chr == '%') {
			/* Immediately get next character */
			chr = string[++i];
			/* Always terminate if end of string */
			if (chr == 0) {
				break;
			}
			/* If duplicate "%" print and continue for loop*/
			if (chr == '%') {
				gl_printTileRShift(font['%'], char_offset);
				continue;
			}
			/* If something else, enter parsing loop */
			while(i < 32) {	// TODO: 32 is random limiter to protect thread from infinite loop, might be adjusted
				/* Search for specific characters depending on step */
				switch(parsing_step){
				case 0:
					if (chr == ' ') {
						minus = 1; // Print minus or space
					} else if (chr == '|') {
						minus = 2; // Ignore minus sign
					} else if (chr == '0') {
						is_zpadding = 1; // Zero padding is true
					}  else if (chr >= '1' && chr <= '9') {
						width = chr - '0'; // Calculate width (subtract zero character offset)
						parsing_step = 1; // Go to width parsing step
					} else if (chr == '.') {
						parsing_step = 2; // Go to precision parsing step
					}
					break;

				case 1:
					/* If number again, than assumed that this is second width digit */
					if (chr >= '1' && chr <= '9') {
						/* If width is already more than 10, ignore all next digits. */
						if (width >= 10) {
							break;
						}
						width = (width * 10) + (chr - '0'); // Calculate width
					} else if (chr == '.') {
						parsing_step = 2; // Go to precision parsing step
					}
					break;

				case 2:
					if (chr >= '1' && chr <= '9') {
						/* If precision is zero, assume that this is a first number */
						if (precision == 0) {
							precision = chr - '0';
						}
						/* If precision is more than zero and less than 10, assume that this is a second digit.*/
						else if (precision > 0 && precision < 10) {
							precision = (precision * 10) + (chr - '0');
						}
						/* If precision is already more than 10, ignore all next digits. */
						else if (precision >= 10) {
							break;
						}
					}
					break;
				}

				/* Look for specifier. */
				if (chr == 'f') {
					/* If not defined, set precision to: 2 */
					if (precision == 0) {
						precision = 2;
					}
					/* Create float variable. */
					float n = *((float*)val);
					u32 n_copy = (u32)fabs(n);
					/* Calculate number of digits to be displayed. */
					if (n_copy == 0) {
						n_digits++;
					}
					while (n_copy != 0) {
						n_digits++;
						n_copy /= 10;
					}
					/* Handle minus sign */
					if (n < 0 && minus == 0 && width > 0) { // If lower than zero and minus sign is not ignored
						width--;
					} else if (minus == 1 && width > 0) { // If space placeholder enabled
						width--;
					}
					/* Handle minus */
					if (is_zpadding == 1 || width <= n_digits) {
						/* If z padding, place minus sign/space first */
						if (n < 0 && minus < 2) {
							gl_printTileRShift(font['-'], char_offset); // Print minus sign
						} else if (minus == 1) {
							gl_printTileRShift(font[' '], char_offset); // Print space
						}
					}
					/* If minimum width is defined and/or lower than expected len, make zero/space padding */
					if (width > (n_digits + 1 + precision)) { // +1 because dot character should also be included
						if (is_zpadding == 1) {
							/* Print zeros till with equalizes */
							while (width > (n_digits + 1 + precision)) { // +1 because dot character should also be included
								gl_printTileRShift(font['0'], char_offset);
								width--;
							}
						} else {
							/* If not z padding, print required number of spaces */
							while (width > (n_digits + 1 + precision)) { // +1 because dot character should also be included
								gl_printTileRShift(font[' '], char_offset);
								width--;
							}
							/* Than handle minus sign/space */
							if (n < 0 && minus < 2) {
								gl_printTileRShift(font['-'], char_offset); // Print minus sign
							} else if (minus == 1) {
								gl_printTileRShift(font[' '], char_offset); // Print space
							}
						}
					}
					/* Handle decimal number part */
					if (n_digits > 0) {
						n_copy = (u32)fabs(n);
						while (n_digits > 0) {
							n_digits--;
							gl_printTileRShift(font['0' + (n_copy / pow10[n_digits])], char_offset); // Print required number by offset 'zero' character
							n_copy %= pow10[n_digits];
						}
					} else {
						gl_printTileRShift(font['0'], char_offset);
					}
					/* Dot */
					gl_printTileRShift(font['.'], char_offset);
					/* Handle fraction part */
					n = fabs(n);
					while (precision > 0) {
						precision--;
						n = n - (u32)n; // Leave only fractional part
						n *= 10;
						gl_printTileRShift(font['0' + (u8)n], char_offset);
					}
					/* Formatting done. Get next char, end while loop */
					chr = string[++i];
					break;

				} else if (chr == 'u') {
					/* Create unsigned int variable */
					u32 n, n_copy;
					/* Get next char to determine actual type */
					chr = string[++i];
					/* Always terminate if end of string */
					if (chr == 0) {
						break;
					}
					/* Determine type and dereference */
					if (chr == 'c') {
						n = (u32)(*((unsigned char*)val));
					} else if (chr == 's') {
						n = (u32)(*((unsigned short*)val));
					} else if (chr == 'i') {
						n = *((unsigned int*)val);
					} else {
						/* Invalid specifier, break! */
						break;
					}
					n_copy = n;
					/* Calculate number of digits to be displayed. */
					if (n_copy == 0) {
						n_digits++;
					}
					while (n_copy != 0) {
						n_digits++;
						n_copy /= 10;
					}

					/* If minimum width is defined and/or lower than expected len, make zero/space padding */
					if (width > n_digits) {
						if (is_zpadding == 1) {
							/* Print zeros till with equalizes */
							while (width > n_digits) { // +1 because dot character should also be included
								gl_printTileRShift(font['0'], char_offset);
								width--;
							}
						} else {
							/* If not z padding, print required number of spaces */
							while (width > n_digits) { // +1 because dot character should also be included
								gl_printTileRShift(font[' '], char_offset);
								width--;
							}
						}
					}
					/* Handle number  */
					if (n_digits > 0) {
						n_copy = n;
						while (n_digits > 0) {
							n_digits--;
							gl_printTileRShift(font['0' + (n_copy / pow10[n_digits])], char_offset); // Print required number by offset 'zero' character
							n_copy %= pow10[n_digits];
						}
					} else {
						gl_printTileRShift(font['0'], char_offset);
					}
					/* Formatting done. Get next char, end while loop */
					chr = string[++i];
					break;

				} else if (chr == 's') {
					/* Create signed int variable */
					s32 n, n_copy;
					/* Get next char to determine actual type */
					chr = string[++i];
					/* Always terminate if end of string */
					if (chr == 0) {
						break;
					}
					/* Determine type and dereference */
					if (chr == 'c') {
						n = (s32)(*((signed char*)val));
					} else if (chr == 's') {
						n = (s32)(*((signed short*)val));
					} else if (chr == 'i') {
						n = *((signed int*)val);
					} else {
						/* Invalid specifier, break! */
						break;
					}
					n_copy = n;
					/* Calculate number of digits to be displayed. */
					if (n_copy == 0) {
						n_digits++;
					}
					while (n_copy != 0) {
						n_digits++;
						n_copy /= 10;
					}

					/* Handle minus sign */
					if (n < 0 && minus == 0 && width > 0) { // If lower than zero and minus sign is not ignored
						width--;
					} else if (minus == 1 && width > 0) { // If space placeholder enabled
						width--;
					}
					/* Handle minus */
					if (is_zpadding == 1 || width <= n_digits) {
						/* If z padding, place minus sign/space first */
						if (n < 0 && minus < 2) {
							gl_printTileRShift(font['-'], char_offset); // Print minus sign
						} else if (minus == 1) {
							gl_printTileRShift(font[' '], char_offset); // Print space
						}
					}
					/* If minimum width is defined and/or lower than expected len, make zero/space padding */
					if (width > n_digits) {
						if (is_zpadding == 1) {
							/* Print zeros till with equalizes */
							while (width > n_digits) { // +1 because dot character should also be included
								gl_printTileRShift(font['0'], char_offset);
								width--;
							}
						} else {
							/* If not z padding, print required number of spaces */
							while (width > n_digits) { // +1 because dot character should also be included
								gl_printTileRShift(font[' '], char_offset);
								width--;
							}
							/* Than handle minus sign/space */
							if (n < 0 && minus < 2) {
								gl_printTileRShift(font['-'], char_offset); // Print minus sign
							} else if (minus == 1) {
								gl_printTileRShift(font[' '], char_offset); // Print space
							}
						}
					}
					/* Handle number  */
					if (n_digits > 0) {
						n_copy = abs(n);
						while (n_digits > 0) {
							n_digits--;
							gl_printTileRShift(font['0' + (n_copy / pow10[n_digits])], char_offset); // Print required number by offset 'zero' character
							n_copy %= pow10[n_digits];
						}
					} else {
						gl_printTileRShift(font['0'], char_offset);
					}
					/* Formatting done. Get next char, end while loop */
					chr = string[++i];
					break;
				}

				chr = string[++i];
				/* Always terminate if end of string */
				if (chr == 0) {
					break;
				}
			}
		}

		/* If end of string (0) - break */
		if (chr == 0) {
			break;
		}

		/* Get tile */
		tile = font[chr];
		gl_printTileRShift(tile, char_offset);
	}
}

/* Display icon by ID */
void gl_displayIcon(u8 icon_id) {
	gl_mergeTile(ico_getIcon(icon_id));
}





