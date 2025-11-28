
#include "Loader.h"

Texture2D Loader::MainMenuBackground = {0};
Texture2D Loader::SelectionMenuBackground = {0};
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

Texture2D Loader::knight1Potrait;
Texture2D Loader::knight2Potrait;
Texture2D Loader::knight3Potrait;

Texture2D Loader::samuraiPotrait;
Texture2D Loader::samuraiArcherPotrait;
Texture2D Loader::samuraiCommanderPotrait;
Texture2D Loader::NewButton;

void Loader::UnloadAssets()
{
    // unload textures
    UnloadTexture(MainMenuBackground);
    UnloadTexture(SelectionMenuBackground);

    // unload fonts
    UnloadFont(TitleFont);
    UnloadFont(ButtonFont);
}