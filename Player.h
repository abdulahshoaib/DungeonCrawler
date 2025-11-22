
#pragma once
#include <raylib.h>

class Player {
  Vector2 pos;
  Vector2 size;

public:
  Player();
  Player(Vector2, Vector2);
  void move(float, float);

  Vector2 getSize() const;
  Vector2 getPos() const;
};