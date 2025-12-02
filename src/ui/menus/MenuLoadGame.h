#pragma once

#include "Menu.h"
#include "Button.h"
#include "Label.h"
#include <raylib.h>
#include <vector>
#include <string>

class MenuLoadGame : public Menu
{
private:
    std::vector<Button> saveSlotButtons;
    int selectedSlot = -1;
    Label titleLabel;
    Button backButton;
    Button loadButton;
    Button confirmButton;
    Button cancelButton;

    bool showConfirmDialog = false;
    int confirmSlot = -1;

    void InitializeSaveSlots();
    std::string GetSaveSlotInfo(int slot);
    bool SaveSlotExists(int slot);
    int GetCharacterIDFromSlot(int slot);

public:
    MenuLoadGame();
    void Draw();
    void HandleInput(Engine &) override;
};