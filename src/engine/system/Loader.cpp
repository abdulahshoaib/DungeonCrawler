
#include "Loader.h"

// Create ONE instance of each character class
Black_werewolf   loader_bw;
Yamabushi_tengu  loader_yt;
Karasu_tengu     loader_kt;
Kitsune          loader_kitsune;

Knight1 loader_knight1;
Knight2 loader_knight2;
Knight3 loader_knight3;

Red_werewolf   loader_rw;
White_werewolf loader_ww;

Samurai            loader_samurai;
Samurai_archer     loader_samurai_archer;
Samurai_Commander  loader_samurai_commander;

Satyr_enemy       loader_satyr;
Skeleton_archer   loader_sk_archer;
Skeleton_warrior  loader_sk_warrior;
Skeleton_spearman loader_sk_spear;

Texture2D Loader::MainMenuBackground = {0};
Texture2D Loader::map = {0};
Texture2D Loader::torch = {0};
Font Loader::TitleFont = {0};
Font Loader::ButtonFont = {0};

void Loader::LoadAssets()
{
    // TODO(demon_slayer): Add a config file to manage asset paths
    // Menu Background
    MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
    map = LoadTexture("assets/maps/map.png");
    torch = LoadTexture("assets/maps/torch.png");
    // Fonts
    TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 160, 0, 0);
    ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 160, 0, 0);

    // CHARACTERS
    loader_bw.LoadTex();
    loader_yt.LoadTex();
    loader_kt.LoadTex();
    loader_kitsune.LoadTex();

    loader_knight1.LoadTex();
    loader_knight2.LoadTex();
    loader_knight3.LoadTex();

    loader_rw.LoadTex();
    loader_ww.LoadTex();

    loader_samurai.LoadTex();
    loader_samurai_archer.LoadTex();
    loader_samurai_commander.LoadTex();

    loader_satyr.LoadTex();
    loader_sk_archer.LoadTex();
    loader_sk_warrior.LoadTex();
    loader_sk_spear.LoadTex();
}

void Loader::UnloadAssets()
{
    // unload textures
    UnloadTexture(MainMenuBackground);
    UnloadTexture(map);
    UnloadTexture(torch);

    // unload fonts
    UnloadFont(TitleFont);
    UnloadFont(ButtonFont);


    loader_bw.UnloadTex();
    loader_yt.UnloadTex();
    loader_kt.UnloadTex();
    loader_kitsune.UnloadTex();

    loader_knight1.UnloadTex();
    loader_knight2.UnloadTex();
    loader_knight3.UnloadTex();

    loader_rw.UnloadTex();
    loader_ww.UnloadTex();

    loader_samurai.UnloadTex();
    loader_samurai_archer.UnloadTex();
    loader_samurai_commander.UnloadTex();

    loader_satyr.UnloadTex();
    loader_sk_archer.UnloadTex();
    loader_sk_warrior.UnloadTex();
    loader_sk_spear.UnloadTex();
}