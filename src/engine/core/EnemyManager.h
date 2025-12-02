#pragma once

#include "Enemy.h"
#include "EnemyPath.h"
#include <vector>
#include <memory>

class Map;
class Character;

// Manages all enemies: spawning, updating, rendering, and cleanup
class EnemyManager
{
private:
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<EnemyPath>> paths;
    Character *playerRef = nullptr;
    Map *collisionMapRef = nullptr;
    bool debugDraw = false;

public:
    EnemyManager();
    ~EnemyManager();

    // ===== INITIALIZATION =====
    void SetPlayerReference(Character *player) { playerRef = player; }
    void SetCollisionMapReference(Map *map) { collisionMapRef = map; }
    void SetDebugDraw(bool debug) { debugDraw = debug; }

    // ===== ENEMY CREATION =====
    // Create a new enemy without a path
    Enemy *SpawnEnemy(Vector2 startPos, float detectionRange = 200.0f, float attackRange = 80.0f);

    // Create a new enemy with a path
    Enemy *SpawnEnemyWithPath(Vector2 startPos, EnemyPath *path,
                              float detectionRange = 200.0f, float attackRange = 80.0f);

    // Template: Create a specific enemy type without a path
    template<typename EnemyType>
    EnemyType *SpawnEnemyType(Vector2 startPos, float detectionRange = 200.0f, float attackRange = 80.0f)
    {
        auto enemy = std::make_unique<EnemyType>();
        enemy->Pos = startPos;
        enemy->SetTargetPlayer(playerRef);
        enemy->SetDetectionRange(detectionRange);
        enemy->SetAttackRange(attackRange);
        enemy->SetDebugDraw(debugDraw);

        EnemyType *ptr = enemy.get();
        enemies.push_back(std::move(enemy));
        return ptr;
    }

    // Template: Create a specific enemy type with a path
    template<typename EnemyType>
    EnemyType *SpawnEnemyTypeWithPath(Vector2 startPos, EnemyPath *path,
                                      float detectionRange = 200.0f, float attackRange = 80.0f)
    {
        EnemyType *enemy = SpawnEnemyType<EnemyType>(startPos, detectionRange, attackRange);
        if (enemy && path)
        {
            enemy->SetPatrolPath(path);
        }
        return enemy;
    }

    // Create a new path for enemies to follow
    EnemyPath *CreatePath();

    // ===== PATH MANAGEMENT =====
    void AddPathNode(EnemyPath *path, Vector2 pos, float pauseTime = 0.0f);
    void SetPathLooping(EnemyPath *path, bool looping);

    // ===== ENEMY MANAGEMENT =====
    void Update(float dt);
    void Draw(class Animator &animator);
    void DebugDraw() const;

    // ===== QUERIES =====
    size_t GetEnemyCount() const { return enemies.size(); }
    Enemy *GetEnemy(size_t index);
    const Enemy *GetEnemy(size_t index) const;

    // ===== CLEANUP =====
    void RemoveDeadEnemies();
    void Clear();

    // ===== ENEMY INTERACTIONS =====
    // Called when player hits an enemy
    void DamageEnemy(size_t index, float damage, Vector2 knockbackDir, float knockbackForce);

    // Find enemies within a certain range of a position
    std::vector<size_t> GetEnemiesInRange(Vector2 pos, float range) const;

private:
    // ===== INTERNAL HELPERS =====
    void RemoveEnemy(size_t index);
};
