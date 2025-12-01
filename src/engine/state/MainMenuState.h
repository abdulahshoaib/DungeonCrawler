#pragma once

#include "GameState.h"
#include "MenuMain.h"

class MainMenuState : public GameState
{
private:
    MenuMain mainMenu;

public:
    void Enter(Engine &);
    void Update(Engine &);
    void Draw(Engine &);
};