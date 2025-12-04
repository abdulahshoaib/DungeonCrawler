#pragma once

#include <raylib.h>

class Progressbar
{
private:
  float value;           // Current progress value (0.0 to 1.0)
  Rectangle rect;        // Position and size
  float maxValue;        // Maximum value for the bar
  Color fillColor;       // Color of the filled portion
  Color backgroundColor; // Color of the empty portion

public:
  Progressbar();
  ~Progressbar();

  // Setup
  void Setup(Rectangle bounds, Color fill = {50, 200, 50, 255}, Color bg = {30, 30, 30, 255});

  // Update/Draw
  void SetValue(float newValue);
  void Draw();

  // Getters
  float GetValue() const { return value; }
  float GetMaxValue() const { return maxValue; }
};