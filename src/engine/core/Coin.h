#pragma once
#include "raylib.h"
#include "Loader.h"

class CoinObject
{
public:
    Vector2 pos;
    Rectangle hitbox;

    int currentFrame = 0;
    float frameTimer = 0.0f;
    float scaledWidth = 0.0f;
    float scaledHeight = 0.0f;
    Vector2 drawOffset = {0.0f, 0.0f};

    CoinObject(float x, float y);

    void Update(float dt);
    void Draw();
};
