#include "grid.h"

typedef struct {
	unsigned short tile0; //Unrotated tile data
	unsigned short tile1; //90deg rotated tile data
	unsigned short tile2; //180deg rotated tile data
	unsigned short tile3; //270deg rotated tile data
} piece_t;

grid_t* pieceToGrid(const piece_t* tile_p, char index);

const piece_t I_PIECE;
const piece_t L_PIECE;
const piece_t J_PIECE;
const piece_t Z_PIECE;
const piece_t S_PIECE;
const piece_t O_PIECE;
const piece_t T_PIECE;