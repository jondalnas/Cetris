#include "input.h"
/* #include <conio.h> */

char arrow, key, exitGame;

char getArrowDown() {
	char temp = arrow;
	arrow = -1;

	return temp;
}

char getKeyDown() {
	return key;
}

/* DWORD WINAPI inputLoop(LPVOID var) { */
int inputLoop(int var) {
	exitGame = 0;
	while (1) {
		/* char ch = getch(); */
		char ch;

		if (ch == 0) {
			/* char a = getch(); */
			char a;

			if (a != arrow) {
				arrow = a;
			}
		} else if (ch == 113 || ch == 81) {
			exitGame = 1;
			return 0;
		} else {
			key = ch;
		}
	}

	return 0;
}

char getExitGame() {
	return exitGame;
}
