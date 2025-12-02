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
  Audio::Load();
  Audio::Play(MAIN_MENU_MUSIC);

  SetExitKey(KEY_NULL);

  gameState = new LoadingState();
}

void Engine::run()
{
  while (!WindowShouldClose() && !exitRequested)
  {
    Audio::Update();
    gameState->Update(*this);

    BeginDrawing();
    ClearBackground(BLACK);
    gameState->Draw(*this);
    EndDrawing();
  }
  // Only close the window if it is still ready. Some UI code may call
  // CloseWindow() (e.g., quit button) which would make a second call
  // here and produce GLFW "not initialized" warnings. Guard to avoid that.
  if (IsWindowReady())
  {
    CloseWindow();
  }
}

void Engine::ChangeState(GameState *newGameState)
{
  delete this->gameState;
  this->gameState = newGameState;
  gameState->Enter(*this);
}

void Engine::PopState()
{
  if (previousState != nullptr)
  {
    delete gameState;
    gameState = previousState;
    previousState = nullptr;
    // Note: Don't call Enter() again, just resume
  }
}

void Engine::PushState(GameState *newGameState)
{
  // Store current state as previous
  previousState = gameState;
  gameState = newGameState;
  gameState->Enter(*this);
}

// GetPreviousState is implemented inline in the header
