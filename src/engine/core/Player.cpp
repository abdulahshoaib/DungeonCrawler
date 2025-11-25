
#include "Player.h"

Player::Player(Vector2 position, Vector2 size) : pos(position), size(size) {}
Player::Player() : pos({0, 0}), size({10, 10}) {}

void Player::move(float _x, float _y)
{
  pos.x += _x;
  pos.y += _y;
}