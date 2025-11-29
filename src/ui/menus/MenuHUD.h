#pragma once

#include "Menu.h"
#include "Engine.h"

class MenuHUD : public Menu
{
  int currentHealth;
  int maxHealth;
  int coins;

public:
  std::string playerName;
  Texture2D Potrait;

  MenuHUD();
  void Draw();
  void HandleInput(Engine &);
};