#include "Coin.h"

CoinObject::CoinObject(float x, float y)
{
    pos = {x, y};
    float scale = 32.0f / Loader::CoinAnim.frameWidth;
    scaledWidth = Loader::CoinAnim.frameWidth * scale;
    scaledHeight = Loader::CoinAnim.frameHeight * scale;
    drawOffset = {
        (32.0f - scaledWidth) / 2.0f,
        (32.0f - scaledHeight) / 2.0f};
    hitbox = {x + drawOffset.x,
              y + drawOffset.y,
              scaledWidth,
              scaledHeight};
}

void CoinObject::Update(float dt)
{
    // Update animation timer
    frameTimer += dt;

    // Change frame based on frameSpeed (frames per second)
    if (frameTimer >= 1.0f / Loader::CoinAnim.fps)
    {
        frameTimer = 0;
        currentFrame++;

        if (currentFrame >= Loader::CoinAnim.frameCount)
            currentFrame = 0;
    }

    // Update hitbox to follow the scaled destination area
    hitbox.x = pos.x + drawOffset.x;
    hitbox.y = pos.y + drawOffset.y;
}

void CoinObject::Draw()
{
    // Source rect selects the correct animation frame
    Rectangle src = {
        (float)(currentFrame * Loader::CoinAnim.frameWidth),
        0,
        (float)Loader::CoinAnim.frameWidth,
        (float)Loader::CoinAnim.frameHeight};

    // Scale coin down from 120x120 to 32x32 (scale factor ~0.27)
    // Reuse precomputed draw measurements
    float scaledWidth = this->scaledWidth;
    float scaledHeight = this->scaledHeight;
    Vector2 centerOffset = drawOffset;

    // Destination rect for scaled drawing
    Rectangle dest = {
        pos.x + centerOffset.x,
        pos.y + centerOffset.y,
        scaledWidth,
        scaledHeight};

    // Draw scaled coin texture with animation frame
    DrawTexturePro(
        Loader::CoinAnim.spriteSheet,
        src,
        dest,
        {0, 0},
        0.0f,
        WHITE);
}