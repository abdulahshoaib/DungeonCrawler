#pragma once

#include "Label.h"
#include "Button.h"
#include "Engine.h"
#include <raylib.h>
#include <vector>
#include <string>

class MenuNewGame
{
private:
    Rectangle rectKnight1, rectKnight2, rectKnight3;
    Rectangle rectSamurai1, rectSamurai2, rectSamurai3;

    // Hover tracking variables
    bool hoveredKnight1;
    bool hoveredKnight2;
    bool hoveredKnight3;
    bool hoveredSamurai1;
    bool hoveredSamurai2;
    bool hoveredSamurai3;

    // Selected character ID (1-6, or 0 for none)
    int selectedCharacter = 0;

    // Save slot selection
    std::vector<Button> slotButtons;
    int selectedSlot = -1;
    bool showSlotSelection = false;

public:
    MenuNewGame();
    virtual ~MenuNewGame();
    void Draw();
    void HandleInput(Engine &engine);
    void InitializeSlotButtons();
};
