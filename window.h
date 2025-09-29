#pragma once
#include "raylib.h"
#include <string>

class Window {
  int screenWidth;
  int screenHeigth;

public:
  Window();
  Window(int, int, std::string);
  int getWindowHeight() const;
  int getWindowWidth() const;
};
