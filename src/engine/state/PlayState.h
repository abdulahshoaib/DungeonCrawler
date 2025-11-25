#pragma once
#include "GameState.h"
#include "GameManager.h"

class PlayState : public GameState
{
private:
    GameManager gameManager;

public:
    PlayState();
    void Update(Engine &);
    void Draw(Engine &);
};