#include "EnemyYokai.h"
#include "system/Loader.h"

EnemyYokai::EnemyYokai() : Enemy()
{
    // Base Yokai setup
    hp = 40.0f;
    damage = 11.0f;
    speed = 200.0f;
}

EnemyKarasuTengu::EnemyKarasuTengu() : EnemyYokai()
{
    // Setup Karasu Tengu animations
    idle1Anim = &Loader::KarasuTenguIdle1;
    idle2Anim = &Loader::KarasuTenguIdle2;
    runAnim = &Loader::KarasuTenguRun;
    walkAnim = &Loader::KarasuTenguWalk;
    attack1Anim = &Loader::KarasuTenguAttack1;
    attack2Anim = &Loader::KarasuTenguAttack2;
    attack3Anim = &Loader::KarasuTenguAttack3;
    hurtAnim = &Loader::KarasuTenguHurt;
    deadAnim = &Loader::KarasuTenguDead;

    currentAnim = idle1Anim;

    hp = 38.0f;
    damage = 11.0f;
    speed = 200.0f;
    
    // Hitbox for 96x96 sprite (smaller than skeletons)
    hitboxW = 38.0f;
    hitboxH = 68.0f;
    hitboxOffsetX = 29.0f;
    hitboxOffsetY = 28.0f;
}

EnemyYamabushiTengu::EnemyYamabushiTengu() : EnemyYokai()
{
    // Setup Yamabushi Tengu animations
    idle1Anim = &Loader::YamabushiTenguIdle1;
    idle2Anim = &Loader::YamabushiTenguIdle2;
    runAnim = &Loader::YamabushiTenguRun;
    walkAnim = &Loader::YamabushiTenguWalk;
    attack1Anim = &Loader::YamabushiTenguAttack1;
    attack2Anim = &Loader::YamabushiTenguAttack2;
    attack3Anim = &Loader::YamabushiTenguAttack3;
    hurtAnim = &Loader::YamabushiTenguHurt;
    deadAnim = &Loader::YamabushiTenguDead;

    currentAnim = idle1Anim;

    hp = 44.0f;
    damage = 13.0f;
    speed = 180.0f;
    
    // Hitbox for 96x96 sprite
    hitboxW = 40.0f;
    hitboxH = 70.0f;
    hitboxOffsetX = 28.0f;
    hitboxOffsetY = 26.0f;
}