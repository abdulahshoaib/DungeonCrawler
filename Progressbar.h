#pragma once
#include <raylib.h>
#include "UIElement.h"

class Progressbar : public UIElement {
  int progress;

public:
  Progressbar();
};