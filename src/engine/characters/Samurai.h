#pragma once

#include <raylib.h>
#include "Character.h"

class Samurai : public Character
{
public:
    Samurai();
    void LoadTex() override;
    void UnloadTex() override;
    ~Samurai();
};