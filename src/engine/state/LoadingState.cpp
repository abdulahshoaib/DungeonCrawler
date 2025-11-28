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
        Loader::LoadMenuBackground = LoadTexture("assets/images/loadmenubg.jpeg");
        Loader::SelectionMenuBackground = LoadTexture("assets/images/selection_bg.png");
        break;
    }
    case 1:
        Loader::TitleFont = LoadFontEx("assets/fonts/StarCrush.otf", 70, 0, 0);
        break;
    case 2:
    {
        Loader::Coin = LoadTexture("assets/images/coin.png");
        Loader::CoinAnim = LoadTexture("assets/images/coinAnim.png");
        Loader::ButtonFont = LoadFontEx("assets/fonts/Roboto.ttf", 32, 0, 0);
        break;
    }
    case 3:
        Loader::blackWerewolf.LoadTex();
        break;
    case 4:
    {
        Loader::yamabushiTengu.LoadTex();

        Loader::samuraiPotrait = LoadTexture("assets/images/Samurai.png");
        Loader::samuraiArcherPotrait = LoadTexture("assets/images/Samurai_Archer.png");
        Loader::samuraiCommanderPotrait = LoadTexture("assets/images/Samurai_Commander.png");
        Loader::MainMenuBackground = LoadTexture("assets/images/menu_bg.png");
        break;
    }
    case 5:
        Loader::karasuTengu.LoadTex();
        break;
    case 6:
    {
        Loader::knight1Potrait = LoadTexture("assets/images/Knight1.png");
        Loader::knight2Potrait = LoadTexture("assets/images/Knight2.png");
        Loader::knight3Potrait = LoadTexture("assets/images/Knight3.png");
        Loader::kitsune.LoadTex();
        break;
    }
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

    const int screenW = GetScreenWidth();
    const int screenH = GetScreenHeight();

    const char *msg = "Loading";
    const float fontSize = 40.0f;
    const float spacing = 2.0f;
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, msg, fontSize, spacing);
    Vector2 textPos = {(screenW - textSize.x) * 0.5f, screenH * 0.45f - textSize.y * 0.5f};

    DrawTextEx(Loader::TitleFont, msg, textPos, fontSize, spacing, WHITE);

    const int barWidth = 500;
    const int barHeight = 8;
    const int barX = (screenW - barWidth) / 2;
    const int barY = (int)(textPos.y + textSize.y + 20); // gap below text

    DrawRectangle(barX, barY, barWidth, barHeight, GRAY);
    DrawRectangle(barX, barY, (int)(barWidth * progress), barHeight, YELLOW);
}