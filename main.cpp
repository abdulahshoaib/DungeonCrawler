#include "core.h"
#include <cstdlib>
#include <raylib.h>

int main() {

  Engine engine;
  Screen screen = {.width = 800, .height = 300, .title = "Game"};

  // initialize window, assests and the game loop
  engine.init(screen);
  engine.run();

  return EXIT_SUCCESS;
}
