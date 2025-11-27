#pragma once

#include <raylib.h>
#include "Label.h"

class Button
{
public:
  Rectangle rect;
  Label label;

  Color labelColor;
  Color labelNormalColor;
  Color labelHoverColor;

  int padding = 3;

  Button();
  void Draw(Color, Color);
};