#pragma once

#include <raylib.h>
#include <string>

class Loader
{
public:
  static Texture2D MainMenuBackground;
  static Font TitleFont;
  static Font ButtonFont;

  static void LoadAssets();

  static void UnloadAssets();
};