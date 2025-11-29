#include "Skeleton_archer.h"
#include "Loader.h"

Skeleton_archer::Skeleton_archer()
{
    attack1Anim = &Loader::SkeletonArcherAttack1;
    attack2Anim = &Loader::SkeletonArcherAttack2;
    attack3Anim = &Loader::SkeletonArcherAttack3;
    deadAnim   = &Loader::SkeletonArcherDead;
    hurtAnim   = &Loader::SkeletonArcherHurt;
    idle1Anim  = &Loader::SkeletonArcherIdle;
    shot1Anim  = &Loader::SkeletonArcherShot1;
    shot2Anim  = &Loader::SkeletonArcherShot2;
    evasionAnim = &Loader::SkeletonArcherEvasion;
    walkAnim    = &Loader::SkeletonArcherWalk;

    currentAnim = idle1Anim;   // start idle
}