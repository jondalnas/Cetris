#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

const char _NONE		= 0x20; //Space
const char _BORDER_V  	= 0xBA; //Box
const char _BORDER_H  	= 0xCD; //Box
const char _BORDER_UR 	= 0xBB; //Box
const char _BORDER_UL 	= 0xC9; //Box
const char _BORDER_DR 	= 0xBC; //Box
const char _BORDER_DL 	= 0xC8; //Box
const char _BLOCK 		= 0xDB; //Block
const char _GRID 		= 0x2A; //Star

grid_t* createNewGrid(char width, char height) {
	grid_t* grid_p = (grid_t*) malloc(sizeof(grid_t));
	if (grid_p == NULL) {
		puts("Memmory for grid could not be allocated");
		return NULL;
	}
	grid_p->width = width;
	grid_p->height = height;

	grid_p->tiles_p = (tile_t*) malloc(width * height * sizeof(tile_t));
	if (grid_p->tiles_p == NULL) {
		puts("Tile allocation could not be done");
		return NULL;
	}

	for (char y = 0; y < height; y++) {
		int yOffs = y * grid_p->width;
		for (char x = 0; x < width; x++) {
			tile_t* tile_p = grid_p->tiles_p + x + yOffs;
			tile_p->screenObj = _NONE;
			tile_p->x = x;
			tile_p->y = y;
		}
	}

	return grid_p;
}

void renderGrid(grid_t* grid_p) {
	char* line = (char*)malloc((grid_p->width + 1) * sizeof(char));
	*(line + grid_p->width) = 0; //Newline ascii code (this will never be overwritten)

	for (char y = 0; y < grid_p->height; y++) {
		int yOffs = y * grid_p->width;

		for (char x = 0; x < grid_p->width; x++) {
			tile_t* curr = grid_p->tiles_p + x + yOffs;
			*(line + x) = curr->screenObj;
		}

		printf(line);
		printf("\n");
	}

	free(line);
}

void drawGrid(grid_t* grid_p, grid_t* target, int x, int y) {
	for (char yy = 0; yy < target->height; yy++) {
		int y0 = yy + y;
		int yOffs = y0 * grid_p->width;

		if (y0 < 0 || y0 >= grid_p->height) continue;

		for (char xx = 0; xx < target->width; xx++) {
			int x0 = xx + x;
			
			if (x0 < 0 || x0 >= grid_p->width) continue;

			tile_t* dest = grid_p->tiles_p + x0 + yOffs;
			tile_t* targ = target->tiles_p + xx + yy * target->width;

			if (targ->screenObj == _NONE) continue;

			dest->screenObj = targ->screenObj;
		}
	}
}

void drawGridScale(grid_t* grid_p, grid_t* target, char scale, int x, int y) {
	for (char yy = 0; yy < target->height; yy++) {
		int y0 = yy + y;
		int yOffs = y0 * grid_p->width;

		if (y0 < 0 || y0 >= grid_p->height) continue;

		for (char xx = 0; xx < target->width; xx++) {

			tile_t* targ = target->tiles_p + xx + yy * target->width;

			if (targ->screenObj == _NONE) continue;

			for (int s = 0; s < scale; s++) {
				int x0 = xx * scale + x;
				
				if (x0 < 0 || x0 >= grid_p->width) continue;

				tile_t* dest = grid_p->tiles_p + x0 + s + yOffs;

				dest->screenObj = targ->screenObj;
			}
		}
	}
}

void drawBoxChar(grid_t* grid_p, char fill, int x, int y, int width, int height) {
	for (char yy = 0; yy < height; yy++) {
		int y0 = yy + y;
		int yOffs = y0 * grid_p->width;

		for (char xx = 0; xx < width; xx++) {
			int x0 = xx + x;

			tile_t* curr = grid_p->tiles_p + x0 + yOffs;
			
			if (xx % 2 == 1 || yy % 2 == 1) curr->screenObj = fill;
			else curr->screenObj = _NONE;

			if (xx == 0) {
				if (yy == 0) {
					curr->screenObj = _BORDER_UL;
				} else if (yy == height - 1) {
					curr->screenObj = _BORDER_DL;
				} else {
					curr->screenObj = _BORDER_V;
				}
			} else if (xx == width - 1) {
				if (yy == 0) {
					curr->screenObj = _BORDER_UR;

				} else if (yy == height - 1) {
					curr->screenObj = _BORDER_DR;
				} else {
					curr->screenObj = _BORDER_V;
				}
			} else {
				if (yy == 0 || yy == height - 1) {
					curr->screenObj = _BORDER_H;
				}
			}
		}
	}

	//(grid_p->tiles_p + 0 + (20 - 6) * grid_p->width)->screenObj = '1';
	//(grid_p->tiles_p + 0 + 10 * grid_p->width)->screenObj = 's';
}

void clearScreen(grid_t* screen_p) {
	system("cls");

	for (char y = 0; y < screen_p->height; y++) {
		int yOffs = y * screen_p->width;
		for (char x = 0; x < screen_p->width; x++) {
			(screen_p->tiles_p + x + yOffs)->screenObj = _NONE;
		}
	}
}