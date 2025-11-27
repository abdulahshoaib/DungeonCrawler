#pragma once

#include "GameState.h"
#include "MenuLoadGame.h"

class LoadGameState : public GameState
{
    MenuLoadGame loadGameMenu;
public:
    ~LoadGameState();
    void Update(Engine &);
    void Draw(Engine &);
};