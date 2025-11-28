#include "MenuLoadGame.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"
#include "MainMenuState.h"

MenuLoadGame::MenuLoadGame()
{
}
void MenuLoadGame::Draw()
{
    DrawTextureEx(Loader::LoadMenuBackground, {0, 0}, 0, 0.9f, WHITE);
}
void MenuLoadGame::HandleInput(Engine &engine)
{
    if (IsKeyPressed(KEY_B))
    {
        // For demonstration, we directly go to PlayState with a dummy save slot
        engine.ChangeState(new MainMenuState()); // Assuming '1' is the loaded save slot
    }
}