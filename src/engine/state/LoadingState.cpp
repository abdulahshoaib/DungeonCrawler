#include "LoadingState.h"
#include "Loader.h"
#include "MainMenuState.h"

#define TOTAL_STEPS 17

void LoadingState::Update(Engine &engine)
{
    Loader::TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 48, 0, 0);
    switch (step)
    {
    case 0:
    {
        Loader::knight1Potrait = LoadTexture("assets/images/Knight1.png");
        Loader::knight2Potrait = LoadTexture("assets/images/Knight2.png");
        Loader::knight3Potrait = LoadTexture("assets/images/Knight3.png");

        Loader::samuraiPotrait = LoadTexture("assets/images/Samurai.png");
        Loader::samuraiArcherPotrait = LoadTexture("assets/images/Samurai_Archer.png");
        Loader::samuraiCommanderPotrait = LoadTexture("assets/images/Samurai_Commander.png");
        Loader::MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
        break;
    }
    case 1:
        Loader::TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 70, 0, 0);
        break;
    case 2:
        Loader::ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 32, 0, 0);
        break;

    case 3:
        Loader::blackWerewolf.LoadTex();
        break;
    case 4:
        Loader::yamabushiTengu.LoadTex();
        break;
    case 5:
        Loader::karasuTengu.LoadTex();
        break;
    case 6:
        Loader::kitsune.LoadTex();
        break;

    case 7:
        Loader::knight1.LoadTex();
        break;
    case 8:
        Loader::knight2.LoadTex();
        break;
    case 9:
        Loader::knight3.LoadTex();
        break;

    case 10:
        Loader::samurai.LoadTex();
        break;
    case 11:
        Loader::samuraiArcher.LoadTex();
        break;
    case 12:
        Loader::samuraiCommander.LoadTex();
        break;

    case 13:
        Loader::satyr.LoadTex();
        break;

    case 14:
        Loader::skeletonArcher.LoadTex();
        break;
    case 15:
        Loader::skeletonWarrior.LoadTex();
        break;
    case 16:
        Loader::skeletonSpearman.LoadTex();
        break;

    default:
        engine.ChangeState(new MainMenuState());
        return;
    }

    step++;
}

void LoadingState::Draw(Engine &)
{
    ClearBackground(BLACK);
    float progress = (float)step / TOTAL_STEPS;

    DrawTextEx(Loader::TitleFont, "Loading", {450, 300}, 40, 2, WHITE);

    // Loading Bar
    DrawRectangle(300, 500, 500, 5, GRAY);
    DrawRectangle(300, 500, (int)(500 * progress), 5, DARKGREEN);
}