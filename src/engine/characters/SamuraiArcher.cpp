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
}

void SamuraiArcher::anim()
{
}
