#pragma once

#include <raylib.h>

class Character
{
public:
    Texture2D attack[3];
    Texture2D dead;
    Texture2D defend;
    Texture2D hurt;

    virtual void LoadTex() = 0;
};