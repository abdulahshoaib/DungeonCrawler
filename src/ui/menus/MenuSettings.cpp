#include "MenuSettings.h"
#include "Loader.h"

MenuSettings::MenuSettings()
{
}

void MenuSettings::Draw()
{
    Texture2D bg = Loader::MainMenuBackground;
    Vol_btn.label.text = "Mute";
    Vol_btn.rect = {100, 100, 200, 50};
    Vol_btn.Draw(GREEN, DARKGREEN);
}

void MenuSettings::HandleInput(Engine &)
{
}
