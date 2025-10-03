#include "core.h"
#include <raylib.h>

Engine::~Engine() {}

void Engine::init(Screen screen) {
  InitWindow(screen.width, screen.height, "game");
  gameState = MENU;
  // TODO(demon_slayer): load the assets
}

void Engine::run() {

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // TODO(demon_slayer): I don't like how this
    // state management is handled
    if (gameState == MENU)
      ui_engine.menus[MAIN_MENU]->Draw();
    if (gameState == GAME_LOOP) {

      const float speed = 0.4f;

      int key = 0;
      if (IsKeyDown(KEY_W))
        key = KEY_W;
      if (IsKeyDown(KEY_A))
        key = KEY_A;
      if (IsKeyDown(KEY_D))
        key = KEY_D;
      if (IsKeyDown(KEY_S))
        key = KEY_S;

      switch (key) {
      case KEY_W:
        player.move(0, -speed);
        break;
      case KEY_A:
        player.move(-speed, 0);
        break;
      case KEY_S:
        player.move(0, speed);
        break;
      case KEY_D:
        player.move(speed, 0);
        break;
      }

      DrawRectangleV(player.getPos(), player.getSize(), RED);
    }
    EndDrawing();
  }
  CloseWindow();
}

Engine::Engine() {
  // UI
}
Player::Player(Vector2 position, Vector2 size) : pos(position), size(size) {}
Player::Player() : pos({0, 0}), size({10, 10}) {}

Vector2 Player::getPos() const { return pos; }
Vector2 Player::getSize() const { return size; }

void Player::move(float _x, float _y) {
  pos.x += _x;
  pos.y += _y;
}

Loader::Loader(Font f) : font(f) {}
Loader::Loader() {}

Font *Loader::getFont() { return &font; } // just return a ref to the font

Audio::Audio(char *audio_name) {
  InitAudioDevice();

  // TODO(demon_slayer): change this so that when I change
  // to using an array for audio and sound then it loads them
  // one by one
  wave = LoadWave(audio_name);
  sound = LoadSoundFromWave(wave);
}

Audio::Audio() { InitAudioDevice(); }

Audio::~Audio() {
  UnloadSound(sound);
  UnloadWave(wave);
  CloseAudioDevice();
}

UIElement::UIElement(Font *_font) { font = _font; }
UIElement::UIElement() = default;

Progressbar::Progressbar(Font *font) : UIElement(font) {}
Button::Button(Font *font) : UIElement(font) {}
Label::Label(Font *font) : UIElement(font) {}

Menu::Menu() {}
Menu::~Menu() {}
void Menu::Draw() {}

MenuHUD::MenuHUD(Font *font) {
  //
  // elements.Append(const UIElement &)
}

MenuMain::MenuMain(Font *font) {
  Button Play_btn(font), Pause_btn(font), Settings_btn(font), Quit(font);
  elements.Append(Play_btn);
  elements.Append(Pause_btn);
  elements.Append(Settings_btn);
}
MenuPause::MenuPause(Font *font) {}
MenuInventory::MenuInventory(Font *font) {}
void MenuMain::Draw() {
  DrawText("GAME TITLE", 100, 50, 40, WHITE);

  DrawRectangle(100, 150, 200, 50, GRAY);
  DrawText("PLAY", 150, 165, 20, WHITE);

  DrawRectangle(100, 220, 200, 50, GRAY);
  DrawText("SETTINGS", 130, 235, 20, WHITE);

  DrawRectangle(100, 290, 200, 50, GRAY);
  DrawText("QUIT", 160, 305, 20, WHITE);
}
void MenuPause::Draw() {}
void MenuHUD::Draw() {}
void MenuInventory::Draw() {}

UIEngine::UIEngine(Loader *l) {
  Font *font = l->getFont();
  menus[PAUSE_MENU] = new MenuPause(font);
  menus[INVENTORY] = new MenuInventory(font);
  menus[MAIN_MENU] = new MenuMain(font);
  menus[HUD] = new MenuHUD(font);
}

UIEngine::UIEngine() {}
