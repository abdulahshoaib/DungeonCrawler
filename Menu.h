#pragma once
#include <raylib.h>
#include "UIElement.h"
#include "utils.h"

class Menu {
protected:
  List<UIElement> elements;

public:
  Menu();
  virtual ~Menu();
  virtual void Draw();
};
