#pragma once

#include <raylib.h>

struct Animation
{
    Texture2D spriteSheet;

    int frameWidth;
    int frawHeight;
    int frameCount;
    int fps;
};