#pragma once

#include <raylib.h>
#include "Character.h"

class SamuraiArcher : public Character
{
public:
    SamuraiArcher();

    void anim() override;
};