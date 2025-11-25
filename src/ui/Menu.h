#pragma once
#include "UIElement.h"
#include "utils/utils.h"

class Engine;

class Menu
{
protected:
public:
  Menu();
  virtual ~Menu();
  virtual void Draw() = 0;
  virtual void HandleInput(Engine &) = 0;
};