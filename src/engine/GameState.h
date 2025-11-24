#pragma once

class Engine;

class GameState
{
public:
    GameState() {}
    virtual ~GameState() {}
    virtual void Update(Engine &) = 0;
    virtual void Draw(Engine &) = 0;
};
