#pragma once
#include <raylib.h>
#include "UIElement.h"
#include "Label.h"

class Button : public UIElement
{
public:
  Rectangle rect;
  Label label;
  int padding = 3; // padding around the label text

  Button();
  void Draw(Color, Color);
};