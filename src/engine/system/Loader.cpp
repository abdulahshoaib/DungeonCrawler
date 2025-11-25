
#include "Loader.h"

Texture2D Loader::MainMenuBackground = {0};
Font Loader::TitleFont = {0};
Font Loader::ButtonFont = {0};

void Loader::LoadAssets()
{
    // TODO(demon_slayer): Add a config file to manage asset paths
    MainMenuBackground = LoadTexture("assets/images/menu_bg.png");

    TitleFont = LoadFontEx("assets/fonts/titleFont.otf", 160, 0, 0);
    ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 160, 0, 0);
}

void Loader::UnloadAssets()
{
    // unload textures
    UnloadTexture(MainMenuBackground);

    // unload fonts
    UnloadFont(TitleFont);
    UnloadFont(ButtonFont);
}