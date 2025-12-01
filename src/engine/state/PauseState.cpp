#include "PauseState.h"
#include "Audio.h"

void PauseState::Enter(Engine &)
{
    Audio::Play(LEVEL_MUSIC);
}

void PauseState::Update(Engine &engine)
{
    pauseMenu.HandleInput(engine);
}

void PauseState::Draw(Engine &engine)
{
    pauseMenu.Draw();
}