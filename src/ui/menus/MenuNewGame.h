#pragma once

#include "Menu.h"

class MenuNewGame : public Menu
{
public:
    MenuNewGame();

    void Draw();
    void HandleInput(Engine &) override;
};