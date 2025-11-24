#pragma once
#include "GameState.h"

class PlayState : public GameState
{
private:
public:
    void Update(Engine &);
    void Draw(Engine &);
};