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

int main() {
	//Input
	HANDLE inputThread = CreateThread(NULL, 0, inputLoop, NULL, 0, NULL);

	grid_t* screen_p = createNewGrid(SCREEN_WIDTH, SCREEN_HEIGHT);
	grid_t* border_p = createNewGrid(BORDER_WIDTH, SCREEN_HEIGHT);
	grid_t* i_p = pieceToGrid(&L_PIECE, 2);
	
	drawBoxChar(border_p, _NONE, 0, 0, BORDER_WIDTH, SCREEN_HEIGHT);

	char x = 0;
	char y = 0;

	float dx = 0;
	float dy = 0;

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
				case 72://UP
					break;
				case 80://DOWN
					break;
				case 75://LEFT
					x--;
					break;
				case 77://RIGHT
					x++;
					break;
			}
		}

		//Calculating x and y
		if (dy > 1) {
			dy--;
			y++;
		} else if (dy < 0) {
			dy++;
			y--;
		}

		if (dx > 1) {
			dx--;
			x++;
		} else if (dx < 0) {
			dx++;
			x--;
		}

		drawGrid(screen_p, i_p, x + (SCREEN_WIDTH - BORDER_WIDTH) / 2 + 1, y+1);

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
	free(i_p);
}