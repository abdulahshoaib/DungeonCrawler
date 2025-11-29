#include "Yamabushi_tengu.h"
#include "Loader.h"

Yamabushi_tengu::Yamabushi_tengu()
{
    attack1Anim = &Loader::YamabushiTenguAttack1;
    attack2Anim = &Loader::YamabushiTenguAttack2;
    attack3Anim = &Loader::YamabushiTenguAttack3;
    deadAnim = &Loader::YamabushiTenguDead;
    hurtAnim = &Loader::YamabushiTenguHurt;
    idle1Anim = &Loader::YamabushiTenguIdle1;
    idle2Anim = &Loader::YamabushiTenguIdle2;
    runAnim = &Loader::YamabushiTenguRun;
    walkAnim = &Loader::YamabushiTenguWalk;

    currentAnim = idle1Anim;
}

void Yamabushi_tengu::anim()
{
}