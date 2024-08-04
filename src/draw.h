#pragma once

#include <stdint.h>

void cls(void);
void draw_line(char *line);
void draw_char(char c);
void draw_utf8_char(uint32_t c);
void move_cursor(uint8_t x, uint8_t y);

void draw_flush();
