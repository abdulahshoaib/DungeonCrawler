#include "LoadGameState.h"

void LoadGameState::Update(Engine &engine)
{
    loadGameMenu.HandleInput(engine);
}

void LoadGameState::Draw(Engine &)
{
    loadGameMenu.Draw();
}