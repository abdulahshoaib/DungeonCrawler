#include "Samurai.h"
#include "Loader.h"

Samurai::Samurai()
{
    attack1Anim = &Loader::SamuraiAttack1;
    attack2Anim = &Loader::SamuraiAttack2;
    attack3Anim = &Loader::SamuraiAttack3;
    deadAnim = &Loader::SamuraiDead;
    hurtAnim = &Loader::SamuraiHurt;
    idle1Anim = &Loader::SamuraiIdle;
    jumpAnim = &Loader::SamuraiJump;
    runAnim = &Loader::SamuraiRun;
    walkAnim = &Loader::SamuraiWalk;
    protectAnim = &Loader::SamuraiProtect;

    currentAnim = idle1Anim;
}

void Samurai::anim()
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
