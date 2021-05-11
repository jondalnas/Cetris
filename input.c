#include "input.h"
#include <conio.h>

char getArrowDown() {
	char temp = arrow;
	arrow = -1;

	return temp;
}

char getKeyDown() {
	return key;
}

DWORD WINAPI inputLoop(LPVOID var) {
	while (1) {
		char ch = getch();

		if (ch == 0) {
			char a = getch();

			if (a != arrow) {
				arrow = a;
			}
		} else if (ch == 113 || ch == 81) {
			exit(0);
			return 0;
		} else {
			key = ch;
		}
	}

	return 0;
}