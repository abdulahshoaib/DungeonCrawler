#pragma once
#include "core.h"
#include <raylib.h>

Engine::~Engine() {}

void Engine::init(Screen screen) {
  gameState = MENU;
  // TODO(demon_slayer): load the assets
}

void Engine::update() {

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // TODO(demon_slayer): I don't like how this
    // state management is handled
    if (gameState == MENU)
      ui.DrawMenu(gameState);
    else if (gameState == GAME_LOOP) {

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

Vector2 Player::getPos() const { return pos; }
Vector2 Player::getSize() const { return size; }

void Player::move(float _x, float _y) {
  pos.x += _x;
  pos.y += _y;
}

Loader::Loader(Font f) : font(f) {}
Font *Loader::getFont() { return &font; } // just return a ref to the font

Audio::Audio(char *audio_name) {
  InitAudioDevice();

  // TODO(demon_slayer): change this so that when I change
  // to using an array for audio and sound then it loads them
  // one by one
  wave = LoadWave(audio_name);
  sound = LoadSoundFromWave(wave);
}

UIElement::UIElement(Font *_font) { font = _font; }

Progressbar::Progressbar(Font *font) : UIElement(font) {}
Button::Button(Font *font) : UIElement(font) {}
Label::Label(Font *font) : UIElement(font) {}

Menu::Menu() {}

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

UIEngine::UIEngine(Loader *l) {
  Font *font = l->getFont();
  menus[PAUSE_MENU] = new MenuPause(font);
  menus[INVENTORY] = new MenuInventory(font);
  menus[MAIN_MENU] = new MenuMain(font);
  menus[HUD] = new MenuHUD(font);
}
