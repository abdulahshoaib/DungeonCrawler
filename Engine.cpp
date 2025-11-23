#include "Engine.h"

Engine::~Engine() {}

void Engine::init(Screen screen)
{
  InitWindow(screen.width, screen.height, "game");
  gameState = GameState::MENU;
  // TODO(demon_slayer): load the assets
}

void Engine::run()
{

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    // TODO(demon_slayer): I don't like how this
    // state management is handled
    if (gameState == GameState::MENU)
      ui_engine.menus[MAIN_MENU]->Draw();

    if (gameState == GameState::GAME_LOOP)
    {

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

      switch (key)
      {
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

Engine::Engine()
{
  // UI
}