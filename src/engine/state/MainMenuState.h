#pragma once

#include "GameState.h"
#include "MenuMain.h"

class MainMenuState : public GameState
{
private:
    MenuMain mainMenu;

public:
    void Update(Engine &);
    void Draw(Engine &);
};