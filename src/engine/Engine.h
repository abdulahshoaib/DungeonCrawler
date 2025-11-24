#pragma once

#include "GameState.h"
#include "Audio.h"
#include "Loader.h"
#include "Player.h"
#include "UIEngine.h"
#include "state/MainMenuState.h"

struct Screen
{
  int width;
  int height;
  std::string title;
};

class Engine
{
  Audio audio;
  Loader loader;
  Player player;
  UIEngine ui_engine;

public:
  Engine();
  ~Engine();

  // TODO(demon_slayer): initialization of Window, loading
  // game assets and setting up the game state machine
  void init(Screen);

  // TODO(demon_slayer): game loop and the updation of the
  // game logic
  void run();

  // Game State
  GameState *gameState;

  // Change the current game state
  void ChangeState(GameState *gameState);
};