#pragma once

typedef struct {
  char screenObj;
  char x;
  char y;
} tile_t;

typedef struct {
  tile_t *tiles_p;
  char width;
  char height;
} grid_t;

grid_t *createNewGrid(char width, char height);
void renderGrid(grid_t *grid_p);
void drawBoxChar(grid_t *grid_p, char fill, int x, int y, int width,
                 int height);
void drawGrid(grid_t *grid_p, grid_t *target, int x, int y);
void drawGridScale(grid_t *grid_p, grid_t *target, char scale, int x, int y);
void clearScreen(grid_t *screen_p);
void drawBoxCharGrid(grid_t *grid_p, int x, int y, int width, int height);

extern const char _NONE;
extern const char _BORDER_V;
extern const char _BORDER_H;
extern const char _BORDER_UR;
extern const char _BORDER_UL;
extern const char _BORDER_DR;
extern const char _BORDER_DL;
extern const char _BLOCK;
extern const char _GRID_H;
extern const char _GRID_V;
extern const char _GRID_C;
