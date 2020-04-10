#include <ui/glib.h>
#include <globals.h>
#include <drivers/UC1608X_driver.h>
#include <ui/fonts.h>

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

/* Display icon by ID */
void gl_displayIcon(u8 icon_id) {

}





