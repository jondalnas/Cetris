#include "render.h"

#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "draw.h"

#ifdef _WIN32
const unsigned int _NONE		= 0x20; //Space
const unsigned int _BORDER_V  	= 0xBA; //Box
const unsigned int _BORDER_H  	= 0xCD; //Box
const unsigned int _BORDER_UR 	= 0xBB; //Box
const unsigned int _BORDER_UL 	= 0xC9; //Box
const unsigned int _BORDER_DR 	= 0xBC; //Box
const unsigned int _BORDER_DL 	= 0xC8; //Box
const unsigned int _BLOCK 		= 0xDB; //Block
const unsigned int _GRID_H 		= 0x7C; //Pipe
const unsigned int _GRID_V 		= 0x2D; //Dash
const unsigned int _GRID_C 		= 0x2B; //Plus
#else
/* const unsigned int _NONE		= 0x20; //Space */
/* const unsigned int _BORDER_V  	= 0x2551; //Box */
/* const unsigned int _BORDER_H  	= 0x2550; //Box */
/* const unsigned int _BORDER_UR 	= 0x255A; //Box */
/* const unsigned int _BORDER_UL 	= 0x255D; //Box */
/* const unsigned int _BORDER_DR 	= 0x2554; //Box */
/* const unsigned int _BORDER_DL 	= 0x2557; //Box */
/* const unsigned int _BLOCK 		= 0x2588; //Block */
/* const unsigned int _GRID_H 		= 0x7C; //Pipe */
/* const unsigned int _GRID_V 		= 0x2D; //Dash */
/* const unsigned int _GRID_C 		= 0x2B; //Plus */

const unsigned int _NONE		= 0x20; //Space
const unsigned int _BORDER_V  	= '|'; //Box
const unsigned int _BORDER_H  	= '-'; //Box
const unsigned int _BORDER_UR 	= '+'; //Box
const unsigned int _BORDER_UL 	= '+'; //Box
const unsigned int _BORDER_DR 	= '+'; //Box
const unsigned int _BORDER_DL 	= '+'; //Box
const unsigned int _BLOCK 		= 'o'; //Block
const unsigned int _GRID_H 		= 0x7C; //Pipe
const unsigned int _GRID_V 		= 0x2D; //Dash
const unsigned int _GRID_C 		= 0x2B; //Plus
#endif

#define MAX_LINE_LENGTH SCREEN_WIDTH

uint32_t _border_char(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	if (x == 0) {
		if (y == 0)
			return _BORDER_DR;
		else if (y == height - 1)
			return _BORDER_UR;
		else
			return  _BORDER_V;
	} else if (x == width - 1) {
		if (y == 0)
			return _BORDER_DL;
		else if (y == height - 1)
			return _BORDER_UL;
		else
			return  _BORDER_V;
	} else {
		if (y == 0 || y == height - 1)
			return _BORDER_H;
		else
			return 0;
	}
}

void draw_borders(uint32_t fill, uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint8_t xx, yy;

	for (yy = 0; yy < height; yy++) {
		move_cursor(x, y + yy);
		for (xx = 0; xx < width; xx++) {
			if (xx == 0 || yy == 0 || xx == width - 1 || yy == height - 1) {
				draw_utf8_char(_border_char(xx, yy, width, height));
				continue;
			}
			
			draw_utf8_char(fill);
		}
	}

	draw_flush();
}

void draw_grid(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
	uint8_t xx, yy;

	for (yy = 0; yy < height; yy++) {
		move_cursor(x, y + yy);
		for (xx = 0; xx < width; xx++) {
			draw_char('+');
		}
	}

	draw_flush();
}

void draw_piece(const uint16_t *piece, uint8_t x, uint8_t y, uint8_t width, uint8_t rot) {
	uint8_t i;

	uint8_t xx, yy;

	uint16_t pixels = piece[rot];

	x += 1;
	y += 1;

	for (i = 0; i < 4; i++) {
		xx = pixels & 3;
		yy = (pixels >> 2) & 3;

		move_cursor(xx + x, yy + y);
		draw_utf8_char(_BLOCK);

		pixels >>= 4;
	}

	draw_flush();
}

void draw_stack(uint32_t *stack, uint32_t fill, uint8_t width, uint8_t height) {
	uint8_t x, y;

	for (y = 0; y < height; y++) {
		move_cursor(1, y + 1);
		for (x = 0; x < width; x++) {
			if ((stack[y] >> x) & 1)
				draw_utf8_char(_BLOCK);
			else
				draw_utf8_char(fill);
		}
	}

	draw_flush();
}

void clear_screen() {
	cls();
}

void clear_piece(const uint16_t *piece, uint32_t fill, uint8_t x, uint8_t y, uint8_t width, uint8_t rot) {
	uint8_t i;

	uint8_t xx, yy;

	uint16_t pixels = piece[rot];

	x += 1;
	y += 1;

	for (i = 0; i < 4; i++) {
		xx = pixels & 3;
		yy = (pixels >> 2) & 3;

		move_cursor(xx + x, yy + y);
		draw_utf8_char(fill);

		pixels >>= 4;
	}

	draw_flush();
}
