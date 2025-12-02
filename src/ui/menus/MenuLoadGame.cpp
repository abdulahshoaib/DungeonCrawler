#include "MenuLoadGame.h"
#include "Loader.h"
#include "Engine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Audio.h"
#include "GameProgress.h"
#include <fstream>
#include <iostream>

MenuLoadGame::MenuLoadGame()
{
    InitializeSaveSlots();
}

void MenuLoadGame::InitializeSaveSlots()
{
    saveSlotButtons.clear();
    saveSlotButtons.resize(3);

    int screenWidth = GetScreenWidth();
    float startX = screenWidth / 2 - 150;
    float startY = 250;

    for (int i = 0; i < 3; i++)
    {
        saveSlotButtons[i].rect = {startX, startY + (i * 80), 300, 60};
        saveSlotButtons[i].label.fontSize = 20;
    }
}

bool MenuLoadGame::SaveSlotExists(int slot)
{
    std::string filename = "savegame_slot" + std::to_string(slot) + ".dat";
    std::ifstream file(filename);
    return file.good();
}

std::string MenuLoadGame::GetSaveSlotInfo(int slot)
{
    std::string filename = "savegame_slot" + std::to_string(slot) + ".dat";

    if (!SaveSlotExists(slot))
        return "EMPTY SLOT";

    std::ifstream file(filename);
    if (!file.is_open())
        return "ERROR";

    std::string playerName;
    std::getline(file, playerName);
    file.close();

    return playerName;
}

int MenuLoadGame::GetCharacterIDFromSlot(int slot)
{
    std::string filename = "savegame_slot" + std::to_string(slot) + ".dat";

    if (!SaveSlotExists(slot))
        return 1; // Default to Knight1

    std::ifstream file(filename);
    if (!file.is_open())
        return 1;

    std::string playerName;
    int characterID;
    std::getline(file, playerName);
    file >> characterID;
    file.close();

    return characterID;
}

void MenuLoadGame::Draw()
{
    // Draw background
    DrawTextureEx(Loader::LoadMenuBackground, {0, 0}, 0, 0.9f, WHITE);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float cx = screenWidth / 2;

    // Draw main content panel with stone border
    float panelX = 100;
    float panelY = 80;
    float panelW = screenWidth - 200;
    float panelH = screenHeight - 160;

    // Draw title with decorative background
    titleLabel.fontSize = 60;
    titleLabel.text = "Select Save";
    Vector2 titleSize = MeasureTextEx(Loader::TitleFont, titleLabel.text.c_str(), titleLabel.fontSize, 2);

    // Title background panel
    float titleBgX = cx - (titleSize.x / 2) - 30;
    float titleBgY = 120;
    float titleBgW = titleSize.x + 60;
    float titleBgH = titleSize.y + 20;

    DrawRectangleRec((Rectangle){titleBgX, titleBgY, titleBgW, titleBgH},
                     (Color){45, 38, 32, 200});
    DrawRectangleLinesEx((Rectangle){titleBgX, titleBgY, titleBgW, titleBgH},
                         2, (Color){150, 120, 80, 200});

    titleLabel.position = {cx - (titleSize.x / 2), titleBgY + 10};
    titleLabel.Draw((Color){255, 220, 100, 255});

    // Draw save slot buttons
    float slotStartY = 220;
    for (int i = 0; i < 3; i++)
    {
        std::string slotText = "SLOT " + std::to_string(i + 1);
        std::string slotInfo = GetSaveSlotInfo(i);
        bool hasData = SaveSlotExists(i);

        saveSlotButtons[i].rect = {cx - 200, slotStartY + (i * 85), 400, 70};

        if (hasData)
        {
            // Use standard button drawing for active slots
            saveSlotButtons[i].label.text = slotText;
            saveSlotButtons[i].Draw(GRAY, ORANGE);

            // Draw player name below the slot label
            DrawTextEx(Loader::TitleFont,
                       slotInfo.c_str(),
                       {saveSlotButtons[i].rect.x + 20, saveSlotButtons[i].rect.y + 40},
                       14, 2,
                       (Color){220, 200, 150, 255});
        }
        else
        {
            DrawRectangleRec((Rectangle){saveSlotButtons[i].rect.x + 4, saveSlotButtons[i].rect.y + 4,
                                         saveSlotButtons[i].rect.width, saveSlotButtons[i].rect.height},
                             (Color){20, 15, 10, 100});

            // Main stone border
            DrawRectangleRec(saveSlotButtons[i].rect, (Color){45, 38, 32, 200});

            // Inner groove
            DrawRectangleRec((Rectangle){saveSlotButtons[i].rect.x + 3, saveSlotButtons[i].rect.y + 3,
                                         saveSlotButtons[i].rect.width - 6, saveSlotButtons[i].rect.height - 6},
                             (Color){28, 22, 18, 200});

            // Interior
            DrawRectangleRec((Rectangle){saveSlotButtons[i].rect.x + 6, saveSlotButtons[i].rect.y + 6,
                                         saveSlotButtons[i].rect.width - 12, saveSlotButtons[i].rect.height - 12},
                             (Color){40, 35, 30, 150});

            // Draw disabled text
            Vector2 textSize = MeasureTextEx(Loader::TitleFont, slotText.c_str(), 20, 1);
            DrawTextEx(Loader::TitleFont, slotText.c_str(),
                       {saveSlotButtons[i].rect.x + (saveSlotButtons[i].rect.width - textSize.x) / 2,
                        saveSlotButtons[i].rect.y + 15},
                       20, 1, (Color){100, 90, 80, 120});

            DrawTextEx(Loader::TitleFont, "EMPTY", {saveSlotButtons[i].rect.x + 20, saveSlotButtons[i].rect.y + 40}, 14, 2, (Color){100, 90, 80, 100});
        }
    }

    // Draw back button
    backButton.rect = {cx - 75, (float)GetScreenHeight() - 100, 150, 50};
    backButton.label.text = "BACK";
    backButton.Draw(GRAY, RED);

    // Draw confirmation dialog if active
    if (showConfirmDialog && confirmSlot >= 0)
    {
        // Semi-transparent overlay
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 170});

        // Dialog panel
        int dialogWidth = 500;
        int dialogHeight = 320;
        float dialogX = (GetScreenWidth() - dialogWidth) / 2;
        float dialogY = (GetScreenHeight() - dialogHeight) / 2;

        // Outer shadow for depth
        DrawRectangleRec((Rectangle){dialogX + 10, dialogY + 10, (float)dialogWidth, (float)dialogHeight},
                         (Color){20, 15, 10, 220});

        // Main stone border
        DrawRectangleRec((Rectangle){dialogX, dialogY, (float)dialogWidth, (float)dialogHeight},
                         (Color){45, 38, 32, 255});

        // Inner darker groove
        DrawRectangleRec((Rectangle){dialogX + 5, dialogY + 5, (float)dialogWidth - 10, (float)dialogHeight - 10},
                         (Color){28, 22, 18, 255});

        // Main panel interior
        DrawRectangleRec((Rectangle){dialogX + 10, dialogY + 10, (float)dialogWidth - 20, (float)dialogHeight - 20},
                         (Color){65, 55, 45, 255});

        // Top highlight edge
        DrawRectangle((int)(dialogX + 10), (int)(dialogY + 10), dialogWidth - 20, 3,
                      (Color){100, 85, 70, 150});

        // Bottom shadow groove
        DrawRectangle((int)(dialogX + 10), (int)(dialogY + dialogHeight - 13), dialogWidth - 20, 3,
                      (Color){20, 15, 10, 200});

        // Decorative corner ornaments
        float cornerSize = 14.0f;
        Color cornerColor = (Color){200, 160, 80, 220};
        Color cornerHighlight = (Color){255, 220, 150, 200};

        // Top-left
        DrawRectangle((int)dialogX, (int)dialogY, (int)cornerSize, (int)cornerSize, cornerColor);
        DrawRectangle((int)(dialogX + 2), (int)(dialogY + 2), (int)(cornerSize - 4), (int)(cornerSize - 4), cornerHighlight);

        // Top-right
        DrawRectangle((int)(dialogX + dialogWidth - cornerSize), (int)dialogY, (int)cornerSize, (int)cornerSize, cornerColor);
        DrawRectangle((int)(dialogX + dialogWidth - cornerSize + 2), (int)(dialogY + 2), (int)(cornerSize - 4), (int)(cornerSize - 4), cornerHighlight);

        // Bottom-left
        DrawRectangle((int)dialogX, (int)(dialogY + dialogHeight - cornerSize), (int)cornerSize, (int)cornerSize, cornerColor);
        DrawRectangle((int)(dialogX + 2), (int)(dialogY + dialogHeight - cornerSize + 2), (int)(cornerSize - 4), (int)(cornerSize - 4), cornerHighlight);

        // Bottom-right
        DrawRectangle((int)(dialogX + dialogWidth - cornerSize), (int)(dialogY + dialogHeight - cornerSize), (int)cornerSize, (int)cornerSize, cornerColor);
        DrawRectangle((int)(dialogX + dialogWidth - cornerSize + 2), (int)(dialogY + dialogHeight - cornerSize + 2), (int)(cornerSize - 4), (int)(cornerSize - 4), cornerHighlight);

        // Title
        std::string playerName = GetSaveSlotInfo(confirmSlot);
        std::string confirmText = "Resume Game?";
        Vector2 titleSize = MeasureTextEx(Loader::TitleFont, confirmText.c_str(), 40, 2);
        DrawTextEx(Loader::TitleFont, confirmText.c_str(),
                   {dialogX + (dialogWidth - titleSize.x) / 2, dialogY + 30},
                   40, 2, (Color){255, 220, 100, 255});

        // Player name in a subtle box
        Vector2 nameSize = MeasureTextEx(Loader::TitleFont, playerName.c_str(), 26, 1);
        float nameBoxX = dialogX + (dialogWidth - nameSize.x) / 2 - 20;
        float nameBoxY = dialogY + 85;

        DrawRectangleRec((Rectangle){nameBoxX - 10, nameBoxY - 5, nameSize.x + 40, nameSize.y + 10},
                         (Color){45, 38, 32, 180});
        DrawRectangleLinesEx((Rectangle){nameBoxX - 10, nameBoxY - 5, nameSize.x + 40, nameSize.y + 10},
                             1, (Color){150, 120, 80, 200});

        DrawTextEx(Loader::TitleFont, playerName.c_str(),
                   {dialogX + (dialogWidth - nameSize.x) / 2, nameBoxY},
                   26, 1, (Color){220, 200, 150, 255});

        // Confirm and Cancel buttons
        confirmButton.rect = {dialogX + 40, dialogY + 170, 180, 70};
        confirmButton.label.text = "RESUME";
        confirmButton.Draw(GRAY, GREEN);

        cancelButton.rect = {dialogX + 280, dialogY + 170, 180, 70};
        cancelButton.label.text = "CANCEL";
        cancelButton.Draw(GRAY, RED);
    }
}

void MenuLoadGame::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    Vector2 mousePoint = GetMousePosition();

    if (showConfirmDialog)
    {
        // Handle confirmation dialog
        if (IsKeyPressed(KEY_ESCAPE) || (clicked && CheckCollisionPointRec(mousePoint, cancelButton.rect)))
        {
            showConfirmDialog = false;
            confirmSlot = -1;
            return;
        }

        if (clicked && CheckCollisionPointRec(mousePoint, confirmButton.rect))
        {
            // Load the game
            std::string filename = "savegame_slot" + std::to_string(confirmSlot) + ".dat";
            std::ifstream file(filename);

            if (GameProgress::LoadProgress(confirmSlot))
            {
                Audio::PlaySFx(BUTTON_HOVER);
                engine.ChangeState(new PlayState(GameProgress::GetCharacterID()));
            }
        }
        return;
    }

    // Main menu logic (when not showing confirmation)
    if (IsKeyPressed(KEY_ESCAPE) || (clicked && CheckCollisionPointRec(mousePoint, backButton.rect)))
    {
        engine.ChangeState(new MainMenuState());
        return;
    }

    // Check save slot selection
    for (int i = 0; i < 3; i++)
    {
        if (clicked && CheckCollisionPointRec(mousePoint, saveSlotButtons[i].rect))
        {
            if (SaveSlotExists(i))
            {
                selectedSlot = i;
                showConfirmDialog = true;
                confirmSlot = i;
                Audio::PlaySFx(BUTTON_HOVER);
            }
        }
    }
}