#include "Character.h"

bool Character::IsAnimationLocked() const
{
    return isAnimationLocked;
}

void Character::OnAnimationComplete()
{
    isAnimationLocked = false;
    ChangeAnimState(AnimState::IDLE);
}

Character::Character()
{
    Pos.x = 100;
    Pos.y = 500;
    hp = 100;
}

void Character::ChangeAnimState(AnimState newState)
{
    // Don't allow changes if locked
    if (isAnimationLocked && animState != newState)
        return;
    
    animState = newState;
    
    // Lock animations that shouldn't be interrupted
    if (newState == AnimState::ATTACK1 ||
        newState == AnimState::ATTACK2 ||
        newState == AnimState::ATTACK3 ||
        newState == AnimState::JUMP ||
        newState == AnimState::HURT ||
        newState == AnimState::DEAD)
    {
        isAnimationLocked = true;
    }
}
