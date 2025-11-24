#include "PlayState.h"
#include "Engine.h"
#include "SettingsState.h"
#include "MenuMain.h"

MenuMain::MenuMain()
{
  elements.Append(Play_btn);
  elements.Append(Quit_btn);
  elements.Append(Settings_btn);
}

void MenuMain::Draw()
{
  // TODO(demon_slayer): Need to move more of this into the button class code.
  Vector2 mousePoint = GetMousePosition();
  int screenWidth = 1100;

  int cx = screenWidth / 2;
  int cy = 100;
  int buttonFontSize = 20;
  int titleFontSize = 60;

  Vector2 titleText = {cx - 230, cy};

  Rectangle PlayRect = {cx - (int)(200 / 2), titleText.y + titleFontSize * 4, 200, 50};
  Rectangle SettingsRect = {cx - (int)200 / 2, PlayRect.y + PlayRect.height + 10, 200, 50};
  Rectangle QuitRect = {cx - (int)200 / 2, SettingsRect.y + SettingsRect.height + 10, 200, 50};

  // TODO(demon_slayer): Need to move all the text into the label UIElement class
  DrawText("Dungeon Crawler", titleText.x, titleText.y, titleFontSize, WHITE);

  Color playColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, PlayRect))
  {
    playColor = GREEN;
  }
  DrawRectangleRec(PlayRect, playColor);
  DrawText("PLAY", PlayRect.x + 70, PlayRect.y + 15, buttonFontSize, WHITE);

  Color settingsColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, SettingsRect))
  {
    settingsColor = PURPLE;
  }
  DrawRectangleRec(SettingsRect, settingsColor);
  DrawText("SETTINGS", SettingsRect.x + 45, SettingsRect.y + 15, buttonFontSize, WHITE);

  Color quitColor = GRAY;
  if (CheckCollisionPointRec(mousePoint, QuitRect))
  {
    quitColor = RED;
  }
  DrawRectangleRec(QuitRect, quitColor);
  DrawText("QUIT", QuitRect.x + 70, QuitRect.y + 15, buttonFontSize, WHITE);
}

void MenuMain::HandleInput(Engine &engine)
{
  bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  Vector2 mousePoint = GetMousePosition();

  // TODO(demon_slayer): a switch statement should be good here
  if (clicked && CheckCollisionPointRec(mousePoint, Play_btn.rect))
    engine.ChangeState(new PlayState());

  if (clicked && CheckCollisionPointRec(mousePoint, Settings_btn.rect))
    engine.ChangeState(new SettingsState());

  if (clicked && CheckCollisionPointRec(mousePoint, Quit_btn.rect))
    CloseWindow();
}