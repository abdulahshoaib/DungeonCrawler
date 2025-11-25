#pragma once

#include "Menu.h"
#include "Engine.h"

class MenuHUD : public Menu
{
public:
  MenuHUD();
  void Draw();
  void HandleInput(Engine &);
};