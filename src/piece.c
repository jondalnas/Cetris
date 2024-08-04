#include "piece.h"
#include <stdio.h>

const uint16_t I_PIECE[4] = {0x89AB, 0x26AE, 0x4567, 0x159D};
const uint16_t J_PIECE[4] = {0x0456, 0x1259, 0x456A, 0x1589};
const uint16_t L_PIECE[4] = {0x2456, 0x159A, 0x4568, 0x0159};
const uint16_t O_PIECE[4] = {0x0145, 0x0145, 0x0145, 0x0145};
const uint16_t S_PIECE[4] = {0x1245, 0x156A, 0x5689, 0x2569};
const uint16_t T_PIECE[4] = {0x1456, 0x1569, 0x4569, 0x1459};
const uint16_t Z_PIECE[4] = {0x0156, 0x2569, 0x459A, 0x1458};

const uint16_t *pieces[7] = {I_PIECE, J_PIECE, L_PIECE, O_PIECE,
                             S_PIECE, T_PIECE, Z_PIECE};
