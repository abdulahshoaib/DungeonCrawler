#pragma once
#include "Menu.h"

class MenuMain : public Menu
{
private:
  Button Play_btn, Settings_btn, Quit_btn;

public:
  MenuMain();
  void Draw();
  void HandleInput(Engine &) override;
};