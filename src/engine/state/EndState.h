#pragma once

#include "GameState.h"
#include "../ui/ui_elements/Button.h"
#include <raylib.h>

class EndState : public GameState
{
public:
    EndState(int kills = 0, int coins = 0);
    virtual void Enter(Engine &engine);
    virtual void Update(Engine &engine) override;
    virtual void Draw(Engine &engine) override;

private:
    int enemiesKilled = 0;
    int coinsCollected = 0;

    Button retryBtn;
    Button menuBtn;
    Button quitBtn;

    // Stats text buffers
    char statsKills[128];
    char statsCoins[128];
};
