#include "Coin.h"

CoinObject::CoinObject(float x, float y)
{
    pos = { x, y };
    hitbox = { x, y, 
        (float)Loader::CoinAnim.frameWidth, 
        (float)Loader::CoinAnim.frameHeight 
    };
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
        (float)Loader::CoinAnim.frameHeight
    };

    // Draw coin at its position
    DrawTextureRec(
        Loader::CoinAnim.spriteSheet,
        src,
        pos,
        WHITE
    );
}
