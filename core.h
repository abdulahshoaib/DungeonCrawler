#pragma once
#include "utils.h"
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
  Player();
  Player(Vector2, Vector2);
  void move(float, float);

  Vector2 getSize() const;
  Vector2 getPos() const;
};

class Loader {
  Font font;

public:
  Loader();
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
  Audio();
  Audio(char *);
  ~Audio();
};

class UIElement {
protected:
  Font *font;
  std::string text;

public:
  UIElement();
  UIElement(Font *);
};

/* UI Elements */
class Button : public UIElement {
public:
  Button(Font *);
};
class Label : public UIElement {
public:
  Label(Font *);
};
class Progressbar : public UIElement {
  int progress;

public:
  Progressbar(Font *);
};

class Menu {
protected:
  List<UIElement> elements;

public:
  Menu();
  virtual ~Menu();
  virtual void Draw();
};

/* Menus */
class MenuMain : public Menu {
public:
  MenuMain(Font *);
  void Draw();
};
class MenuPause : public Menu {
public:
  MenuPause(Font *);
  void Draw();
};
class MenuHUD : public Menu {
public:
  MenuHUD(Font *);
  void Draw();
};
class MenuInventory : public Menu {
public:
  MenuInventory(Font *);
  void Draw();
};

#define MAIN_MENU 0
#define PAUSE_MENU 1
#define HUD 2
#define INVENTORY 3

/* UI Engine */
class UIEngine {
public:
  Menu *menus[4];
  UIEngine();
  UIEngine(Loader *);
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
