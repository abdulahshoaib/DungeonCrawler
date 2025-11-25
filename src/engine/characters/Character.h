#pragma once

#include <raylib.h>

class Character
{
public:
    Texture2D attack[3];
    Texture2D dead;
    Texture2D defend;
    Texture2D hurt;
    Texture2D idle[2];
    Texture2D jump;
    Texture2D protect;
    Texture2D run;
    Texture2D run_attack;
    Texture2D walk;
    Texture2D arrow;
    Texture2D shot[2];
    Texture2D charge;
    Texture2D evasion;
    Texture2D fall;
    Texture2D fire[2];

    virtual void LoadTex() = 0;
};