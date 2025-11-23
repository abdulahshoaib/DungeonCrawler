
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
  DrawText("GAME TITLE", 100, 50, 40, WHITE);

  DrawRectangle(100, 150, 200, 50, GRAY);
  DrawText("PLAY", 150, 165, 20, WHITE);

  DrawRectangle(100, 220, 200, 50, GRAY);
  DrawText("SETTINGS", 130, 235, 20, WHITE);

  DrawRectangle(100, 290, 200, 50, GRAY);
  DrawText("QUIT", 160, 305, 20, WHITE);
}