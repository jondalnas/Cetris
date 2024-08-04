#pragma once

#include "piece.h"

typedef struct {
  unsigned char x, y;
  char dx, dy;
  unsigned char rot;
  unsigned char curr_gravity;
  const uint16_t *curr_piece;
  uint32_t *stack;
} game_t;

void update(game_t *go);
void init_game(game_t *go);
