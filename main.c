#include <stdio.h>
#include "grid.h"

int main() {
	grid_t* grid_p = createNewGrid(20, 20);

	drawBoxChar(grid_p, _NONE, 5, 5, 10, 10);

	renderGrid(grid_p);
}