#include "Karasu_tengu.h"
#include "Loader.h"

Karasu_tengu::Karasu_tengu()
{
    attack1Anim = &Loader::KarasuTenguAttack1;
    attack2Anim = &Loader::KarasuTenguAttack2;
    attack3Anim = &Loader::KarasuTenguAttack3;
    deadAnim = &Loader::KarasuTenguDead;
    hurtAnim = &Loader::KarasuTenguHurt;
    runAnim = &Loader::KarasuTenguRun;
    walkAnim = &Loader::KarasuTenguWalk;
    idle1Anim = &Loader::KarasuTenguIdle1;
    idle2Anim = &Loader::KarasuTenguIdle2;

    currentAnim = idle1Anim;
}

void Karasu_tengu::anim()
{
}
