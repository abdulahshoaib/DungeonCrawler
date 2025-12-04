#include "LoadingState.h"
#include "Loader.h"
#include "Audio.h"
#include "MainMenuState.h"
#include "PlayState.h"

#define TOTAL_STEPS 17

void LoadingState::Update(Engine &engine)
{
#ifdef DEBUG
    // DEBUG: Skip loading with CTRL+SHIFT+D
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_D))
    {
        engine.ChangeState(new PlayState(1)); // Default to Knight1
        return;
    }
#endif

    Loader::LoadFont();
    switch (step)
    {
    case 0:
        Loader::LoadSpecialItems();
        break;

    case 1:
        Loader::LoadSkeletonWarrior();
        break;

    case 2:
        Loader::LoadSkeletonSpearman();
        break;

    case 3:
        Loader::LoadKnight1();
        break;

    case 4:
        Loader::LoadKnight2();
        break;

    case 5:
        Loader::LoadKnight3();
        break;

    case 6:
        Loader::LoadSamurai();
        break;

    case 7:
        Loader::LoadSamuraiArcher();
        break;

    case 8:
        Loader::LoadSamuraiCommander();
        break;

    case 9:
        Loader::LoadKarasuTengu();
        break;

    case 10:
        Loader::LoadYamabushiTengu();
        break;

    case 11:
        Loader::LoadBackgrounds();
        break;

    case 12:
        Loader::LoadCollectables();
        break;

    case 13:
        Loader::LoadHUDPotraits();
        break;

    case 14:
        Loader::LoadPotraitCards();
        break;

    case 15:
        Loader::LoadSkeletonArcher();
        break;

    case 16:
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