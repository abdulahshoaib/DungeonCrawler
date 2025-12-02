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
  GameState *gameState;
  GameState *previousState;
  bool exitRequested = false;

public:
  Engine();
  ~Engine();

  // TODO(demon_slayer):
  void init(Screen);

  void run();

  void RequestExit() { exitRequested = true; }

  void ChangeState(GameState *);
  void PopState(); // Add this method
  void PushState(GameState *);
  // Expose previous state (used by pause menu to access underlying playstate)
  GameState *GetPreviousState() const { return previousState; }
};