#pragma once

#include <raylib.h>
#include "Character.h"

class White_werewolf : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};