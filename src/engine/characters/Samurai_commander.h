#pragma once

#include <raylib.h>
#include "Character.h"

class Samurai_Commander: public Character
{
public:
    Samurai_Commander();
    void LoadTex() override;
    void UnloadTex() override;
    ~Samurai_Commander();
};