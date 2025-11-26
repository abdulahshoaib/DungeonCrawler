#pragma once

#include <raylib.h>
#include "Character.h"

class Karasu_tengu : public Character
{
public:
    Karasu_tengu();
    void LoadTex() override;
    void UnloadTex() override;
    ~Karasu_tengu();
};