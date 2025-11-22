#pragma once
#include <raylib.h>
#include <string>

class UIElement {
protected:
  Font *font;
  std::string text;

public:
  UIElement();
  UIElement(Font *);
};
