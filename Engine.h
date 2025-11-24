#pragma once

#include "MenuMain.h"
#include "MenuPause.h"
#include "MenuSettings.h"
#include "Audio.h"
#include "Loader.h"
#include "Window.h"
#include "Player.h"
#include "UIEngine.h"

class GameState
{
public:
  GameState() {}
  virtual ~GameState() {}
  virtual void Update(Engine &) = 0;
  virtual void Draw(Engine &) = 0;
};

class MainMenuState : public GameState
{
private:
  MenuMain mainMenu;

public:
  void Update(Engine &);
  void Draw(Engine &);
};

class PlayState : public GameState
{
private:
public:
  void Update(Engine &);
  void Draw(Engine &);
};

class PauseState : public GameState
{
private:
  MenuPause pauseMenu;

public:
  void Update(Engine &);
  void Draw(Engine &);
};

class SettingsState : public GameState
{
private:
  MenuSettings settingsMenu;

public:
  void Update(Engine &);
  void Draw(Engine &);
};

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
  Window window;
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
};