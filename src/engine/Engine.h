#pragma once

#include "GameState.h"
#include "Loader.h"
#include "state/LoadingState.h"
#include <string>

struct Screen
{
  int width;
  int height;
  std::string title;
};

class Engine
{
  GameState* gameState;
  GameState* previousState;
public:
  Engine();
  ~Engine();

  // TODO(demon_slayer): 
    void init(Screen);

  void run();

  void ChangeState(GameState*);
  void PopState(); // Add this method
  void PushState(GameState*);
};