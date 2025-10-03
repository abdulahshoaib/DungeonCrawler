#include "window.h"
#include <raylib.h>

int Window::getWindowHeight() const { return screenHeigth; }
int Window::getWindowWidth() const { return screenWidth; }

Window::Window() {}

Window::Window(int width, int height, std::string)
    : screenWidth(width), screenHeigth(height) {
  InitWindow(width, height, "game");
}
