#include "Knight3.h"
#include "Loader.h"

Knight3::Knight3()
{
    idle1Anim = &Loader::Knight3Idle;
    runAnim = &Loader::Knight3Run;
    walkAnim = &Loader::Knight3Walk;

    attack1Anim = &Loader::Knight3Attack1;
    attack2Anim = &Loader::Knight3Attack2;
    attack3Anim = &Loader::Knight3Attack3;

    hurtAnim = &Loader::Knight3Hurt;
    deadAnim = &Loader::Knight3Dead;
    defendAnim = &Loader::Knight3Defend;

    jumpAnim = &Loader::Knight3Jump;
    protectAnim = &Loader::Knight3Protect;
    runAttackAnim = &Loader::Knight3RunAttack;

    currentAnim = idle1Anim;
}

void Knight3::anim()
{
    switch (animState)
    {
    case AnimState::IDLE:
        currentAnim = idle1Anim;
        break;

    case AnimState::RUN:
        currentAnim = runAnim;
        break;

    case AnimState::WALK:
        currentAnim = walkAnim;
        break;

    case AnimState::JUMP:
        currentAnim = jumpAnim;
        break;

    case AnimState::ATTACK1:
        currentAnim = attack1Anim;
        break;

    case AnimState::ATTACK2:
        currentAnim = attack2Anim;
        break;

    case AnimState::ATTACK3:
        currentAnim = attack3Anim;
        break;

    case AnimState::HURT:
        currentAnim = hurtAnim;
        break;

    case AnimState::DEAD:
        currentAnim = deadAnim;
        break;

    case AnimState::PROTECT:
        currentAnim = protectAnim;
        break;

    case AnimState::RUN_ATTACK:
        currentAnim = runAttackAnim;
        break;

    default:
        currentAnim = idle1Anim;
        break;
    }
}
