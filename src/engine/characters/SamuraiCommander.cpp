#include "SamuraiCommander.h"
#include "Loader.h"

SamuraiCommander::SamuraiCommander()
{
    attack1Anim = &Loader::SamuraiCommanderAttack1;
    attack2Anim = &Loader::SamuraiCommanderAttack2;
    attack3Anim = &Loader::SamuraiCommanderAttack3;
    deadAnim = &Loader::SamuraiCommanderDead;
    hurtAnim = &Loader::SamuraiCommanderHurt;
    idle1Anim = &Loader::SamuraiCommanderIdle;
    jumpAnim = &Loader::SamuraiCommanderJump;
    runAnim = &Loader::SamuraiCommanderRun;
    walkAnim = &Loader::SamuraiCommanderWalk;
    protectAnim = &Loader::SamuraiCommanderProtect;

    currentAnim = idle1Anim;
}

void SamuraiCommander::anim()
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

    default:
        currentAnim = idle1Anim;
        break;
    }
}