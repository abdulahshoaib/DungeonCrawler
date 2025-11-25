#pragma once

#include "Engine.h"

class LoadingState : public GameState
{
public:
    int step = 0;

    void Update(Engine&) override;
    void Draw(Engine&) override;
};