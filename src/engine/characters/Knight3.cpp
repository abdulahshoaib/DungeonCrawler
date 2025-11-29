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
}