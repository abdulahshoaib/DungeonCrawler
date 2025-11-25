#pragma once

#include <raylib.h>
#include "Character.h"

class Kitsune : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};