#pragma once

#include "Label.h"
#include "Engine.h"
#include <raylib.h>

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

public:
    MenuNewGame();
    virtual ~MenuNewGame();
    void Draw();
    void HandleInput(Engine &engine);
};
