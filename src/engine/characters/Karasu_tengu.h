#pragma once

#include <raylib.h>
#include "Character.h"

class Karasu_tengu : public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};