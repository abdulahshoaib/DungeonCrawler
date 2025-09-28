#pragma once
#include <raylib.h>
#include "utils.h"

class UIElement {
    Font *font;
    std::string text;
};

/* UI Elements */
class Button : public UIElement {
public:
  Button();
};
class Label : public UIElement {
public:
  Label();
};
class Progressbar : public UIElement {
  int progress;
public:
  Progressbar();
};

class Menu {
  List<UIElement> elements;

public:
  Menu();
  virtual ~Menu();
};

/* Menus */
class MenuMain : public Menu {
public:
  MenuMain();
};
class MenuPause : public Menu {
public:
  MenuPause();
};
class MenuHUD : public Menu {
public:
  MenuHUD();
};
class MenuInventory : public Menu {
public:
  MenuInventory();
};

/* UI Engine */
class UIEngine {
  Menu menus[4];

public:
  UIEngine();
};
