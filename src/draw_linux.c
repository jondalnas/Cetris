#include "draw.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

void cls(void) {
	system("clear");
}

void draw_line(char *line) {
	wprintf(L"%s", line);
}

void draw_char(char c) {
	wprintf(L"%c", c);
}

void draw_utf8_char(uint32_t c) {
	setlocale(LC_CTYPE, "");
	wchar_t wc = (wchar_t) c;
	wprintf(L"%lc", wc);
}

void move_cursor(uint8_t x, uint8_t y) {
	wprintf(L"\033[%d;%dH", y + 1, x + 1);
}

void draw_flush() {
	wprintf(L"\n");
}
