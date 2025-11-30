#include "Engine.h"
#include "Loader.h" // <--- 1. Include this so you can access AudioSys

Engine::Engine()
{
  gameState = nullptr;
}

Engine::~Engine()
{
  delete gameState;

  Audio::Clean();
  Loader::UnloadAssets();
}

void Engine::init(Screen screen)
{
  InitWindow(screen.width, screen.height, "game");

  // 3. Initialize Audio Device (Must happen after InitWindow usually)
  Audio::Init();

  gameState = new LoadingState();
}

void Engine::run()
{
  while (!WindowShouldClose())
  {
    // 4. CRITICAL: Update Audio Stream
    // If you forget this line, music will stutter or stop!
    Audio::Update();
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