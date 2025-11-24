#pragma once
#include "Menu.h"

class Engine;

class MenuSettings : public Menu
{
public:
    MenuSettings();
    void Draw();
    void HandleInput(Engine &) override;
};