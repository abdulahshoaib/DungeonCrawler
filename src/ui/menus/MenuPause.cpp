// MenuPause.cpp
#include "MenuPause.h"
#include "GameProgress.h"
#include "../../engine/state/PlayState.h"
#include "Loader.h"
#include "Audio.h"
#include "MainMenuState.h"
#include "../UITheme.h"
#include <raylib.h>

MenuPause::MenuPause()
{
    SetupButtons();
}

void MenuPause::SetupButtons()
{
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    float buttonWidth = 300;
    float buttonHeight = 60;
    float startY = screenHeight / 2 - 50;
    float spacing = 80;

    // Resume Button
    resumeButton.rect = {screenWidth / 2 - buttonWidth / 2, startY, buttonWidth, buttonHeight};
    resumeButton.label.text = "RESUME";
    resumeButton.labelNormalColor = (Color){235, 220, 195, 255};
    resumeButton.labelHoverColor = (Color){255, 200, 100, 255};

    // Save Game Button
    saveGameButton.rect = {screenWidth / 2 - buttonWidth / 2, startY + spacing, buttonWidth, buttonHeight};
    saveGameButton.label.text = "SAVE GAME";
    saveGameButton.labelNormalColor = (Color){235, 220, 195, 255};
    saveGameButton.labelHoverColor = (Color){120, 255, 120, 255};

    // Main Menu Button
    mainMenuButton.rect = {screenWidth / 2 - buttonWidth / 2, startY + spacing * 2, buttonWidth, buttonHeight};
    mainMenuButton.label.text = "MAIN MENU";
    mainMenuButton.labelNormalColor = (Color){235, 220, 195, 255};
    mainMenuButton.labelHoverColor = (Color){255, 200, 100, 255};

    // Quit Button
    quitButton.rect = {screenWidth / 2 - buttonWidth / 2, startY + spacing * 3, buttonWidth, buttonHeight};
    quitButton.label.text = "QUIT GAME";
    quitButton.labelNormalColor = (Color){235, 220, 195, 255};
    quitButton.labelHoverColor = (Color){255, 100, 80, 255};

    // Store buttons for iteration
    buttons = {&resumeButton, &saveGameButton, &mainMenuButton, &quitButton};
}

void MenuPause::DrawPauseHeader()
{
    const char *title = "GAME PAUSED";
    float fontSize = 48.0f;
    Vector2 textSize = MeasureTextEx(Loader::TitleFont, title, fontSize, 2.0f);

    float x = GetScreenWidth() / 2 - textSize.x / 2;
    float y = 80;

    // Use consistent text rendering
    UITheme::TextEffects::DrawTextWithShadow(Loader::TitleFont, title, {x, y}, fontSize, 2.0f, UITheme::Colors::TEXT_TITLE);
}

void MenuPause::DrawPlayerInfo()
{
    float fontSize = 28.0f;
    float infoY = 180;

    // Slim player info box (only name + score)
    Rectangle infoBox = {(float)(GetScreenWidth() / 2) - 180, infoY - 10, 360, 80};

    // Use consistent panel drawing
    UITheme::Panels::DrawPanel(infoBox, false);

    // Player information (only name and score)
    std::string usernameText = GameProgress::GetUsername();
    std::string pointsText = "Score: " + std::to_string(GameProgress::GetPoints());

    float textX = GetScreenWidth() / 2;

    Vector2 usernameSize = MeasureTextEx(Loader::TitleFont, usernameText.c_str(), fontSize, 1.0f);
    UITheme::TextEffects::DrawTextWithShadow(Loader::TitleFont, usernameText,
                                             {textX - usernameSize.x / 2, infoY}, fontSize, 1.0f, UITheme::Colors::TEXT_PRIMARY);

    Vector2 pointsSize = MeasureTextEx(Loader::TitleFont, pointsText.c_str(), fontSize * 0.9f, 1.0f);
    UITheme::TextEffects::DrawTextWithShadow(Loader::TitleFont, pointsText,
                                             {textX - pointsSize.x / 2, infoY + 36}, fontSize * 0.9f, 1.0f, UITheme::Colors::TEXT_PRIMARY);
}

void MenuPause::Draw()
{
    DrawPauseHeader();
    DrawPlayerInfo();

    for (Button *button : buttons)
    {
        Rectangle btnRect = button->rect;

        DrawRectangleRec((Rectangle){btnRect.x + 4, btnRect.y + 4, btnRect.width, btnRect.height},
                         (Color){20, 15, 10, 180});
        DrawRectangleRec(btnRect, (Color){45, 38, 32, 255});
        DrawRectangleRec((Rectangle){btnRect.x + 3, btnRect.y + 3, btnRect.width - 6, btnRect.height - 6},
                         (Color){28, 22, 18, 255});
        DrawRectangleRec((Rectangle){btnRect.x + 6, btnRect.y + 6, btnRect.width - 12, btnRect.height - 12},
                         (Color){65, 55, 45, 255});

        DrawRectangle(btnRect.x + 6, btnRect.y + 6, btnRect.width - 12, 2, (Color){85, 75, 60, 120});
        DrawRectangle(btnRect.x + 6, btnRect.y + btnRect.height - 8, btnRect.width - 12, 2,
                      (Color){20, 15, 10, 160});

        // Corner rivets
        DrawCircle(btnRect.x + 10, btnRect.y + 10, 3, (Color){40, 35, 30, 255});
        DrawCircle(btnRect.x + btnRect.width - 10, btnRect.y + 10, 3, (Color){40, 35, 30, 255});
        DrawCircle(btnRect.x + 10, btnRect.y + btnRect.height - 10, 3, (Color){40, 35, 30, 255});
        DrawCircle(btnRect.x + btnRect.width - 10, btnRect.y + btnRect.height - 10, 3, (Color){40, 35, 30, 255});

        // Draw button label
        button->Draw((Color){65, 55, 45, 255}, (Color){85, 75, 60, 255});
    }
}

void MenuPause::HandleInput(Engine &engine)
{
    if (CheckCollisionPointRec(GetMousePosition(), resumeButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.PopState();
    }

    // Save Game Button
    if (CheckCollisionPointRec(GetMousePosition(), saveGameButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Audio::PlaySFx(BUTTON_HOVER);

        // If underlying state is a PlayState, capture current coin positions and player position before saving
        GameState *prev = engine.GetPreviousState();
        if (prev)
        {
            PlayState *ps = dynamic_cast<PlayState *>(prev);
            if (ps)
            {
                auto coins = ps->GetGameManager().GetCoinPositions();
                GameProgress::SetRemainingCoins(coins);

                Vector2 playerPos = ps->GetGameManager().GetPlayerPosition();
                GameProgress::SetMapPosition(playerPos);
            }
        }

        if (GameProgress::SaveProgress())
        {
            TraceLog(LOG_INFO, "Game saved successfully from pause menu!");
        }
        else
        {
            TraceLog(LOG_ERROR, "Failed to save game!");
        }
    }

    // Main Menu Button - Save and return to main menu
    if (CheckCollisionPointRec(GetMousePosition(), mainMenuButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        // Save progress before going to main menu
        GameProgress::SaveProgress();
        // Change to main menu state
        engine.ChangeState(new MainMenuState());
    }

    // Quit Button - Save and close the game
    if (CheckCollisionPointRec(GetMousePosition(), quitButton.rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        // Save progress before quitting
        GameProgress::SaveProgress();
        // Request the engine to exit so cleanup happens in the main loop.
        engine.RequestExit();
    }

    // ESC key to resume game
    if (IsKeyPressed(KEY_ESCAPE))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.PopState(); // Return to game
    }
}