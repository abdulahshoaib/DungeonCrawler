#pragma once
#include "UIElement.h"
#include "utils.h"

class Engine;

class Menu
{
protected:
  List<UIElement> elements;

public:
  Menu();
  virtual ~Menu();
  virtual void Draw() = 0;
  virtual void HandleInput(Engine &) = 0;
};