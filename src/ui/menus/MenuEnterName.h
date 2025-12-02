#pragma once

#include "Menu.h"
#include <raylib.h>
#include "Label.h"
#include "ui_elements/Button.h"

class MenuEnterName : public Menu
{
    Label playerName;
    Button backButton;

public:
    MenuEnterName();

    void Draw();
    void HandleInput(Engine &) override;
};
