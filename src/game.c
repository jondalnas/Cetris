#include "game.h"

#include <stdlib.h>

#include "input.h"
#include "defs.h"
#include "render.h"

unsigned short collision(const uint16_t *piece_p, unsigned char index, uint32_t *stack, char x, char y);

void clear_line(game_t *go);

const uint16_t *get_random_piece() {
  return pieces[rand() % 7];
}

void init_game(game_t *go) {
  go->x = GAME_WIDTH / 2 - 2;
  go->y = 0;
  go->rot = 0;

  go->dx = 0;
  go->dy = 0;

  go->curr_gravity = 10;

  go->curr_piece = get_random_piece();

  go->stack = (uint32_t *) calloc(GAME_HEIGHT, sizeof(uint32_t));

  clear_screen();
  draw_borders('+', 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  draw_piece(go->curr_piece, go->x, go->y, GAME_WIDTH, go->rot);
}

void update(game_t* go) {
  char arrow;
  uint8_t i;
  int newRot;
  char move_dir = 0;

  go->dy += 1;

  // Input
  arrow = getArrowDown();
  switch (arrow) {
  case ARROW_UP: // UP
    newRot = (go->rot + 1) & 0x03;

    if (collision(go->curr_piece, newRot, go->stack, go->x, go->y))
      break;

    clear_piece(go->curr_piece, '+', go->x, go->y, GAME_WIDTH, go->rot);
    go->rot = newRot;
    draw_piece(go->curr_piece, go->x, go->y, GAME_WIDTH, go->rot);
    break;
  case ARROW_DOWN: // DOWN
    break;
  case ARROW_LEFT: // LEFT
    move_dir = -1;
    break;
  case ARROW_RIGHT: // RIGHT
    move_dir = 1;
    break;
  default: break;
  }

  // Move piece left or right
  if (move_dir != 0 && !collision(go->curr_piece, go->rot, go->stack, go->x + move_dir, go->y)) {
    clear_piece(go->curr_piece, '+', go->x, go->y, GAME_WIDTH, go->rot);
    go->x += move_dir;
    draw_piece(go->curr_piece, go->x, go->y, GAME_WIDTH, go->rot);
  }

  // Calculating x and y
  if (go->dy <= go->curr_gravity) return;
  
  if (!collision(go->curr_piece, go->rot, go->stack, go->x, go->y + 1)) {
    go->dy -= go->curr_gravity;
    clear_piece(go->curr_piece, '+', go->x, go->y, GAME_WIDTH, go->rot);
    go->y++;
    draw_piece(go->curr_piece, go->x, go->y, GAME_WIDTH, go->rot);
  } else if (go->dy > go->curr_gravity * 6) {
    // Piece stuck
    unsigned short pieceData = go->curr_piece[go->rot];

    // Write piece into collision data
    for (i = 0; i < 4; i++) {
      uint8_t x_offs = pieceData & 3;
      uint8_t y_offs = (pieceData >> 2) & 3;

      go->stack[y_offs + go->y] |= 1 << (go->x + x_offs);

      pieceData >>= 4;
    }

    // Reset piece position to middle-top of screen
    go->x = GAME_WIDTH / 2 - 2;
    go->y = go->rot = go->dx = go->dy = 0;

    // Select new piece
    go->curr_piece = get_random_piece();

    // Clear line
    clear_line(go);
  }
}

void clear_line(game_t *go) {
  uint8_t should_redraw = 0;

  for (uint8_t y = 0; y < GAME_HEIGHT; y++) {
    int line = go->stack[y];

    // If line is not filled, then continue
    if (line != ROW_WIDTH_BITMASK)
      continue;

    // Set stack collision to 0
    go->stack[y] = 0;

    should_redraw = 1;

    // Go though all lines and copy them down
    for (uint8_t yy = y - 1; yy != 255; yy--) {
      go->stack[yy + 1] = go->stack[yy];

      if (!go->stack[yy]) break;
    }
  }

  if (should_redraw)
    draw_stack(go->stack, '+', GAME_WIDTH, GAME_HEIGHT);
}

unsigned short collision(const uint16_t *piece, unsigned char index, uint32_t *stack, char x, char y) {
  uint16_t piece_data = piece[index];
  uint8_t i;
  uint8_t x_offs, y_offs;

  for (i = 0; i < 4; i++) {
    x_offs = piece_data & 3;
    y_offs = (piece_data >> 2) & 3;

    if (x + x_offs < 0 || x + x_offs >= GAME_WIDTH || y + y_offs < 0 || y + y_offs >= GAME_HEIGHT)
      return 1;

    if ((stack[y + y_offs] >> (x + x_offs)) & 1)
      return 1;

    piece_data >>= 4;
  }

  return 0;
}
