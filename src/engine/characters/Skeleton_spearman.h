#pragma once

#include <raylib.h>
#include "Character.h"

class Skeleton_spearman: public Character
{
public:
    void LoadTex() override;
    void UnloadTex() override;
};