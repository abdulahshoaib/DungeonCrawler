#pragma once

#include "GameState.h"
#include "MenuNewGame.h"

class NewGameState : public GameState
{
private:
    MenuNewGame newGameMenu;

public:
    void Update(Engine &);
    void Draw(Engine &);
};