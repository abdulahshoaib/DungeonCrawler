// PauseState.cpp
#include "PauseState.h"
#include "Audio.h"
#include "GameProgress.h"
#include "PlayState.h"

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
    // Draw the game state underneath the pause menu
    GameState *prevState = engine.GetPreviousState();
    if (prevState)
    {
        prevState->Draw(engine);
    }
    
    // Draw semi-transparent overlay over the game
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 180});
    
    pauseMenu.Draw();
}