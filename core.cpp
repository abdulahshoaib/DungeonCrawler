#include "core.h"
#include <raylib.h>

Game::~Game() {
  delete window;
  delete player;
  delete ui;
  delete loader;
}

void Game::init(Screen screen) {
  window = new Window(screen.width, screen.height, screen.title);

  // TODO(demon_slayer): change these magic numbers
  player = new Player({200, 200}, {10, 10});

  Font f = LoadFont("roboto.ttf");
  loader = new Loader(f);

  ui = new UI(loader->getFont());

  gameState = MENU;

  // TODO(demon_slayer): load the assets
}

void Game::update() {

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // TODO(demon_slayer): I don't like how this
    // state management is handled
    if (gameState == MENU)
      ui->DrawMenu(gameState);
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
        player->move(0, -speed);
        break;
      case KEY_A:
        player->move(-speed, 0);
        break;
      case KEY_S:
        player->move(0, speed);
        break;
      case KEY_D:
        player->move(speed, 0);
        break;
      }

      DrawRectangleV(player->getPos(), player->getSize(), RED);
    }
    EndDrawing();
  }
  CloseWindow();
}

Game::Game() : window(nullptr) {}

Player::Player(Vector2 position, Vector2 size) : pos(position), size(size) {}

Vector2 Player::getPos() const { return pos; }
Vector2 Player::getSize() const { return size; }

void Player::move(float _x, float _y) {
  pos.x += _x;
  pos.y += _y;
}

Loader::Loader(Font f) : font(f) {}
Font *Loader::getFont() { return &font; } // just return a ref to the font

// MENU UI
void UI::DrawMenu(GameState &g) {
  DrawTextEx(*font, "Main Menu", {100, 100}, 30.0f, 3.0f, GREEN);
  DrawRectangleV({200, 200}, {50, 30}, GREEN);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
      (GetMousePosition().x > 200 && GetMousePosition().x < 250) &&
      (GetMousePosition().y > 200 && GetMousePosition().y < 230)) {
    g = GAME_LOOP;
  }
}

UI::UI(Font *_font) : font(_font) {}

Audio::~Audio() {
  UnloadWave(wave);
  CloseAudioDevice();
}

Audio::Audio(char *audio_name) {
  InitAudioDevice();

  // TODO(demon_slayer): change this so that when I change
  // to using an array for audio and sound then it loads them
  // one by one
  wave = LoadWave(audio_name);
  sound = LoadSoundFromWave(wave);
}
