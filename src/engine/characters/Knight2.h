#pragma once

#include <raylib.h>
#include "Character.h"

class Knight2 : public Character
{
public:
    Knight2();
    void anim() override;
};