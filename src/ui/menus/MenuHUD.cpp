
#include "MenuHUD.h"
#include "system/GameProgress.h"
#include "characters/Character.h"
MenuHUD::MenuHUD()
{
  playerName = "Haris";
  currentHealth = 100;
  maxHealth = 100;
  coins = 0;
}

void MenuHUD::SetPlayer(Character *p)
{
  playerRef = p;
  if (playerRef)
  {
    maxHealth = (int)playerRef->maxHp;
    currentHealth = (int)playerRef->hp;
  }
}

void MenuHUD::HurtFlash()
{
  hurtTimer = hurtDuration;
}

void MenuHUD::Draw()
{
  int padding = 40;

  // ==== PORTRAIT BOX ====
  int portraitX = padding;
  int portraitY = padding;
  int portraitW = 100;
  int portraitH = 100;

  DrawTextureEx(
      Potrait,
      {(float)portraitX, (float)portraitY},
      0.0f,
      1.0f,
      WHITE);
  DrawRectangleLines(portraitX, portraitY, portraitW, portraitH, BROWN);

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

  // Read live health from player reference if available
  if (playerRef)
  {
    currentHealth = (int)playerRef->hp;
    maxHealth = (int)playerRef->maxHp;
    if (maxHealth <= 0)
      maxHealth = 1;
  }

  float healthPercent = (float)currentHealth / maxHealth;
  if (healthPercent < 0)
    healthPercent = 0;
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
      TextFormat("%d", GameProgress::GetCoinsCollected()),
      {(float)(barX + 45), (float)(coinY + 4)},
      fontSize,
      1.0f,
      WHITE);

  // Update and draw hurt flash overlay for HUD
  if (hurtTimer > 0.0f)
  {
    float dt = GetFrameTime();
    hurtTimer -= dt;
    if (hurtTimer < 0.0f)
      hurtTimer = 0.0f;

    float alphaPct = hurtTimer / hurtDuration;                // 1.0 -> 0.0
    unsigned char alpha = (unsigned char)(alphaPct * 200.0f); // max ~200
    // Draw a vertical gradient from red (top) to transparent (bottom)
    DrawRectangleGradientV(0, 0, GetScreenWidth(), portraitY + portraitH + 60, (Color){255, 60, 60, alpha}, (Color){255, 60, 60, 0});
  }
}

void MenuHUD::HandleInput(Engine &)
{
}