#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "input.h"
#include "piece.h"
#include "game.h"
#include "defs.h"
#include "render.h"

#include "draw.h"

int main() {
  game_t go;

  srand(time(0));
  // Input
#ifdef _WIN32
  HANDLE input_thread = CreateThread(NULL, 0, inputLoop, NULL, 0, NULL);
#else
  pthread_t input_thread;
  int err_code = pthread_create(&input_thread, NULL, il, NULL);
  
  if (err_code) {
    printf("Could not create input thread, exitting");
    exit(1);
  }
#endif

  init_game(&go);

  while (!getExitGame()) {
    // Game logic
    update(&go);

#ifdef _WIN32
    Sleep(SLEEP);
#else
    usleep(SLEEP * 1000);
#endif
  }

#ifdef _WIN32
  CloseHandle(inputThread);
#else
  pthread_join(input_thread, NULL);
#endif
  free(go.stack);

  return 0;
}
