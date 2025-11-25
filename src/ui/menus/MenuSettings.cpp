#include "MenuSettings.h"
#include "Engine.h"
#include "Loader.h"

MenuSettings::MenuSettings()
{
}

void MenuSettings::Draw()
{
    Texture2D bg = Loader::MainMenuBackground;
    DrawTextureEx(bg, {0, 0}, 0.0f, 0.8f, WHITE);

    Vol_btn.label.text = "Mute";
    Vol_btn.rect = {100, 100, 200, 50};
    Vol_btn.Draw(GREEN, DARKGREEN);

    Back_btn.label.text = "Back";
    Back_btn.rect = {100, 200, 200, 50};
    Back_btn.Draw(GRAY, BLACK);
}

void MenuSettings::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (clicked && CheckCollisionPointRec(GetMousePosition(), Back_btn.rect))
    {
        // WARN(demon_slayer): this crashes the game, fix
        // engine.ChangeState(new MainMenuState());
    }
}