#pragma once

#include <stdint.h>

#include "piece.h"

void draw_borders(uint32_t fill, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void draw_grid(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void draw_piece(const uint16_t *piece, uint8_t x, uint8_t y, uint8_t width, uint8_t rot);
void draw_stack(uint32_t *stack, uint32_t fill, uint8_t width, uint8_t height);

void clear_screen();
void clear_piece(const uint16_t *piece, uint32_t fill, uint8_t x, uint8_t y, uint8_t width, uint8_t rot);
