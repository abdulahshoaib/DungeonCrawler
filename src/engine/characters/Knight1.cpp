#include "Knight1.h"
#include "AnimStates.h"
#include "Loader.h"

Knight1::Knight1()
{
    idle1Anim = &Loader::Knight1Idle;
    runAnim = &Loader::Knight1Run;
    walkAnim = &Loader::Knight1Walk;

    attack1Anim = &Loader::Knight1Attack1;
    attack2Anim = &Loader::Knight1Attack2;
    attack3Anim = &Loader::Knight1Attack3;

    hurtAnim = &Loader::Knight1Hurt;
    deadAnim = &Loader::Knight1Dead;
    defendAnim = &Loader::Knight1Defend;

    jumpAnim = &Loader::Knight1Jump;
    protectAnim = &Loader::Knight1Protect;
    runAttackAnim = &Loader::Knight1RunAttack;

    currentAnim = idle1Anim;

    // Combat stats
    damage = 10.0f;
}

void Knight1::anim()
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

    case AnimState::RUN_ATTACK:
        currentAnim = runAttackAnim;
        break;

    default:
        currentAnim = idle1Anim;
        break;
    }
}