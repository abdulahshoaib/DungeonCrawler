#pragma once

#include "Menu.h"
#include "Button.h"

class MenuMain : public Menu
{
private:
  Button NewGame_btn, Settings_btn, Quit_btn, LoadGame_btn, EnterName_btn;
  Label titleLabel;
  Texture2D bgTex;
  Font titleFont;
  Font buttonFont;

public:
  void Draw();
  void HandleInput(Engine &) override;
};
