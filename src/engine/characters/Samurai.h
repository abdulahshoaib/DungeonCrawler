#pragma once

#include <raylib.h>
#include "Character.h"

class Samurai : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};