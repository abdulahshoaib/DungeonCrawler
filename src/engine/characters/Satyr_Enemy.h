#pragma once

#include <raylib.h>
#include "Character.h"

class Satyr_enemy : public Character
{
public:
    Satyr_enemy();
    void LoadTex() override;
    void UnloadTex() override;
    ~Satyr_enemy();
};