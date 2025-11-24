#include "MenuMain.h"
#include "Button.h"
MenuMain::MenuMain()
{
  Button Play_btn, Pause_btn, Settings_btn, Quit;
  elements.Append(Play_btn);
  elements.Append(Pause_btn);
  elements.Append(Settings_btn);
}

void MenuMain::Draw()
{
  Vector2 mousePoint = GetMousePosition();
  bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  int screenWidth = 1100;

  int cx = screenWidth / 2;
  int cy = 100;
  int buttonFontSize = 20;
  int titleFontSize = 60;

  Vector2 titleText = {cx - 250, cy};

  Rectangle PlayRect = {cx - (int)(200 / 2), titleText.y + titleFontSize * 2, 200, 50};
  Rectangle SettingsRect = {cx - (int)200 / 2, PlayRect.y + PlayRect.height + 10, 200, 50};
  Rectangle QuitRect = {cx - (int)200 / 2, SettingsRect.y + SettingsRect.height + 10, 200, 50};

  DrawText("Dungeon Crawler", titleText.x, titleText.y, titleFontSize, WHITE);

  Color playColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, PlayRect))
  {
    playColor = GREEN;

    if (clicked)
    {
      // TODO: engine->gameState = GAME_LOOP;
    }
  }
  DrawRectangleRec(PlayRect, playColor);
  DrawText("PLAY", PlayRect.x + 70, PlayRect.y + 15, buttonFontSize, WHITE);

  Color settingsColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, SettingsRect))
  {
    settingsColor = PURPLE;

    if (clicked)
    {
      // TODO: game state change
    }
  }
  DrawRectangleRec(SettingsRect, settingsColor);
  DrawText("SETTINGS", SettingsRect.x + 45, SettingsRect.y + 15, buttonFontSize, WHITE);

  Color quitColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, QuitRect))
  {
    quitColor = RED;

    if (clicked)
    {
      // TODO: game state change
    }
  }
  DrawRectangleRec(QuitRect, quitColor);
  DrawText("QUIT", QuitRect.x + 70, QuitRect.y + 15, buttonFontSize, WHITE);
}