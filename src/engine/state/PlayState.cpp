#include "PlayState.h"
#include "GameProgress.h"

PlayState::PlayState(int ID)
    : gameManager(ID)
{
    // Set the character ID in GameProgress so it gets saved
    GameProgress::SetCharacterID(ID);
}

void PlayState::Update(Engine &engine)
{
    gameManager.Update(engine);
}

void PlayState::Draw(Engine &engine)
{
    gameManager.Draw();
}