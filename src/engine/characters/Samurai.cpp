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
}
