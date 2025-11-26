#pragma once

#include <raylib.h>
#include <string>

class Label
{
public:
  Vector2 position;

  int fontSize = 20;
  int spacing = 2;

  std::string text = "Label not set";

  Label();
  ~Label();
  void Draw(Color normalColor);
};