#pragma once
#include "Menu.h"
#include "Engine.h"

class MenuInventory : public Menu
{
public:
  MenuInventory();
  void Draw();
  void HandleInput(Engine &);
};