#pragma once

#include "GameState.h"
#include "../ui/ui_elements/Button.h"

class DeathState : public GameState
{
private:
    Button quitBtn;
    Button menuBtn;
    Button replayBtn;

public:
    void Enter(Engine &);
    void Update(Engine &);
    void Draw(Engine &);
};
