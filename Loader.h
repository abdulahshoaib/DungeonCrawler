#pragma once
#include <raylib.h>

class Loader {
  Font font;

public:
  Loader();
  Loader(Font);
  Font *getFont();
};