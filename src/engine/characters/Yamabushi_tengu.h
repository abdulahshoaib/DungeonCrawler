#pragma once

#include <raylib.h>
#include "Character.h"

class Yamabushi_tengu : public Character
{
public:
    Yamabushi_tengu();

    void anim() override;
};