#pragma once

#include <raylib.h>
#include "Character.h"

class Skeleton_spearman: public Character
{
public:
    Skeleton_spearman();
    void LoadTex() override;
    void UnloadTex() override;
    ~Skeleton_spearman();
};