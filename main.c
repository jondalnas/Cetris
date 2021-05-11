#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#include <stdio.h>

#include <stdlib.h>
#include "piece.h"
#include "input.h"

#define SLEEP 16
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20
#define BORDER_WIDTH 20 

unsigned short collision(const piece_t* piece_p, char index, char x, char y) {
	unsigned short pieceData = *(&piece_p->tile0 + index);

	unsigned short col = 0; //4x4 collision square, at piece x, y coordinate
	if (x < 0) {
		if (x == -1) col |= 0x1111;
		else if (x == -2) col |= 0x3333;
		else if (x == -3) col |= 0x7777;
		else if (x == -4) col |= 0xFFFF;
	} else if (x > BORDER_WIDTH - 6) {
		if (x == SCREEN_HEIGHT - 5) col |= 0x8888;
		else if (x == SCREEN_HEIGHT - 4) col |= 0xCCCC;
		else if (x == SCREEN_HEIGHT - 3) col |= 0xEEEE;
		else if (x == SCREEN_HEIGHT - 2) col |= 0xFFFF;
	}

	if (y > SCREEN_HEIGHT - 6) {
		if (y == SCREEN_HEIGHT - 5) col |= 0xF000;
		else if (y == SCREEN_HEIGHT - 4) col |= 0xFF00;
		else if (y == SCREEN_HEIGHT - 3) col |= 0xFFF0;
		else if (y >= SCREEN_HEIGHT - 2) col |= 0xFFFF;
	}

	return pieceData & col;
}

int main() {
	//Input
	HANDLE inputThread = CreateThread(NULL, 0, inputLoop, NULL, 0, NULL);

	grid_t* screen_p = createNewGrid(SCREEN_WIDTH, SCREEN_HEIGHT);
	grid_t* border_p = createNewGrid(BORDER_WIDTH, SCREEN_HEIGHT);
	
	drawBoxChar(border_p, _NONE, 0, 0, BORDER_WIDTH, SCREEN_HEIGHT);

	char x = BORDER_WIDTH / 2 - 2;
	char y = 0;
	int rot = 0;

	float dx = 0;
	float dy = 0;

	const piece_t* currPice_p = &L_PIECE;
	
	grid_t* currPiceGrid_p[4]; //Maybe make pieceToGrid retun array of all rotations
	currPiceGrid_p[0] = pieceToGrid(currPice_p, 0);
	currPiceGrid_p[1] = pieceToGrid(currPice_p, 1);
	currPiceGrid_p[2] = pieceToGrid(currPice_p, 2);
	currPiceGrid_p[3] = pieceToGrid(currPice_p, 3);

	while (1) {
		clearScreen(screen_p);
		drawGrid(screen_p, border_p, (SCREEN_WIDTH - BORDER_WIDTH) / 2, 0);

		//Game logic
		//Gravity
		dy += 0.1;

		//Input
		char arrow;
		if ((arrow = getArrowDown()) != -1) {
			switch(arrow) {
				case 72:;//UP
					int newRot = (rot + 1) & 0x03;

					if (!collision(currPice_p, newRot, x, y)) {
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
		if (dy > 1) {
			dy--;

			if (!collision(currPice_p, rot, x, y + 1)) {
				y++;
			}
		} else if (dy < 0) {
			dy++;

			if (!collision(currPice_p, rot, x, y - 1)) {
				y--;
			}
		}

		if (dx > 1) {
			dx--;

			if (!collision(currPice_p, rot, x + 1, y)) {
				x++;
			}
		} else if (dx < 0) {
			dx++;

			if (!collision(currPice_p, rot, x - 1, y)) {
				x--;
			}
		}

		drawGrid(screen_p, currPiceGrid_p[rot], x + (SCREEN_WIDTH - BORDER_WIDTH) / 2 + 1, y+1);

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
	for (int i = 0; i < 4; i++) free(currPiceGrid_p[i]);
}