#pragma once

#include <raylib.h>
#include <string>

class Loader
{
public:
  static Texture2D MainMenuBackground;
  static Font TitleFont;
  static Font ButtonFont;
  static Font TitleFont2;

  static Texture2D knight1_attack1, knight1_attack2, knight1_attack3, knight1_dead, knight1_defend, knight1_hurt, knight1_idle, knight1_jump, knight1_protect, knight1_run, knight1_runattack, knight1_walk;
  static Texture2D knight2_attack1, knight2_attack2, knight2_attack3, knight2_dead, knight2_defend, knight2_hurt, knight2_idle, knight2_jump, knight2_protect, knight2_run, knight2_runattack, knight2_walk;
  static Texture2D knight3_attack1, knight3_attack2, knight3_attack3, knight3_dead, knight3_defend, knight3_hurt, knight3_idle, knight3_jump, knight3_protect, knight3_run, knight3_runattack, knight3_walk;

  static void Load_knight_assests();

  static void LoadAssets();

  static void UnloadAssets();
};