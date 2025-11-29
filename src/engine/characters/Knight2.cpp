#include "Knight2.h"
#include "Loader.h"

Knight2::Knight2()
{
    idle1Anim = &Loader::Knight2Idle;
    runAnim = &Loader::Knight2Run;
    walkAnim = &Loader::Knight2Walk;

    attack1Anim = &Loader::Knight2Attack1;
    attack2Anim = &Loader::Knight2Attack2;
    attack3Anim = &Loader::Knight2Attack3;

    hurtAnim = &Loader::Knight2Hurt;
    deadAnim = &Loader::Knight2Dead;
    defendAnim = &Loader::Knight2Defend;

    jumpAnim = &Loader::Knight2Jump;
    protectAnim = &Loader::Knight2Protect;
    runAttackAnim = &Loader::Knight2RunAttack;

    currentAnim = idle1Anim;
}

void Knight2::anim()
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
