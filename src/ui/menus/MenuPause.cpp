// MenuPause.cpp
#include "MenuPause.h"
#include "GameProgress.h"
#include "Loader.h"
#include "Audio.h"
#include "MainMenuState.h" // You'll need to include your main menu state
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

    // Shadow
    DrawTextEx(Loader::TitleFont, title, {x + 3, y + 3}, fontSize, 2.0f, (Color){20, 15, 10, 200});
    // Main text
    DrawTextEx(Loader::TitleFont, title, {x, y}, fontSize, 2.0f, (Color){255, 200, 100, 255});
}

void MenuPause::DrawPlayerInfo()
{
    float fontSize = 24.0f;
    float infoY = 160;
    float lineSpacing = 35;

    // Player info box background
    Rectangle infoBox = {(float)(GetScreenWidth() / 2) - 200, infoY - 10, 400, 120};

    // Outer shadow
    DrawRectangleRec((Rectangle){infoBox.x + 3, infoBox.y + 3, infoBox.width, infoBox.height},
                     (Color){20, 15, 10, 180});
    // Main border
    DrawRectangleRec(infoBox, (Color){45, 38, 32, 255});
    // Inner area
    DrawRectangleRec((Rectangle){infoBox.x + 4, infoBox.y + 4, infoBox.width - 8, infoBox.height - 8},
                     (Color){65, 55, 45, 255});

    // Player information
    std::string usernameText = "Player: " + GameProgress::GetUsername();
    std::string pointsText = "Points: " + std::to_string(GameProgress::GetPoints());
    std::string levelText = "Level: " + std::to_string(GameProgress::GetCurrentLevel());
    std::string coinsText = "Coins: " + std::to_string(GameProgress::GetCoinsCollected());

    Vector2 pos = GameProgress::GetMapPosition();
    std::string positionText = "Position: (" +
                               std::to_string((int)pos.x) + ", " +
                               std::to_string((int)pos.y) + ")";

    float textX = GetScreenWidth() / 2;
    Color infoColor = (Color){235, 220, 195, 255};

    Vector2 usernameSize = MeasureTextEx(Loader::TitleFont, usernameText.c_str(), fontSize, 1.0f);
    DrawTextEx(Loader::TitleFont, usernameText.c_str(),
               {textX - usernameSize.x / 2, infoY}, fontSize, 1.0f, infoColor);

    Vector2 pointsSize = MeasureTextEx(Loader::TitleFont, pointsText.c_str(), fontSize, 1.0f);
    DrawTextEx(Loader::TitleFont, pointsText.c_str(),
               {textX - pointsSize.x / 2, infoY + lineSpacing}, fontSize, 1.0f, infoColor);

    Vector2 levelSize = MeasureTextEx(Loader::TitleFont, levelText.c_str(), fontSize, 1.0f);
    DrawTextEx(Loader::TitleFont, levelText.c_str(),
               {textX - levelSize.x / 2, infoY + lineSpacing * 2}, fontSize, 1.0f, infoColor);

    Vector2 coinsSize = MeasureTextEx(Loader::TitleFont, coinsText.c_str(), fontSize, 1.0f);
    DrawTextEx(Loader::TitleFont, coinsText.c_str(),
               {textX - coinsSize.x / 2, infoY + lineSpacing * 3}, fontSize, 1.0f, infoColor);
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
        // Close the window (Engine::run() will handle cleanup)
        CloseWindow();
    }

    // ESC key to resume game
    if (IsKeyPressed(KEY_ESCAPE))
    {
        Audio::PlaySFx(BUTTON_HOVER);
        engine.PopState(); // Return to game
    }
}