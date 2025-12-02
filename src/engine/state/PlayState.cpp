#include "PlayState.h"

// TODO(demon_slayer) add a way to make sure ID and the Potraits match
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