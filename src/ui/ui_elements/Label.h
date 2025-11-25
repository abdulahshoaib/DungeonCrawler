#pragma once
#include <raylib.h>
#include "UIElement.h"

class Label : public UIElement
{
public:
  Vector2 position;

  int fontSize = 20;
  int spacing = 2;

  std::string text = "Label not set";
  Font font;

  Label();
  void Draw(Color normalColor);
};