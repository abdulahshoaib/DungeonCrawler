#include "Coin.h"

CoinObject::CoinObject(float x, float y)
{
    pos = {x, y};
    hitbox = {x, y,
              (float)Loader::CoinAnim.frameWidth,
              (float)Loader::CoinAnim.frameHeight};
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

    // Update hitbox
    hitbox.x = pos.x;
    hitbox.y = pos.y;
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
    float scale = 32.0f / Loader::CoinAnim.frameWidth;

    // Center the scaled coin on the tile position
    float scaledWidth = Loader::CoinAnim.frameWidth * scale;
    float scaledHeight = Loader::CoinAnim.frameHeight * scale;
    Vector2 centerOffset = {
        (32.0f - scaledWidth) / 2.0f,
        (32.0f - scaledHeight) / 2.0f};

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