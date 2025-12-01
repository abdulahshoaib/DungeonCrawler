#include "NewGameState.h"

void NewGameState::Update(Engine &engine)
{
    newGameMenu.HandleInput(engine);
}

void NewGameState::Draw(Engine &)
{
    newGameMenu.Draw();
}
