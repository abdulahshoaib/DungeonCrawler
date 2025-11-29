#include "Character.h"

Character::Character()
{
    hp = 100;
}

void Character::ChangeAnimState(AnimState newAnimState)
{
    animState = newAnimState;
}
