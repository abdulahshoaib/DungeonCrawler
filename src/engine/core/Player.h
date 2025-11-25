
#pragma once

#include <raylib.h>
#include "Entitiy.h"

class Player : public Entity
{
public:
  Vector2 pos;
  Vector2 size;

  Player();
  Player(Vector2, Vector2);
  void move(float, float);
};