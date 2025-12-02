#include "EnemySkeleton.h"
#include "system/Loader.h"

EnemySkeleton::EnemySkeleton() : Enemy()
{
    // Base skeleton setup
    hp = 35.0f;
    damage = 10.0f;
}

EnemySkeletonWarrior::EnemySkeletonWarrior() : EnemySkeleton()
{
    // Setup Skeleton Warrior animations
    idle1Anim = &Loader::SkeletonWarriorIdle;
    runAnim = &Loader::SkeletonWarriorRun;
    walkAnim = &Loader::SkeletonWarriorWalk;
    attack1Anim = &Loader::SkeletonWarriorAttack1;
    attack2Anim = &Loader::SkeletonWarriorAttack2;
    attack3Anim = &Loader::SkeletonWarriorAttack3;
    runAttackAnim = &Loader::SkeletonWarriorRunAttack;
    hurtAnim = &Loader::SkeletonWarriorHurt;
    deadAnim = &Loader::SkeletonWarriorDead;
    defendAnim = &Loader::SkeletonWarriorProtect;

    currentAnim = idle1Anim;

    hp = 35.0f;
    damage = 10.0f;
}

EnemySkeletonArcher::EnemySkeletonArcher() : EnemySkeleton()
{
    // Setup Skeleton Archer animations
    idle1Anim = &Loader::SkeletonArcherIdle;
    runAnim = &Loader::SkeletonArcherWalk;
    walkAnim = &Loader::SkeletonArcherWalk;
    attack1Anim = &Loader::SkeletonArcherAttack1;
    attack2Anim = &Loader::SkeletonArcherAttack2;
    attack3Anim = &Loader::SkeletonArcherAttack3;
    hurtAnim = &Loader::SkeletonArcherHurt;
    deadAnim = &Loader::SkeletonArcherDead;
    defendAnim = &Loader::SkeletonArcherEvasion;

    currentAnim = idle1Anim;

    hp = 28.0f;
    damage = 8.0f;
    speed = 140.0f;  // Archers are slower
}

EnemySkeletonSpearman::EnemySkeletonSpearman() : EnemySkeleton()
{
    // Setup Skeleton Spearman animations
    idle1Anim = &Loader::SkeletonSpearmanIdle;
    runAnim = &Loader::SkeletonSpearmanRun;
    walkAnim = &Loader::SkeletonSpearmanWalk;
    attack1Anim = &Loader::SkeletonSpearmanAttack1;
    attack2Anim = &Loader::SkeletonSpearmanAttack2;
    attack3Anim = &Loader::SkeletonSpearmanAttack1;  // Use attack1 if attack3 not available
    runAttackAnim = &Loader::SkeletonSpearmanRunAttack;
    hurtAnim = &Loader::SkeletonSpearmanHurt;
    deadAnim = &Loader::SkeletonSpearmanDead;
    defendAnim = &Loader::SkeletonSpearmanProtect;

    currentAnim = idle1Anim;

    hp = 42.0f;
    damage = 12.0f;
    speed = 160.0f;  // Spearmen are strong but slower
}
