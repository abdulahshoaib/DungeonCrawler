#include "Samurai_archer.h"
#include "Loader.h"

Samurai_archer::Samurai_archer()
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
}

void Samurai_archer::anim()
{
}
