#pragma once

#include <raylib.h>
#include "Character.h"

class Knight1 : public Character
{
public:
    Knight1();
    void LoadTex() override;
    void UnloadTex() override;
    ~Knight1();
};