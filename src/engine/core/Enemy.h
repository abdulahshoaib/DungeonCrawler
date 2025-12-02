#pragma once

#include "characters/Character.h"
#include "EnemyPath.h"
#include <raylib.h>
#include <cstddef>

// Enemy AI states
enum class EnemyAIState
{
    IDLE,        // Waiting at a waypoint
    PATROLLING,  // Moving along patrol path
    CHASING,     // Player within detection range - moving toward player
    ATTACKING,   // In combat range - attacking player
    KNOCKBACK,   // Hit by player attack
    DEAD         // Enemy defeated
};

class Enemy : public Character
{
private:
    // ===== AI BEHAVIOR =====
    EnemyAIState aiState = EnemyAIState::PATROLLING;
    EnemyPath *patrolPath = nullptr;
    size_t currentPathNode = 0;
    float pathPauseTimer = 0.0f;

    // ===== DETECTION & COMBAT =====
    float detectionRange = 200.0f;      // Distance at which to start chasing player
    float attackRange = 80.0f;           // Distance at which to attack player
    float attackCooldown = 0.0f;         // Cooldown between attacks
    float attackCooldownMax = 1.2f;      // Max cooldown time

    // ===== COMBAT TRACKING =====
    Character *targetPlayer = nullptr;   // Reference to player
    float chaseTimeMax = 5.0f;           // Max time to chase before returning to patrol
    float chaseTimer = 0.0f;

    // ===== KNOCKBACK =====
    float knockbackDuration = 0.0f;
    float knockbackDurationMax = 0.3f;
    Vector2 knockbackVelocity = {0, 0};

    // ===== DEBUG =====
    bool debugDraw = false;

public:
    Enemy();
    ~Enemy();

    // ===== INITIALIZATION =====
    void SetPatrolPath(EnemyPath *path) { patrolPath = path; }
    void SetTargetPlayer(Character *player) { targetPlayer = player; }
    void SetDetectionRange(float range) { detectionRange = range; }
    void SetAttackRange(float range) { attackRange = range; }
    void SetDebugDraw(bool debug) { debugDraw = debug; }

    // ===== STATE QUERIES =====
    EnemyAIState GetAIState() const { return aiState; }
    float GetDetectionRange() const { return detectionRange; }
    float GetAttackRange() const { return attackRange; }

    // ===== BEHAVIOR =====
    void Update(float dt, class Map &collisionMap);
    void DebugDraw() const;

    // ===== COMBAT =====
    void TakeDamage(float damage);
    void ApplyKnockback(Vector2 direction, float force);

private:
    // ===== PRIVATE BEHAVIOR METHODS =====
    void UpdatePatrol(float dt, Map &collisionMap);
    void UpdateChase(float dt, Map &collisionMap);
    void UpdateAttack(float dt);
    void UpdateKnockback(float dt, Map &collisionMap);

    // ===== PATHFINDING =====
    float GetDistanceToPlayer() const;
    bool IsPlayerInRange(float range) const;
    void MoveTowardTarget(Vector2 target, float dt);
    void MoveAlongPath(float dt, Map &collisionMap);

    // ===== ANIMATION =====
    void anim() override; // Implement from Character
};