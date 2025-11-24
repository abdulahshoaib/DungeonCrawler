#pragma once
#include "Menu.h"
#include "Loader.h"
#define MAIN_MENU 0
#define PAUSE_MENU 1
#define HUD 2
#define INVENTORY 3

class UIEngine
{
public:
  Menu *menus[4];
  UIEngine();
};