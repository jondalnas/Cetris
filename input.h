#ifdef _WIN32
#include <windows.h>
#endif

char arrow;

char getArrowDown();
char getKeyDown();
DWORD WINAPI inputLoop(LPVOID var);