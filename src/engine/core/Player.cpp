
#include "Player.h"

// NOTE(demon_slayer): this constructor is called from the GameManager
//                     and sets the variable attribs based on the character chosen  
Player::Player(Character)
{
}

void Player::move(float _x, float _y)
{
  pos.x += _x;
  pos.y += _y;
}