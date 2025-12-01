#include "PlayState.h"
#include "Engine.h"
#include "SettingsState.h"
#include "NewGameState.h"
#include "MenuMain.h"
#include "LoadGameState.h"
#include "EnterNameState.h"
#include "Audio.h"

void MenuMain::Draw()
{
    float scale = 0.8f;
    Vector2 bgPosition = {0, 0};
    Texture2D bgTex = Loader::MainMenuBackground;
    DrawTextureEx(bgTex, bgPosition, 0.0f, scale, WHITE);

    int screenWidth = 1100;

    float cx = screenWidth / 2;
    float cy = 150.0f;
    int titleFontSize = 72;

    Font titleFont = Loader::TitleFont;

    std::string title = "Dungeon Crawler";

    Vector2 size = MeasureTextEx(titleFont, title.c_str(), titleFontSize, 2);
    Vector2 titleTextPos = {cx - (size.x / 2.0f), cy};

    Rectangle NewGameRect = {cx - (200 / 2), titleTextPos.y + 200, 200, 50};
    Rectangle LoadGameRect = {cx - (200 / 2), NewGameRect.y + NewGameRect.height + 10, 200, 50};
    Rectangle SettingsRect = {cx - (200 / 2), LoadGameRect.y + LoadGameRect.height + 10, 200, 50};
    Rectangle QuitRect = {cx - (200 / 2), SettingsRect.y + SettingsRect.height + 10, 200, 50};

    titleLabel.fontSize = titleFontSize;
    titleLabel.text = title;
    titleLabel.position = titleTextPos;
    titleLabel.Draw(WHITE);

    NewGame_btn.label.text = "NEW GAME";
    NewGame_btn.rect = NewGameRect;
    NewGame_btn.Draw(GRAY, GREEN);

    LoadGame_btn.label.text = "LOAD GAME";
    LoadGame_btn.rect = LoadGameRect;
    LoadGame_btn.Draw(GRAY, ORANGE);

    Settings_btn.label.text = "SETTINGS";
    Settings_btn.rect = SettingsRect;
    Settings_btn.Draw(GRAY, BLUE);

    Quit_btn.label.text = "QUIT";
    Quit_btn.rect = QuitRect;
    Quit_btn.Draw(GRAY, RED);
}

void MenuMain::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    Vector2 mousePoint = GetMousePosition();

    // 1. Play SFX on interactions
    if (clicked)
    {
        // Check if any button was clicked to play sound
        if (CheckCollisionPointRec(mousePoint, NewGame_btn.rect) ||
            CheckCollisionPointRec(mousePoint, LoadGame_btn.rect) ||
            CheckCollisionPointRec(mousePoint, Settings_btn.rect) ||
            CheckCollisionPointRec(mousePoint, Quit_btn.rect))
        {
            // Loader::udioSys.PlaySFX("Click"); // Ensure you loaded "Click" in Loader
        }
    }

    // 2. State Switching Logic
    if (clicked && CheckCollisionPointRec(mousePoint, NewGame_btn.rect))
        engine.ChangeState(new EnterNameState());

    if (clicked && CheckCollisionPointRec(mousePoint, LoadGame_btn.rect))
        engine.ChangeState(new LoadGameState());

    if (clicked && CheckCollisionPointRec(mousePoint, Settings_btn.rect))
        engine.ChangeState(new SettingsState());

    if (clicked && CheckCollisionPointRec(mousePoint, Quit_btn.rect))
        CloseWindow();
}