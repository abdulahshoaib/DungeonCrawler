
#include "Loader.h"

Texture2D Loader::MainMenuBackground = {0};
Font Loader::TitleFont = {0};
Font Loader::ButtonFont = {0};

Black_werewolf Loader::blackWerewolf;

Yamabushi_tengu Loader::yamabushiTengu;
Karasu_tengu Loader::karasuTengu;
Kitsune Loader::kitsune;

Knight1 Loader::knight1;
Knight2 Loader::knight2;
Knight3 Loader::knight3;

Samurai Loader::samurai;
Samurai_archer Loader::samuraiArcher;
Samurai_Commander Loader::samuraiCommander;

Satyr_enemy Loader::satyr;

Skeleton_archer Loader::skeletonArcher;
Skeleton_warrior Loader::skeletonWarrior;
Skeleton_spearman Loader::skeletonSpearman;

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
}