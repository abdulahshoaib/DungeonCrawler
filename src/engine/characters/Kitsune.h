#pragma once

#include <raylib.h>
#include "Character.h"

class Kitsune : public Character
{
public:
    Kitsune();
    void LoadTex() override;
    void UnloadTex() override;
    ~Kitsune();
};