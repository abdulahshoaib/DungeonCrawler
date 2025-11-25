
#include "Loader.h"

Texture2D Loader::MainMenuBackground = {0};
Font Loader::TitleFont = {0};
Font Loader::ButtonFont = {0};
Font Loader::TitleFont2 = {0};
// Knight textures must also be defined here:
Texture2D Loader::knight1_attack1 = {0};
Texture2D Loader::knight1_attack2 = {0};
Texture2D Loader::knight1_attack3 = {0};
Texture2D Loader::knight1_dead = {0};
Texture2D Loader::knight1_defend = {0};
Texture2D Loader::knight1_hurt = {0};
Texture2D Loader::knight1_idle = {0};
Texture2D Loader::knight1_jump = {0};
Texture2D Loader::knight1_protect = {0};
Texture2D Loader::knight1_run = {0};
Texture2D Loader::knight1_runattack = {0};
Texture2D Loader::knight1_walk = {0};

Texture2D Loader::knight2_attack1 = {0};
Texture2D Loader::knight2_attack2 = {0};
Texture2D Loader::knight2_attack3 = {0};
Texture2D Loader::knight2_dead = {0};
Texture2D Loader::knight2_defend = {0};
Texture2D Loader::knight2_hurt = {0};
Texture2D Loader::knight2_idle = {0};
Texture2D Loader::knight2_jump = {0};
Texture2D Loader::knight2_protect = {0};
Texture2D Loader::knight2_run = {0};
Texture2D Loader::knight2_runattack = {0};
Texture2D Loader::knight2_walk = {0};

Texture2D Loader::knight3_attack1 = {0};
Texture2D Loader::knight3_attack2 = {0};
Texture2D Loader::knight3_attack3 = {0};
Texture2D Loader::knight3_dead = {0};
Texture2D Loader::knight3_defend = {0};
Texture2D Loader::knight3_hurt = {0};
Texture2D Loader::knight3_idle = {0};
Texture2D Loader::knight3_jump = {0};
Texture2D Loader::knight3_protect = {0};
Texture2D Loader::knight3_run = {0};
Texture2D Loader::knight3_runattack = {0};
Texture2D Loader::knight3_walk = {0};

void Loader::Load_knight_assests()
{
    knight1_attack1   = LoadTexture("assets/knight/knight1/attack1.png");
    knight1_attack2   = LoadTexture("assets/knight/knight1/attack2.png");
    knight1_attack3   = LoadTexture("assets/knight/knight1/attack3.png");
    knight1_dead      = LoadTexture("assets/knight/knight1/dead.png");
    knight1_defend    = LoadTexture("assets/knight/knight1/defend.png");
    knight1_hurt      = LoadTexture("assets/knight/knight1/hurt.png");
    knight1_idle      = LoadTexture("assets/knight/knight1/idle.png");
    knight1_jump      = LoadTexture("assets/knight/knight1/jump.png");
    knight1_protect   = LoadTexture("assets/knight/knight1/protect.png");
    knight1_run       = LoadTexture("assets/knight/knight1/run.png");
    knight1_runattack = LoadTexture("assets/knight/knight1/runattack.png");
    knight1_walk      = LoadTexture("assets/knight/knight1/walk.png");
    knight2_attack1   = LoadTexture("assets/knight/knight2/attack1.png");
    knight2_attack2   = LoadTexture("assets/knight/knight2/attack2.png");
    knight2_attack3   = LoadTexture("assets/knight/knight2/attack3.png");
    knight2_dead      = LoadTexture("assets/knight/knight2/dead.png");
    knight2_defend    = LoadTexture("assets/knight/knight2/defend.png");
    knight2_hurt      = LoadTexture("assets/knight/knight2/hurt.png");
    knight2_idle      = LoadTexture("assets/knight/knight2/idle.png");
    knight2_jump      = LoadTexture("assets/knight/knight2/jump.png");
    knight2_protect   = LoadTexture("assets/knight/knight2/protect.png");
    knight2_run       = LoadTexture("assets/knight/knight2/run.png");
    knight2_runattack = LoadTexture("assets/knight/knight2/runattack.png");
    knight2_walk      = LoadTexture("assets/knight/knight2/walk.png");
    knight3_attack1   = LoadTexture("assets/knight/knight3/attack1.png");
    knight3_attack2   = LoadTexture("assets/knight/knight3/attack2.png");
    knight3_attack3   = LoadTexture("assets/knight/knight3/attack3.png");
    knight3_dead      = LoadTexture("assets/knight/knight3/dead.png");
    knight3_defend    = LoadTexture("assets/knight/knight3/defend.png");
    knight3_hurt      = LoadTexture("assets/knight/knight3/hurt.png");
    knight3_idle      = LoadTexture("assets/knight/knight3/idle.png");
    knight3_jump      = LoadTexture("assets/knight/knight3/jump.png");
    knight3_protect   = LoadTexture("assets/knight/knight3/protect.png");
    knight3_run       = LoadTexture("assets/knight/knight3/run.png");
    knight3_runattack = LoadTexture("assets/knight/knight3/runattack.png");
    knight3_walk      = LoadTexture("assets/knight/knight3/walk.png");
}
void Loader::LoadAssets()
{
    // TODO(demon_slayer): Add a config file to manage asset paths
    //Menu Background
    MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
    //Fonts
    TitleFont = LoadFontEx("assets/fonts/titleFont.otf", 160, 0, 0);
    ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 160, 0, 0);
    TitleFont2 = LoadFontEx("assets/fonts/StarCrush.otf", 160, 0, 0);
    //Knights
    //Knight 1
    Load_knight_assests();

}

void Loader::UnloadAssets()
{
    // unload textures
    UnloadTexture(MainMenuBackground);

    // unload fonts
    UnloadFont(TitleFont);
    UnloadFont(ButtonFont);
    UnloadFont(TitleFont2);
}