#pragma once

#include <raylib.h>
#include "Character.h"

class Knight3 : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};