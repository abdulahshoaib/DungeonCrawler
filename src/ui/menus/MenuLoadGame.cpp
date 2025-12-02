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

void MenuLoadGame::Draw()
{
    float scale = 0.9f;
    DrawTextureEx(Loader::LoadMenuBackground, {0, 0}, 0, scale, WHITE);

    int screenWidth = GetScreenWidth();
    float cx = screenWidth / 2;

    // Draw title
    titleLabel.fontSize = 60;
    titleLabel.text = "SELECT SAVE";
    Vector2 titleSize = MeasureTextEx(Loader::TitleFont, titleLabel.text.c_str(), titleLabel.fontSize, 2);
    titleLabel.position = {cx - (titleSize.x / 2), 100};
    titleLabel.Draw(WHITE);

    // Draw save slot buttons
    for (int i = 0; i < 3; i++)
    {
        std::string slotText = "SLOT " + std::to_string(i + 1);
        std::string slotInfo = GetSaveSlotInfo(i);

        saveSlotButtons[i].label.text = slotText;

        Color normalColor = SaveSlotExists(i) ? (Color){75, 65, 55, 255} : (Color){40, 35, 30, 255};
        Color hoverColor = (Color){100, 90, 75, 255};

        saveSlotButtons[i].Draw(normalColor, hoverColor);

        // Draw slot info below button
        Color infoColor = SaveSlotExists(i) ? WHITE : (Color){128, 128, 128, 255};
        DrawText(
            slotInfo.c_str(),
            (int)saveSlotButtons[i].rect.x + 10,
            (int)saveSlotButtons[i].rect.y + (int)saveSlotButtons[i].rect.height + 5,
            16,
            infoColor);
    }

    // Draw back button
    backButton.rect = {cx - 75, (float)GetScreenHeight() - 100, 150, 50};
    backButton.label.text = "BACK";
    backButton.Draw(GRAY, RED);

    // Draw load button (only if slot selected)
    if (selectedSlot >= 0 && SaveSlotExists(selectedSlot))
    {
        loadButton.rect = {cx - 75, (float)GetScreenHeight() - 160, 150, 50};
        loadButton.label.text = "LOAD";
        loadButton.Draw(GRAY, GREEN);
    }
}

void MenuLoadGame::HandleInput(Engine &engine)
{
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    Vector2 mousePoint = GetMousePosition();

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
                Audio::PlaySFx(BUTTON_HOVER);
            }
        }
    }

    // Load selected save
    if (selectedSlot >= 0 && clicked && CheckCollisionPointRec(mousePoint, loadButton.rect))
    {
        std::string filename = "savegame_slot" + std::to_string(selectedSlot) + ".dat";
        std::ifstream file(filename);

        if (file.is_open())
        {
            std::string playerName;
            int characterID;
            int points;
            float mapX, mapY;
            int level;

            std::getline(file, playerName);
            file >> characterID >> points >> mapX >> mapY >> level;
            file.close();

            // Set game progress from loaded save
            GameProgress::SetUsername(playerName);
            GameProgress::SetCharacterID(characterID);
            GameProgress::SetPoints(points);
            GameProgress::SetMapPosition(mapX, mapY);
            GameProgress::SetCurrentLevel(level);
            GameProgress::SetCurrentSlot(selectedSlot);

            Audio::PlaySFx(BUTTON_HOVER);
            engine.ChangeState(new PlayState(characterID));
        }
    }
}