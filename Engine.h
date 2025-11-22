#pragma once

#include "Audio.h"
#include "Loader.h"
#include "Window.h" 
#include "Player.h"
#include "UIEngine.h"
enum GameState {
    MENU,
    SETTINGS,
    GAME_LOOP,
    GAME_PAUSE
};
struct Screen {
  int width;
  int height;
  std::string title;
};

class Engine {
  Audio audio;
  Loader loader;
  Window window;
  Player player;
  UIEngine ui_engine;
  GameState gameState;

public:
  Engine();
  ~Engine();

  // TODO(demon_slayer): initialization of Window, loading
  // game assets and setting up the game state machine
  void init(Screen);

  // TODO(demon_slayer): game loop and the updation of the
  // game logic
  void run();
};

