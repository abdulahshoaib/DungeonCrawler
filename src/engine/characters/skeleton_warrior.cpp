#include "skeleton_warrior.h"
#include "Loader.h"

Skeleton_warrior::Skeleton_warrior()
{
    *attack1Anim = Loader::SkeletonWarriorAttack1;
    *attack2Anim = Loader::SkeletonWarriorAttack2;
    *attack3Anim = Loader::SkeletonWarriorAttack3;
    *deadAnim = Loader::SkeletonWarriorDead;
    *hurtAnim = Loader::SkeletonWarriorHurt;
    *idle1Anim = Loader::SkeletonWarriorIdle;
    *protectAnim = Loader::SkeletonWarriorProtect;
    *runAnim = Loader::SkeletonWarriorRun;
    *runAttackAnim = Loader::SkeletonWarriorRunAttack;
    *walkAnim = Loader::SkeletonWarriorWalk;

    currentAnim = idle1Anim;
}