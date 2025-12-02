#pragma once
#include "GameState.h"
#include "core/GameManager.h"

class PlayState : public GameState
{
private:
    GameManager gameManager;

public:
    PlayState(int);
    void Update(Engine &);
    void Draw(Engine &);
    GameManager &GetGameManager() { return gameManager; }
};