#pragma once

#include "Menu.h"
#include "Engine.h"

class MenuHUD : public Menu
{
  int currentHealth;
  int maxHealth;
  int coins;
  class Character *playerRef = nullptr;
  // Hurt flash timer (seconds)
  float hurtTimer = 0.0f;
  const float hurtDuration = 0.5f; // half-second flash

public:
  std::string playerName;
  Texture2D Potrait;

  MenuHUD();
  void Draw();
  void HandleInput(Engine &);
  void SetPlayer(class Character *p);
  void HurtFlash();
};