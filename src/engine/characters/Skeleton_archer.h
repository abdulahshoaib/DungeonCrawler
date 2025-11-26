#pragma once

#include <raylib.h>
#include "Character.h"

class Skeleton_archer : public Character
{
public:
    Skeleton_archer();
    void LoadTex() override;
    void UnloadTex() override;

    ~Skeleton_archer();
};