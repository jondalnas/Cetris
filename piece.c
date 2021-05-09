#include <stdio.h>
#include "piece.h"

const piece_t I_PIECE = {0x00F0, 0x2222, 0x0F00, 0x4444};
const piece_t L_PIECE = {0x0074, 0x0622, 0x0170, 0x0223};
const piece_t J_PIECE = {0x0071, 0x0226, 0x0470, 0x0322};
const piece_t Z_PIECE = {0x0063, 0x0264, 0x0630, 0x0132};
const piece_t S_PIECE = {0x0036, 0x0462, 0x0360, 0x0231};
const piece_t O_PIECE = {0x0660, 0x0660, 0x0660, 0x0660};

const piece_t T_PIECE = {0x0072, 0x0262, 0x0270, 0x0232};

grid_t* pieceToGrid(const piece_t* piece_p, char index) {
	grid_t* border_p = createNewGrid(4, 4);

	unsigned short pieceData = *(&piece_p->tile0 + index);

	for (int i = 0; i < 16; i++) {
		(border_p->tiles_p + i)->screenObj = pieceData & 1 ? _BLOCK : _NONE;
		pieceData >>= 1;
	}

	return border_p;
}