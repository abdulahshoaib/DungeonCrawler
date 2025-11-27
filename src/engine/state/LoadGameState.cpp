#include "LoadGameState.h"

LoadGameState::~LoadGameState()
{
}

void LoadGameState::Update(Engine &engine)
{
    loadGameMenu.HandleInput(engine);
}

void LoadGameState::Draw(Engine &)
{
    loadGameMenu.Draw();
}