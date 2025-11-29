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
}