#pragma once

#include "GameState.h"
#include "Loader.h"
#include "core/Player.h"
#include "state/LoadingState.h"
#include "system/Audio.h"
#include <string>

struct Screen
{
  int width;
  int height;
  std::string title;
};

class Engine
{
  Audio audio;
  Player player;

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