#include <stdio.h>
#include "grid.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 20
#define BORDER_WIDTH 20 

int main() {
	grid_t* screen_p = createNewGrid(SCREEN_WIDTH, SCREEN_HEIGHT);
	grid_t* border_p = createNewGrid(BORDER_WIDTH, SCREEN_HEIGHT);

	drawBoxChar(border_p, _NONE, 0, 0, BORDER_WIDTH, SCREEN_HEIGHT);

	drawGrid(screen_p, border_p, (SCREEN_WIDTH - BORDER_WIDTH) / 2, 0);

	renderGrid(screen_p);
}