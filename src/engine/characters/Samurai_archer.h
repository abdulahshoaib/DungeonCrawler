#pragma once

#include <raylib.h>
#include "Character.h"

class Samurai_archer : public Character
{
public:
    Samurai_archer();

    void anim() override;
};