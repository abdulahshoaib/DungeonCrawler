#pragma once

#include "Enemy.h"

// Base skeleton enemy class with different variants
class EnemySkeleton : public Enemy
{
public:
    EnemySkeleton();
    ~EnemySkeleton() = default;
};

// Skeleton Warrior
class EnemySkeletonWarrior : public EnemySkeleton
{
public:
    EnemySkeletonWarrior();
    ~EnemySkeletonWarrior() = default;
};

// Skeleton Archer
class EnemySkeletonArcher : public EnemySkeleton
{
public:
    EnemySkeletonArcher();
    ~EnemySkeletonArcher() = default;
};

// Skeleton Spearman
class EnemySkeletonSpearman : public EnemySkeleton
{
public:
    EnemySkeletonSpearman();
    ~EnemySkeletonSpearman() = default;
};
