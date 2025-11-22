#pragma once
#include "Menu.h"

class MenuHUD : public Menu {
public:
  MenuHUD(Font *);
  void Draw();
};