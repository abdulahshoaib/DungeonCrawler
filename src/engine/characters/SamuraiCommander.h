#pragma once

#include <raylib.h>
#include "Character.h"

class SamuraiCommander : public Character
{
public:
    SamuraiCommander();
    void anim() override;
};