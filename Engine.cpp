#include "Engine.h"

Engine::~Engine()
{
  delete gameState;
}

void Engine::init(Screen screen)
{
  InitWindow(screen.width, screen.height, "game");
  gameState = new MainMenuState();
  // TODO(demon_slayer): load the assets
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

Engine::Engine()
{
  // UI
}

void MainMenuState::Update(Engine &engine)
{
  mainMenu.HandleInput(engine);
}

void MainMenuState::Draw(Engine &engine)
{
  mainMenu.Draw();
}

void PlayState::Update(Engine &engine)
{
  // implement the game manager inputhandling
}

void PlayState::Draw(Engine &engine)
{
  // implement the game manager drawing
}

void PauseState::Update(Engine &engine)
{
  pauseMenu.HandleInput(engine);
}

void PauseState::Draw(Engine &engine)
{
  pauseMenu.Draw();
}

void SettingsState::Update(Engine &engine)
{
  settingsMenu.HandleInput(engine);
}

void SettingsState::Draw(Engine &)
{
  settingsMenu.Draw();
}