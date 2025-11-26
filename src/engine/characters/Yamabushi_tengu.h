#pragma once

#include <raylib.h>
#include "Character.h"

class Yamabushi_tengu : public Character
{
public:
    Yamabushi_tengu();
    void LoadTex() override;
    void UnloadTex() override;
    ~Yamabushi_tengu();
};