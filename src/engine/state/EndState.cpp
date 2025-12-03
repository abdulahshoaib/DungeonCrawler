#include "EndState.h"
#include "Engine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "system/GameProgress.h"
#include "system/Audio.h"
#include "system/Loader.h"
#include <raylib.h>
#include <cstdio>

EndState::EndState(int kills, int coins)
{
    enemiesKilled = kills;
    coinsCollected = coins;
    snprintf(statsKills, sizeof(statsKills), "Enemies Killed: %d", enemiesKilled);
    snprintf(statsCoins, sizeof(statsCoins), "Coins Collected: %d", coinsCollected);
}

void EndState::Enter(Engine &)
{
    Audio::PlaySFx(BUTTON_HOVER);
}

void EndState::Update(Engine &engine)
{
    Vector2 mouse = GetMousePosition();

    // Quit
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, quitBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.RequestExit();
    }

    // Main Menu
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, menuBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.ChangeState(new MainMenuState());
    }

    // Retry
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, retryBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        int cid = GameProgress::GetCharacterID();
        engine.ChangeState(new PlayState(cid));
    }
}

void EndState::Draw(Engine &engine)
{
    // First draw underlying state (the play state) so level remains visible
    GameState *prev = engine.GetPreviousState();
    if (prev)
        prev->Draw(engine);
    // Minimal slate overlay
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    float cx = screenW / 2.0f;

    // Dim the background slightly so the slate stands out
    DrawRectangle(0, 0, screenW, screenH, (Color){0, 0, 0, 160});

    // Slate panel
    float panelWidth = screenW * 0.58f;
    if (panelWidth < 480.0f) panelWidth = 480.0f;
    float panelHeight = 220.0f;
    Rectangle panelRect = {cx - panelWidth / 2.0f, screenH / 2.0f - panelHeight / 2.0f + 14.0f, panelWidth, panelHeight};
    DrawRectangleRounded(panelRect, 0.12f, 6, (Color){28, 30, 34, 230});
    DrawRectangleRoundedLines(panelRect, 0.12f, 6, Fade(WHITE, 0.06f));

    // Title above the slate
    const char *title = "DUNGEON COMPLETED";
    float titleSize = 40.0f;
    Vector2 titleMeasure = MeasureTextEx(Loader::TitleFont, title, titleSize, 2);
    DrawTextEx(Loader::TitleFont, title, {cx - titleMeasure.x / 2.0f, panelRect.y - titleMeasure.y - 18.0f}, titleSize, 2, (Color){235, 230, 215, 255});

    // Simple stats on the slate
    char buf1[64];
    char buf2[64];
    snprintf(buf1, sizeof(buf1), "Enemies: %d", enemiesKilled);
    snprintf(buf2, sizeof(buf2), "Coins: %d", coinsCollected);
    float statSize = 28.0f;
    Vector2 m1 = MeasureTextEx(Loader::TitleFont, buf1, statSize, 1);
    Vector2 m2 = MeasureTextEx(Loader::TitleFont, buf2, statSize, 1);
    DrawTextEx(Loader::TitleFont, buf1, {cx - m1.x / 2.0f, panelRect.y + 36.0f}, statSize, 1, Fade(WHITE, 0.92f));
    DrawTextEx(Loader::TitleFont, buf2, {cx - m2.x / 2.0f, panelRect.y + 36.0f + 40.0f}, statSize, 1, Fade(WHITE, 0.92f));

    // Tagline small note on slate bottom
    const char *note = "The slate records your deeds";
    float noteSize = 16.0f;
    Vector2 nm = MeasureTextEx(Loader::TitleFont, note, noteSize, 1);
    DrawTextEx(Loader::TitleFont, note, {cx - nm.x / 2.0f, panelRect.y + panelRect.height - 30.0f}, noteSize, 1, Fade(WHITE, 0.6f));

    // Buttons below the slate (vertical stack)
    float bw = 220.0f;
    float bh = 56.0f;
    float spacing = 18.0f;
    float startY = panelRect.y + panelRect.height + 18.0f;

    retryBtn.rect = {cx - bw / 2.0f, startY, bw, bh};
    retryBtn.label.text = "RETRY";
    retryBtn.Draw(GRAY, GREEN);

    menuBtn.rect = {cx - bw / 2.0f, startY + bh + spacing, bw, bh};
    menuBtn.label.text = "MAIN MENU";
    menuBtn.Draw(GRAY, ORANGE);

    quitBtn.rect = {cx - bw / 2.0f, startY + (bh + spacing) * 2.0f, bw, bh};
    quitBtn.label.text = "QUIT";
    quitBtn.Draw(GRAY, RED);
}
