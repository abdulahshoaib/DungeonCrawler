#include "Engine.h"
#include "Loader.h"
#include "Audio.h"

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

  Audio::Init();

  gameState = new LoadingState();
}

void Engine::run()
{
  while (!WindowShouldClose())
  {
    Audio::Update();
    gameState->Update(*this);

    BeginDrawing();
    ClearBackground(BLACK);
    gameState->Draw(*this);
    EndDrawing();
  }
  CloseWindow();
}

void Engine::ChangeState(GameState *newGameState)
{
  delete this->gameState;
  this->gameState = newGameState;
  gameState->Enter(*this);
}