
#include "Loader.h"

Texture2D Loader::MainMenuBackground = {0};
Font Loader::TitleFont = {0};
Font Loader::ButtonFont = {0};

void Loader::LoadAssets()
{
    // TODO(demon_slayer): Add a config file to manage asset paths
    // Menu Background
    MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
    // Fonts
    TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 160, 0, 0);
    ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 160, 0, 0);

    // CHARACTERS
    blackWerewolf.LoadTex();
    yamabushiTengu.LoadTex();
    karasuTengu.LoadTex();
    kitsune.LoadTex();

    knight1.LoadTex();
    knight2.LoadTex();
    knight3.LoadTex();

    samurai.LoadTex();
    samuraiArcher.LoadTex();
    samuraiCommander.LoadTex();

    satyr.LoadTex();

    skeletonArcher.LoadTex();
    skeletonWarrior.LoadTex();
    skeletonSpearman.LoadTex();
}

void Loader::UnloadAssets()
{
    // unload textures
    UnloadTexture(MainMenuBackground);

    // unload fonts
    UnloadFont(TitleFont);
    UnloadFont(ButtonFont);

    // Unload Characters
    blackWerewolf.UnloadTex();

    yamabushiTengu.UnloadTex();
    karasuTengu.UnloadTex();
    kitsune.UnloadTex();

    knight1.UnloadTex();
    knight2.UnloadTex();
    knight3.UnloadTex();

    samurai.UnloadTex();
    samuraiArcher.UnloadTex();
    samuraiCommander.UnloadTex();

    satyr.UnloadTex();

    skeletonArcher.UnloadTex();
    skeletonWarrior.UnloadTex();
    skeletonSpearman.UnloadTex();
}