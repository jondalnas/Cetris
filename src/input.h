#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#define ARROW_UP 0
#define ARROW_DOWN 1
#define ARROW_RIGHT 2
#define ARROW_LEFT 3

char getExitGame();
char getArrowDown();
char getKeyDown();
void inputLoop(void);

#ifdef _WIN32
static inline DWORD WINAPI il(LPVOID var) {
  inputLoop();
  return 0;
}
#else
static inline void *il(void *v) {
  inputLoop();
  return (void *)0;
}
#endif
