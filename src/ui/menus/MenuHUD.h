#pragma once

#include "Menu.h"
#include "Engine.h"

class MenuHUD : public Menu
{
  std::string playerName;
  int currentHealth;
  int maxHealth;
  int coins;

public:
  MenuHUD();
  void Draw();
  void HandleInput(Engine &);
};