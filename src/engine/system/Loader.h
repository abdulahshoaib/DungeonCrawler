#pragma once

#include <raylib.h>
#include <string>
#include "../characters/Black_werewolf.h"
#include "../characters/Yamabushi_tengu.h"
#include "../characters/Karasu_tengu.h"
#include "../characters/Kitsune.h"
#include "../characters/Knight1.h"
#include "../characters/Knight2.h"
#include "../characters/Knight3.h"
#include "../characters/Red_werewolf.h"
#include "../characters/White_werewolf.h"
#include "../characters/Samurai.h"
#include "../characters/Samurai_archer.h"
#include "../characters/Samurai_commander.h"
#include "../characters/Satyr_Enemy.h"
#include "../characters/Skeleton_archer.h"
#include "../characters/Skeleton_warrior.h"
#include "../characters/Skeleton_spearman.h"

class Loader
{
public:
  static Black_werewolf blackWerewolf;

  static Yamabushi_tengu yamabushiTengu;
  static Karasu_tengu karasuTengu;
  static Kitsune kitsune;

  static Knight1 knight1;
  static Knight2 knight2;
  static Knight3 knight3;

  static Samurai samurai;
  static Samurai_archer samuraiArcher;
  static Samurai_Commander samuraiCommander;

  static Satyr_enemy satyr;

  static Skeleton_archer skeletonArcher;
  static Skeleton_warrior skeletonWarrior;
  static Skeleton_spearman skeletonSpearman;

  static Texture2D MainMenuBackground;
  static Font TitleFont;
  static Font ButtonFont;

  static void LoadAssets();

  static void UnloadAssets();
};