
#pragma once

#include <raylib.h>
#include "Entity.h"
#include "characters/Character.h"

class Player : public Entity
{
public:
  Player();
  void move(float, float);
};