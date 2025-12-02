#include "PlayState.h"

PlayState::PlayState(int ID)
    : gameManager(ID)
{
}

void PlayState::Update(Engine &engine)
{
    gameManager.Update(engine);
}

void PlayState::Draw(Engine &engine)
{
    gameManager.Draw();
}