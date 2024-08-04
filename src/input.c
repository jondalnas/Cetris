#include "input.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <stdio.h>

char getch(void);
#endif

char arrow, key, exitGame;

char getArrowDown() {
	char temp = arrow;
	arrow = -1;

#ifdef _WIN32
    switch (temp) {
    case 72: // UP
		return ARROW_UP;
    case 80: // DOWN
		return ARROW_DOWN;
    case 75: // LEFT
		return ARROW_LEFT;
    case 77: // RIGHT
		return ARROW_RIGHT;
    }
		return temp;
#else
	// UP - 65
	// DOWN - 66
	// RIGHT - 67
	// LEFT - 68
	return temp - 65;
#endif
}

char getKeyDown() {
	return key;
}

#ifdef _WIN32
void inputLoop(void) {
	exitGame = 0;
	while (1) {
		char ch = getch();

		if (ch == 0) {
			char a = getch();

			if (a != arrow) {
				arrow = a;
			}
		} else if (ch == 113 || ch == 81) {
			exitGame = 1;
			return;
		} else {
			key = ch;
		}
	}
}
#else
void inputLoop(void) {
	exitGame = 0;
	while (1) {
		char ch = getch();

		if (ch & 0x80) { // TODO: Might get false positives on KeyCodes > 127
			if (ch != arrow) {
				arrow = ch & 0x7F;
			}
		} else if (ch == 113 || ch == 81) {
			exitGame = 1;
			return;
		} else {
			key = ch;
		}
	}
}
#endif

char getExitGame() {
	return exitGame;
}

#ifndef _WIN32
/* From https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux */
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) {
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	current = old; /* make new settings same as old settings */
	current.c_lflag &= ~ICANON; /* disable buffered i/o */
	if (echo) {
		current.c_lflag |= ECHO; /* set echo mode */
	} else {
		current.c_lflag &= ~ECHO; /* set no echo mode */
	}
	tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
	tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)  {
	char ch;
	initTermios(echo);
	ch = getchar();
	if (ch == 27) { // Arrow
		getchar();
		return getchar() | 0x80;
	}
	resetTermios();
	return ch;
}

/* Read 1 character without echo */
char getch(void) {
	return getch_(0);
}

/* Read 1 character with echo */
char getche(void) {
	return getch_(1);
}
#endif
