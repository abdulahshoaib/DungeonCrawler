#pragma once

#include "Menu.h"
#include <raylib.h>

class MenuNewGame : public Menu
{
    Rectangle rectKnight1, rectKnight2, rectKnight3;
    Rectangle rectSamurai1, rectSamurai2, rectSamurai3;
public:
    MenuNewGame();

    void Draw();
    void HandleInput(Engine &) override;
};
