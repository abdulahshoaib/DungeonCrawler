#pragma once

#include "Menu.h"
#include <raylib.h>
#include "Label.h"

class MenuEnterName : public Menu
{
    Label playerName;

public:
    MenuEnterName();

    void Draw();
    void HandleInput(Engine &) override;
};
