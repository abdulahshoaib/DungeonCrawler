#pragma once
#include "Menu.h"
#include "Engine.h"

class MenuSettings : public Menu
{
public:
    MenuSettings();
    void Draw();
    void HandleInput(Engine &) override;
};