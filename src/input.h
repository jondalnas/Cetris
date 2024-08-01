#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

char getExitGame();
char getArrowDown();
char getKeyDown();
//DWORD WINAPI inputLoop(LPVOID var);
int inputLoop(int);
