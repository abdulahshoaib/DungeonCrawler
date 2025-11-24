#pragma once
#include "Menu.h"

class Engine;

class MenuPause : public Menu
{
public:
  MenuPause();
  void Draw();
  void HandleInput(Engine &) override;
};