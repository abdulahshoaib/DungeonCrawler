#pragma once

#include <raylib.h>
#include "Character.h"

class Knight3 : public Character
{
public:
    Knight3();

    void anim() override;
};