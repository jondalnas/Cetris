#ifdef _WIN32
#include <windows.h>
#endif

char arrow;
char key;
char exitGame;

char getExitGame();
char getArrowDown();
char getKeyDown();
DWORD WINAPI inputLoop(LPVOID var);