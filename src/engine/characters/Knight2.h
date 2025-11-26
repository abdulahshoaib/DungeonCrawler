#pragma once

#include <raylib.h>
#include "Character.h"

class Knight2 : public Character
{
public:
    Knight2();
    void LoadTex() override;
    void UnloadTex() override;
    ~Knight2();
};