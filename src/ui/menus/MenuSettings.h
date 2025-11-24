#pragma once
#include "Menu.h"

class MenuSettings : public Menu
{
public:
    MenuSettings();
    void Draw();
    void HandleInput(Engine &);
};