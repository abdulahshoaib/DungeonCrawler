#pragma once

#include <raylib.h>
#include "Character.h"

class Black_werewolf : public Character
{
public:
    Black_werewolf();
    void LoadTex() override;
    void UnloadTex() override;
    ~Black_werewolf();
};