#pragma once

#include <raylib.h>
#include "characters/Character.h"

class Animator
{
public:
    Animator();
    ~Animator();

    void Update(Character *, float);
    void Draw(Character *);
};