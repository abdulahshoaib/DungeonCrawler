#pragma once

#include "GameState.h"
#include "MenuLoadGame.h"

class LoadGameState : public GameState
{
    MenuLoadGame loadGameMenu;
public:

    void Update(Engine &);
    void Draw(Engine &);
};