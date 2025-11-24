#include "MainMenuState.h"

void MainMenuState::Update(Engine &engine)
{
    mainMenu.HandleInput(engine);
}

void MainMenuState::Draw(Engine &engine)
{
    mainMenu.Draw();
}