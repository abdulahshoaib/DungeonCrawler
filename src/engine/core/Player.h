
#pragma once

#include <raylib.h>
#include "Entity.h"
#include "Character.h"

class Player : public Entity
{
public:
  Player(Character);
  void move(float, float);
};