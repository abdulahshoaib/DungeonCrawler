#pragma once
#include "GameState.h"
#include "core/GameManager.h"

class PlayState : public GameState
{
private:
    GameManager gameManager;

public:
    // PlayState();
    void Update(Engine &);
    void Draw(Engine &);
};