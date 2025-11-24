#include "PauseState.h"

void PauseState::Update(Engine &engine)
{
    pauseMenu.HandleInput(engine);
}

void PauseState::Draw(Engine &engine)
{
    pauseMenu.Draw();
}