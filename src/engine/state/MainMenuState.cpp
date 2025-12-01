#include "MainMenuState.h"
#include "Audio.h"

void MainMenuState::Enter(Engine &)
{
    Audio::Play(MAIN_MENU_MUSIC);
}

void MainMenuState::Update(Engine &engine)
{
    mainMenu.HandleInput(engine);
}

void MainMenuState::Draw(Engine &engine)
{
    mainMenu.Draw();
}