#pragma once
#include "Engine.h"
#include "Menu.h"

class MenuPause : public Menu
{
public:
  MenuPause();
  void Draw();
  void HandleInput(Engine &) override;
};