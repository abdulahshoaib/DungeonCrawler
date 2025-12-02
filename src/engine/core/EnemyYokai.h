#pragma once

#include "Enemy.h"

// Base Yokai enemy class
class EnemyYokai : public Enemy
{
public:
    EnemyYokai();
    ~EnemyYokai() = default;
};

// Karasu Tengu (crow demon)
class EnemyKarasuTengu : public EnemyYokai
{
public:
    EnemyKarasuTengu();
    ~EnemyKarasuTengu() = default;
};

// Yamabushi Tengu (mountain priest demon)
class EnemyYamabushiTengu : public EnemyYokai
{
public:
    EnemyYamabushiTengu();
    ~EnemyYamabushiTengu() = default;
};
