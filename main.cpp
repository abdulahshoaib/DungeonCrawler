#include "core.h"
#include <cstdlib>

int main() {

  Game g;
  Screen screen = {.width = 800, .height = 300, .title = "Game"};

  // initialize window, assests and the game loop
  g.init(screen);
  g.update();

  return EXIT_SUCCESS;
}
