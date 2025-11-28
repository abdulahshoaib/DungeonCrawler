
#include "MenuHUD.h"
MenuHUD::MenuHUD()
{
  playerName = "Haris";
  currentHealth = 100;
  maxHealth = 100;
  coins = 0;
}

void MenuHUD::Draw()
{
  int padding = 15;

  // ==== PORTRAIT BOX ====
  int portraitX = padding;
  int portraitY = padding;
  int portraitW = 100;
  int portraitH = 100;

  DrawRectangle(portraitX, portraitY, portraitW, portraitH, DARKGRAY);
  DrawRectangleLines(portraitX, portraitY, portraitW, portraitH, YELLOW);
  // Portrait image goes here when available:
  // DrawTexturePro(PlayerPortraitTexture, ...)

  // ==== PLAYER NAME ====
  DrawTextEx(Loader::TitleFont,
             playerName.c_str(),
             {(float)(portraitX + portraitW + 15), (float)(portraitY + 5)},
             24.0f,
             1.0f,
             WHITE);

  int barX = portraitX + portraitW + 15;
  int barY = portraitY + 45;
  int barW = 200;
  int barH = 15;

  float healthPercent = (float)currentHealth / maxHealth;
  int healthWidth = (int)(barW * healthPercent);

  // Health
  DrawRectangle(barX, barY, barW, barH, DARKGRAY);
  DrawRectangle(barX, barY, healthWidth, barH, RED);

  // Outline
  DrawRectangleLines(barX, barY, barW, barH, BLACK);

  // ==== COINS ====
  int coinY = barY + 25;

  DrawTextureEx(
      Loader::Coin,
      {(float)barX, (float)coinY},
      0.0f,
      0.3f,
      WHITE);

  float fontSize = 32.0f;

  DrawTextEx(
      Loader::TitleFont,
      TextFormat("%d", coins),
      {(float)(barX + 45), (float)(coinY + 4)},
      fontSize,
      1.0f,
      WHITE);
}

void MenuHUD::HandleInput(Engine &)
{
}