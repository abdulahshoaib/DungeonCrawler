#pragma once

#include <raylib.h>

struct Animation
{
    Texture2D spriteSheet;

    int frameWidth;
    int frameHeight;
    int frameCount;
    int fps;

    int currentFrame = 0;
    float frameTimer = 0.0f;
};