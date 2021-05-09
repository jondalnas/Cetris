#include "input.h"
#include <conio.h>

char getArrowDown() {
	char temp = arrow;
	arrow = -1;

	return temp;
}

char getKeyDown() {
	return getch();
}

DWORD WINAPI inputLoop(LPVOID var) {
	while (1) {
		char ch = getch();

		if (ch == 0) {
			char a = getch();

			if (a != arrow) {
				arrow = a;
			}
		}

		if (ch == 113 || ch == 81) {
			exit(0);
			return 0;
		}
	}

	return 0;
}