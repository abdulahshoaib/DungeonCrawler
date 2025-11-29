#include "Skeleton_spearman.h"
#include "Loader.h"

Skeleton_spearman::Skeleton_spearman()
{
    *attack1Anim = Loader::SkeletonSpearmanAttack1;
    *attack2Anim = Loader::SkeletonSpearmanAttack2;
    *deadAnim = Loader::SkeletonSpearmanDead;
    *hurtAnim = Loader::SkeletonSpearmanHurt;
    *idle1Anim = Loader::SkeletonSpearmanIdle;
    *runAnim = Loader::SkeletonSpearmanRun;
    *walkAnim = Loader::SkeletonSpearmanWalk;
    *protectAnim = Loader::SkeletonSpearmanProtect;
    *runAttackAnim = Loader::SkeletonSpearmanRunAttack;

    currentAnim = idle1Anim;
}