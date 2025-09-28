#pragma once
#include "ui.h"
#include "window.h"
#include <raylib.h>
#include <string>

enum GameState {
  MENU,       // Game currently at the Menu
  SETTINGS,   // Game currently at the Settings menu
  GAME_LOOP,  // Game currently running
  GAME_PAUSE, // Game is paused
  INVENTORY   // The player has the inventory opened
};

struct Screen {
  int width;
  int height;
  std::string title;
};

class Player {
  Vector2 pos;
  Vector2 size;

public:
  Player(Vector2, Vector2);
  void move(float, float);

  Vector2 getSize() const;
  Vector2 getPos() const;
};



class Loader {
  Font font;

public:
  Loader(Font);
  Font *getFont();
};

class Audio {
  // TODO(demon_slayer): we might need to
  // convert this into an array or something
  // to load more than one waves and sounds
  Sound sound;
  Wave wave;
  // Note(demon_slayer): For different Auidos
  // rather than referencing them using numbers
  // use this ENUM
  enum SoundNames {};

public:
  Audio(char *);
  ~Audio();
};

class Engine {
  Window window;
  Player player;
  UIEngine ui_engine;
  Audio audio;
  Loader loader;
  GameState gameState;

public:
  Engine();
  ~Engine();

  // TODO(demon_slayer): initialization of Window, loading
  // game assets and setting up the game state machine
  void init(Screen);

  // TODO(demon_slayer): game loop and the updation of the
  // game logic
  void update();
};
