#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "piece.h"
#include "input.h"

#define SLEEP 16
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20
#define GAME_WIDTH 10 
#define GAME_HEIGHT SCREEN_HEIGHT - 2
#define WIDTH_SCALE 2 
#define BORDER_WIDTH (GAME_WIDTH + 1) * WIDTH_SCALE

#define ROW_WIDTH_BITMASK 0b1111111111

typedef struct {
	int* stack;
	grid_t* grid_p;
} stack_t;

unsigned short collision(const piece_t* piece_p, char index, stack_t* stack_p, char x, char y) {
	unsigned short pieceData = *(&piece_p->tile0 + index);

	unsigned short col = 0; //4x4 collision square, at piece x, y coordinate
	if (x < 0) {
		if (x == -1) col |= 0x1111;
		else if (x == -2) col |= 0x3333;
		else if (x == -3) col |= 0x7777;
		else if (x == -4) col |= 0xFFFF;
	} else if (x > GAME_WIDTH - 4) {
		if (x == GAME_WIDTH - 3) col |= 0x8888;
		else if (x == GAME_WIDTH - 2) col |= 0xCCCC;
		else if (x == GAME_WIDTH - 1) col |= 0xEEEE;
		else if (x == GAME_WIDTH) col |= 0xFFFF;
	}

	if (y > GAME_HEIGHT - 4) {
		if (y == GAME_HEIGHT - 3) col |= 0xF000;
		else if (y == GAME_HEIGHT - 2) col |= 0xFF00;
		else if (y == GAME_HEIGHT - 1) col |= 0xFFF0;
		else if (y >= GAME_HEIGHT) col |= 0xFFFF;
	}

	for (char yy = 0; yy < 4; yy++) {
		if (y + yy >= GAME_HEIGHT) break;

		for (char xx = 0; xx < 4; xx++) {
			if (x + xx >= GAME_WIDTH) break;
			if (x + xx < 0) continue;
			int* stackRow = stack_p->stack + y + yy;

			if ((*stackRow >> (x + xx)) & 1) {
				col |= 1 << (xx + yy * 4);
			}
		}
	}

	return pieceData & col;
}

int main() {
	srand(time(0));
	//Input
	HANDLE inputThread = CreateThread(NULL, 0, inputLoop, NULL, 0, NULL);

	grid_t* screen_p = createNewGrid(SCREEN_WIDTH, SCREEN_HEIGHT);
	grid_t* border_p = createNewGrid(BORDER_WIDTH, SCREEN_HEIGHT);
	
	drawBoxCharGrid(border_p, 0, 0, BORDER_WIDTH, SCREEN_HEIGHT);

	char x = GAME_WIDTH / 2 - 2;
	char y = 0;
	int rot = 0;

	char dx = 0;
	char dy = 0;

	char gravity = 10;

	const piece_t* currPice_p = &I_PIECE + rand() % 7;
	grid_t* currPiceGrid_p[4]; //Maybe make pieceToGrid retun array of all rotations
	currPiceGrid_p[0] = pieceToGrid(currPice_p, 0);
	currPiceGrid_p[1] = pieceToGrid(currPice_p, 1);
	currPiceGrid_p[2] = pieceToGrid(currPice_p, 2);
	currPiceGrid_p[3] = pieceToGrid(currPice_p, 3);

	stack_t stack = {(int*) calloc(GAME_HEIGHT, sizeof(int)), createNewGrid(GAME_WIDTH, GAME_HEIGHT)};

	while (!getExitGame()) {
		clearScreen(screen_p);
		drawGrid(screen_p, border_p, (SCREEN_WIDTH - BORDER_WIDTH) / 2, 0);

		//Game logic
		//Gravity
		dy += 1;

		//Input
		char arrow;
		if ((arrow = getArrowDown()) != -1) {
			switch(arrow) {
				case 72:;//UP
					int newRot = (rot + 1) & 0x03;

					if (!collision(currPice_p, newRot, &stack, x, y)) {
						rot = newRot;
					}
					break;
				case 80://DOWN
					break;
				case 75://LEFT
					dx--;
					break;
				case 77://RIGHT
					dx++;
					break;
			}
		}

		//Calculating x and y
		if (dy > gravity) {
			if (!collision(currPice_p, rot, &stack, x, y + 1)) {
				dy = 0;
				y++;
			} else if (dy > gravity * 6) {
				//Piece stuck
				drawGrid(stack.grid_p, currPiceGrid_p[rot], x, y);
				
				unsigned short pieceData = *(&currPice_p->tile0 + rot);

				for (char yy = 0; yy < 4; yy++) {
					for (char xx = 0; xx < 4; xx++) {
						int* stackRow = stack.stack + yy + y;

						if (pieceData & 1) *stackRow |= 1 << (x + xx);

						pieceData >>= 1;
					}
				}

				x = GAME_WIDTH / 2 - 2;
				y = rot = dx = dy = 0;

				for (int i = 0; i < 4; i++) free(currPiceGrid_p[i]);

				currPice_p = &I_PIECE + rand() % 7;
				currPiceGrid_p[0] = pieceToGrid(currPice_p, 0);
				currPiceGrid_p[1] = pieceToGrid(currPice_p, 1);
				currPiceGrid_p[2] = pieceToGrid(currPice_p, 2);
				currPiceGrid_p[3] = pieceToGrid(currPice_p, 3);

				//Clear line
				for (char y = 0; y < GAME_HEIGHT; y++) {
					int line = *(stack.stack + y);

					if ((line & ROW_WIDTH_BITMASK) != ROW_WIDTH_BITMASK) continue;

					*(stack.stack + y) = 0;
					for (char x = 0; x < GAME_WIDTH; x++) {
						(stack.grid_p->tiles_p + x + y * GAME_WIDTH)->screenObj = _NONE;
					}

					for (char yy = y - 1; yy >= 0; yy--) {
						*(stack.stack + yy + 1) = *(stack.stack + yy);

						for (char x = 0; x < GAME_WIDTH; x++) {
							(stack.grid_p->tiles_p + x + (yy + 1) * GAME_WIDTH)->screenObj = (stack.grid_p->tiles_p + x + yy * GAME_WIDTH)->screenObj;
						}
					}
				}
			}
		}

		if (dx > 1) {
			dx--;

			if (!collision(currPice_p, rot, &stack, x + 1, y)) {
				x++;
			}
		} else if (dx < 0) {
			dx++;

			if (!collision(currPice_p, rot, &stack, x - 1, y)) {
				x--;
			}
		}

		drawGridScale(screen_p, stack.grid_p, WIDTH_SCALE, (SCREEN_WIDTH - BORDER_WIDTH) / 2 + 1, 1);
		drawGridScale(screen_p, currPiceGrid_p[rot], WIDTH_SCALE, x * WIDTH_SCALE + (SCREEN_WIDTH - BORDER_WIDTH) / 2 + 1, y+1);

		renderGrid(screen_p);

		#ifdef _WIN32
			Sleep(SLEEP);
		#else
			sleep(SLEEP / 1000.0);
		#endif
	}

	CloseHandle(inputThread);
	free(screen_p);
	free(border_p);
	free(stack.grid_p);
	free(stack.stack);
	for (int i = 0; i < 4; i++) free(currPiceGrid_p[i]);
}