#pragma once

#include "GameState.h"
#include "MenuNewGame.h"

class NewGameState : public GameState
{
private:
    MenuNewGame newGameMenu;

public:
    ~NewGameState();
    void Update(Engine &);
    void Draw(Engine &);
};