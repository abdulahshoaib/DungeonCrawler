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
}
