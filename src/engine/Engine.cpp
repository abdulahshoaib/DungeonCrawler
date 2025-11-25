#include "Engine.h"

Engine::~Engine()
{
  delete gameState;
  Loader::UnloadAssets();
}

void Engine::init(Screen screen)
{
  // NOTE(demon_slayer): InitWindow(screen.width, screen.height, "game");
  InitWindow(screen.width, screen.height, "game");
  gameState = new LoadingState();
}

void Engine::run()
{

  while (!WindowShouldClose())
  {
    gameState->Update(*this);
    BeginDrawing();
    ClearBackground(BLACK);
    gameState->Draw(*this);
    EndDrawing();
  }
  CloseWindow();
}

void Engine::ChangeState(GameState *gameState)
{
  delete this->gameState;
  this->gameState = gameState;
}

Engine::Engine()
{
  gameState = nullptr;
}