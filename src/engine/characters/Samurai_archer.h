#pragma once

#include <raylib.h>
#include "Character.h"

class Samurai_archer : public Character
{
public:
    Samurai_archer();
    void LoadTex() override;
    void UnloadTex() override;
    ~Samurai_archer();
};