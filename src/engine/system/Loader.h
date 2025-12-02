#pragma once

#include <raylib.h>
#include "Animation.h"

class Loader
{
public:
  // == Skeleton Warrior ==
  inline static Animation SkeletonWarriorAttack1;
  inline static Animation SkeletonWarriorAttack2;
  inline static Animation SkeletonWarriorAttack3;
  inline static Animation SkeletonWarriorDead;
  inline static Animation SkeletonWarriorHurt;
  inline static Animation SkeletonWarriorIdle;
  inline static Animation SkeletonWarriorProtect;
  inline static Animation SkeletonWarriorRun;
  inline static Animation SkeletonWarriorRunAttack;
  inline static Animation SkeletonWarriorWalk;
  static void LoadSkeletonWarrior();
  static void UnLoadSkeletonWarrior();

  // == Skeleton Archer ==
  inline static Animation SkeletonArcherAttack1;
  inline static Animation SkeletonArcherAttack2;
  inline static Animation SkeletonArcherAttack3;
  inline static Animation SkeletonArcherDead;
  inline static Animation SkeletonArcherEvasion;
  inline static Animation SkeletonArcherHurt;
  inline static Animation SkeletonArcherIdle;
  inline static Animation SkeletonArcherShot1;
  inline static Animation SkeletonArcherShot2;
  inline static Animation SkeletonArcherWalk;
  static void LoadSkeletonArcher();
  static void UnLoadSkeletonArcher();

  // == Skeleton Spearman ==
  inline static Animation SkeletonSpearmanAttack1;
  inline static Animation SkeletonSpearmanAttack2;
  inline static Animation SkeletonSpearmanDead;
  inline static Animation SkeletonSpearmanFall;
  inline static Animation SkeletonSpearmanHurt;
  inline static Animation SkeletonSpearmanIdle;
  inline static Animation SkeletonSpearmanProtect;
  inline static Animation SkeletonSpearmanRun;
  inline static Animation SkeletonSpearmanRunAttack;
  inline static Animation SkeletonSpearmanWalk;
  static void LoadSkeletonSpearman();
  static void UnLoadSkeletonSpearman();

  // == Karasu Tengu ==
  inline static Animation KarasuTenguAttack1;
  inline static Animation KarasuTenguAttack2;
  inline static Animation KarasuTenguAttack3;
  inline static Animation KarasuTenguDead;
  inline static Animation KarasuTenguHurt;
  inline static Animation KarasuTenguIdle1;
  inline static Animation KarasuTenguIdle2;
  inline static Animation KarasuTenguRun;
  inline static Animation KarasuTenguWalk;
  static void LoadKarasuTengu();
  static void UnLoadKarasuTengu();

  // == Yamabushi Tengu ==
  inline static Animation YamabushiTenguAttack1;
  inline static Animation YamabushiTenguAttack2;
  inline static Animation YamabushiTenguAttack3;
  inline static Animation YamabushiTenguDead;
  inline static Animation YamabushiTenguHurt;
  inline static Animation YamabushiTenguIdle1;
  inline static Animation YamabushiTenguIdle2;
  inline static Animation YamabushiTenguRun;
  inline static Animation YamabushiTenguWalk;
  static void LoadYamabushiTengu();
  static void UnLoadYamabushiTengu();

  // == Knight 1 ==
  inline static Animation Knight1Attack1;
  inline static Animation Knight1Attack2;
  inline static Animation Knight1Attack3;
  inline static Animation Knight1Dead;
  inline static Animation Knight1Defend;
  inline static Animation Knight1Hurt;
  inline static Animation Knight1Idle;
  inline static Animation Knight1Jump;
  inline static Animation Knight1Protect;
  inline static Animation Knight1Run;
  inline static Animation Knight1RunAttack;
  inline static Animation Knight1Walk;
  static void LoadKnight1();
  static void UnLoadKnight1();

  // == Knight 2 ==
  inline static Animation Knight2Attack1;
  inline static Animation Knight2Attack2;
  inline static Animation Knight2Attack3;
  inline static Animation Knight2Dead;
  inline static Animation Knight2Defend;
  inline static Animation Knight2Hurt;
  inline static Animation Knight2Idle;
  inline static Animation Knight2Jump;
  inline static Animation Knight2Protect;
  inline static Animation Knight2Run;
  inline static Animation Knight2RunAttack;
  inline static Animation Knight2Walk;
  static void LoadKnight2();
  static void UnLoadKnight2();

  // == Knight 3 ==
  inline static Animation Knight3Attack1;
  inline static Animation Knight3Attack2;
  inline static Animation Knight3Attack3;
  inline static Animation Knight3Dead;
  inline static Animation Knight3Defend;
  inline static Animation Knight3Hurt;
  inline static Animation Knight3Idle;
  inline static Animation Knight3Jump;
  inline static Animation Knight3Protect;
  inline static Animation Knight3Run;
  inline static Animation Knight3RunAttack;
  inline static Animation Knight3Walk;
  static void LoadKnight3();
  static void UnLoadKnight3();

  // == Samurai ==
  inline static Animation SamuraiAttack1;
  inline static Animation SamuraiAttack2;
  inline static Animation SamuraiAttack3;
  inline static Animation SamuraiDead;
  inline static Animation SamuraiHurt;
  inline static Animation SamuraiIdle;
  inline static Animation SamuraiJump;
  inline static Animation SamuraiProtect;
  inline static Animation SamuraiRun;
  inline static Animation SamuraiWalk;
  static void LoadSamurai();
  static void UnLoadSamurai();

  // == Samurai Archer ==
  inline static Animation SamuraiArcherAttack1;
  inline static Animation SamuraiArcherAttack2;
  inline static Animation SamuraiArcherAttack3;
  inline static Animation SamuraiArcherDead;
  inline static Animation SamuraiArcherIdle;
  inline static Animation SamuraiArcherJump;
  inline static Animation SamuraiArcherRun;
  inline static Animation SamuraiArcherShot;
  inline static Animation SamuraiArcherWalk;
  static void LoadSamuraiArcher();
  static void UnLoadSamuraiArcher();

  // == Samurai Commander ==
  inline static Animation SamuraiCommanderAttack1;
  inline static Animation SamuraiCommanderAttack2;
  inline static Animation SamuraiCommanderAttack3;
  inline static Animation SamuraiCommanderDead;
  inline static Animation SamuraiCommanderHurt;
  inline static Animation SamuraiCommanderIdle;
  inline static Animation SamuraiCommanderJump;
  inline static Animation SamuraiCommanderProtect;
  inline static Animation SamuraiCommanderRun;
  inline static Animation SamuraiCommanderWalk;
  static void LoadSamuraiCommander();
  static void UnLoadSamuraiCommander();

  // == Menu Background Images ==
  inline static Texture2D MainMenuBackground;
  inline static Texture2D SelectionMenuBackground;
  inline static Texture2D LoadMenuBackground;
  static void LoadBackgrounds();
  static void UnLoadBackgrounds();

  // == Colectable Images ==
  inline static Animation CoinAnim;
  inline static Texture2D Coin;
  static void LoadCollectables();
  static void UnLoadCollectables();

  // == Special Items ==
  inline static Texture2D Arrow;
  inline static Animation Torch;
  static void LoadSpecialItems();
  static void UnLoadSpecialItems();

  // == Fonts ==
  inline static Font TitleFont;
  static void LoadFont();
  static void UnLoadFont();

  // == Potraits ==
  inline static Texture2D Knight1Potrait;
  inline static Texture2D Knight2Potrait;
  inline static Texture2D Knight3Potrait;
  inline static Texture2D SamuraiPotrait;
  inline static Texture2D SamuraiArcherPotrait;
  inline static Texture2D SamuraiCommanderPotrait;
  static void LoadPotraitCards();
  static void UnLoadPotraitCards();

  // == HUD potraits ==
  inline static Texture2D Knight1HUD;
  inline static Texture2D Knight2HUD;
  inline static Texture2D Knight3HUD;
  inline static Texture2D SamuraiHUD;
  inline static Texture2D SamuraiArcherHUD;
  inline static Texture2D SamuraiCommanderHUD;
  static void LoadHUDPotraits();
  static void UnLoadHUDPotraits();

  // == Maps ==
  inline static Texture2D TileSet;

  static void UnloadAssets();
};