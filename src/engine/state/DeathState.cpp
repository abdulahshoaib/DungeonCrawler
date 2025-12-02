#include "DeathState.h"
#include "Engine.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "system/GameProgress.h"
#include "system/Audio.h"
#include "system/Loader.h"
#include <raylib.h>

void DeathState::Enter(Engine &)
{
    // Optionally play a death SFX or stop music
    Audio::PlaySFx(BUTTON_HOVER);
}

void DeathState::Update(Engine &engine)
{
    Vector2 mouse = GetMousePosition();

    // Quit
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, quitBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.RequestExit();
    }

    // Quit to menu
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, menuBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.ChangeState(new MainMenuState());
    }

    // Replay
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, replayBtn.rect))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        int cid = GameProgress::GetCharacterID();
        engine.ChangeState(new PlayState(cid));
    }
}

void DeathState::Draw(Engine &engine)
{
    // First draw underlying state (the play state) so player death frame remains visible
    GameState *prev = engine.GetPreviousState();
    if (prev)
    {
        prev->Draw(engine);
    }

    // Dark overlay
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 180});

    // Center panel
    const char *title = "YOU DIED";
    float titleSize = 64.0f;
    Vector2 ts = MeasureTextEx(Loader::TitleFont, title, titleSize, 2);
    float cx = GetScreenWidth() / 2.0f;
    float cy = GetScreenHeight() / 2.0f - 120.0f;

    DrawTextEx(Loader::TitleFont, title, {cx - ts.x / 2, cy}, titleSize, 2, (Color){255, 100, 100, 255});

    // Setup buttons if not initialized (positioning here is fine)
    float bw = 240.0f;
    float bh = 56.0f;
    float spacing = 24.0f;
    float startY = cy + 80.0f;

    replayBtn.rect = {cx - bw / 2, startY, bw, bh};
    replayBtn.label.text = "REPLAY";
    replayBtn.Draw(GRAY, GREEN);

    menuBtn.rect = {cx - bw / 2, startY + bh + spacing, bw, bh};
    menuBtn.label.text = "MAIN MENU";
    menuBtn.Draw(GRAY, ORANGE);

    quitBtn.rect = {cx - bw / 2, startY + (bh + spacing) * 2, bw, bh};
    quitBtn.label.text = "QUIT";
    quitBtn.Draw(GRAY, RED);
}
