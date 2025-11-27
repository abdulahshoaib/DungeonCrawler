#pragma once

#include "Menu.h"
#include <raylib.h>

class MenuLoadGame : public Menu
{
public:
    MenuLoadGame();
    void Draw();
    void HandleInput(Engine &) override;
};