#include "SamuraiArcher.h"
#include "Loader.h"

SamuraiArcher::SamuraiArcher()
{
    attack1Anim = &Loader::SamuraiArcherAttack1;
    attack2Anim = &Loader::SamuraiArcherAttack2;
    attack3Anim = &Loader::SamuraiArcherAttack3;
    deadAnim = &Loader::SamuraiArcherDead;
    idle1Anim = &Loader::SamuraiArcherIdle;
    jumpAnim = &Loader::SamuraiArcherJump;
    runAnim = &Loader::SamuraiArcherRun;
    walkAnim = &Loader::SamuraiArcherWalk;
    shot1Anim = &Loader::SamuraiArcherShot;

    currentAnim = idle1Anim;

    // Combat stats
    damage = 8.0f;
}

void SamuraiArcher::anim()
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

    case AnimState::SHOT1: // for bow shooting
        currentAnim = shot1Anim;
        break;

    case AnimState::DEAD:
        currentAnim = deadAnim;
        break;

    default:
        currentAnim = idle1Anim;
        break;
    }
}
