#include "PlayState.h"

PlayState::PlayState()
{
}

void PlayState::Update(Engine &engine)
{
    gameManager.Update();
}

void PlayState::Draw(Engine &engine)
{
    gameManager.Draw();
}