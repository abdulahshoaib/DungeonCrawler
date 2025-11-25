#pragma once

#include <raylib.h>
#include "Character.h"

class Knight2 : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};