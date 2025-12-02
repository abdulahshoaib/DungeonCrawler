#include "Enemy.h"
#include "Map.h"
#include "system/Loader.h"
#include <cmath>
#include <algorithm>

Enemy::Enemy() : Character()
{
    // Initialize animations from Loader using pointers (like Knight1 does)
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

    // Default enemy stats
    hp = 30.0f;
    damage = 8.0f;
    speed = 120.0f;

    // Hitbox for enemy (adjust as needed)
    hitboxW = 48.0f;
    hitboxH = 80.0f;
    hitboxOffsetX = 40.0f;
    hitboxOffsetY = 48.0f;

    animState = AnimState::IDLE;
}

Enemy::~Enemy()
{
    // Path is managed externally, don't delete
    patrolPath = nullptr;
    targetPlayer = nullptr;
}

void Enemy::Update(float dt, Map &collisionMap)
{
    if (hp <= 0)
    {
        aiState = EnemyAIState::DEAD;
        ChangeAnimState(AnimState::DEAD);
        return;
    }

    // Update combat timers
    if (attackCooldown > 0)
        attackCooldown -= dt;

    if (chaseTimer > 0)
        chaseTimer -= dt;

    // State machine
    switch (aiState)
    {
    case EnemyAIState::PATROLLING:
        UpdatePatrol(dt, collisionMap);
        break;
    case EnemyAIState::CHASING:
        UpdateChase(dt, collisionMap);
        break;
    case EnemyAIState::ATTACKING:
        UpdateAttack(dt);
        break;
    case EnemyAIState::KNOCKBACK:
        UpdateKnockback(dt, collisionMap);
        break;
    case EnemyAIState::DEAD:
        // Stay dead
        break;
    case EnemyAIState::IDLE:
    default:
        // Idle state - do nothing
        break;
    }

    // Check for player detection and state transitions
    // Don't interrupt ATTACKING state unless player is out of range
    if (targetPlayer && aiState != EnemyAIState::KNOCKBACK && aiState != EnemyAIState::DEAD)
    {
        float distToPlayer = GetDistanceToPlayer();

        if (distToPlayer < attackRange)
        {
            // Close enough to attack - transition to attacking state
            if (aiState != EnemyAIState::ATTACKING)
            {
                aiState = EnemyAIState::ATTACKING;
                velocityX = 0;
            }
        }
        else if (distToPlayer < detectionRange)
        {
            // Player detected - start chasing (but not if already attacking)
            if (aiState != EnemyAIState::ATTACKING)
            {
                aiState = EnemyAIState::CHASING;
                chaseTimer = chaseTimeMax;
            }
        }
        else
        {
            // Player out of range - go back to patrol if not attacking
            if (aiState == EnemyAIState::CHASING)
            {
                aiState = EnemyAIState::PATROLLING;
            }
        }
    }

    // Apply physics
    ApplyPhysics(dt);

    // Collision resolution
    if (collisionMap.CheckCollisionRect(GetHitboxRect()))
    {
        int tx, ty;
        if (collisionMap.GetFirstCollisionTile(GetHitboxRect(), tx, ty))
        {
            if (velocityY > 0)
            {
                // moving down: place hitbox on top of the tile
                Pos.y = ty * collisionMap.GetTileSize() - (hitboxOffsetY + hitboxH);
                isGrounded = true;
            }
            else
            {
                // moving up: place below the tile
                Pos.y = (ty + 1) * collisionMap.GetTileSize() - hitboxOffsetY;
            }
        }
        // Stop vertical motion
        velocityY = 0;
    }

    // Update animation
    anim();
}

void Enemy::UpdatePatrol(float dt, Map &collisionMap)
{
    // If no path, stay idle
    if (!patrolPath || !patrolPath->IsValid())
    {
        aiState = EnemyAIState::IDLE;
        ChangeAnimState(AnimState::IDLE);
        velocityX = 0;
        return;
    }

    // Get target waypoint
    Vector2 targetNode = patrolPath->GetNode(currentPathNode);
    float distToNode = std::sqrt(
        (Pos.x - targetNode.x) * (Pos.x - targetNode.x) +
        (Pos.y - targetNode.y) * (Pos.y - targetNode.y));

    const float WAYPOINT_REACH_DISTANCE = 16.0f;

    // Check if we've reached the current waypoint
    if (distToNode < WAYPOINT_REACH_DISTANCE)
    {
        // Reached waypoint - decrement pause timer
        pathPauseTimer -= dt;

        if (pathPauseTimer <= 0)
        {
            // Pause time expired, move to next waypoint
            pathPauseTimer = 0;
            currentPathNode++;

            if (currentPathNode >= patrolPath->GetNodeCount())
            {
                if (patrolPath->IsLooping())
                {
                    currentPathNode = 0;
                }
                else
                {
                    // End of path - stay idle
                    aiState = EnemyAIState::IDLE;
                    ChangeAnimState(AnimState::IDLE);
                    velocityX = 0;
                    return;
                }
            }

            // Set pause time for the new waypoint we just advanced to
            pathPauseTimer = patrolPath->GetPauseTime(currentPathNode);
        }
        else
        {
            // Still pausing at waypoint
            ChangeAnimState(AnimState::IDLE);
            velocityX = 0;
            return;
        }
    }

    // Move toward the current target waypoint
    targetNode = patrolPath->GetNode(currentPathNode);
    MoveTowardTarget(targetNode, dt);
    ChangeAnimState(AnimState::WALK);
}

void Enemy::UpdateChase(float dt, Map &collisionMap)
{
    if (!targetPlayer)
    {
        aiState = EnemyAIState::PATROLLING;
        return;
    }

    chaseTimer -= dt;
    if (chaseTimer <= 0)
    {
        // Chase timeout - return to patrol
        aiState = EnemyAIState::PATROLLING;
        currentPathNode = 0;
        pathPauseTimer = 0;
        return;
    }

    // Move toward player
    Vector2 playerCenter = {
        targetPlayer->Pos.x + targetPlayer->hitboxOffsetX + targetPlayer->hitboxW * 0.5f,
        targetPlayer->Pos.y + targetPlayer->hitboxOffsetY + targetPlayer->hitboxH * 0.5f};

    MoveTowardTarget(playerCenter, dt);
    ChangeAnimState(AnimState::RUN);
}

void Enemy::UpdateAttack(float dt)
{
    if (!targetPlayer)
    {
        aiState = EnemyAIState::CHASING;
        chaseTimer = chaseTimeMax;
        return;
    }

    velocityX = 0; // Stop moving while attacking

    float distToPlayer = GetDistanceToPlayer();
    if (distToPlayer > attackRange * 1.2f)
    {
        // Player moved out of range - resume chasing
        aiState = EnemyAIState::CHASING;
        chaseTimer = chaseTimeMax;
        return;
    }

    // Face the player
    Vector2 playerCenter = {
        targetPlayer->Pos.x + targetPlayer->hitboxOffsetX + targetPlayer->hitboxW * 0.5f,
        targetPlayer->Pos.y};
    bool playerToRight = playerCenter.x > Pos.x;
    SetFacingLeft(!playerToRight);

    // Attack when ready and not locked
    if (attackCooldown <= 0 && !IsAnimationLocked())
    {
        ChangeAnimState(AnimState::ATTACK1);
        attackCooldown = attackCooldownMax;
    }
    // If animation is done and cooldown ready, keep playing idle until next attack
    else if (IsAnimationLocked() == false)
    {
        ChangeAnimState(AnimState::IDLE);
    }
}

void Enemy::UpdateKnockback(float dt, Map &collisionMap)
{
    knockbackDuration -= dt;

    // Apply knockback velocity
    velocityX = knockbackVelocity.x;
    velocityY = knockbackVelocity.y;

    if (knockbackDuration <= 0)
    {
        knockbackDuration = 0;
        aiState = EnemyAIState::CHASING;
        chaseTimer = chaseTimeMax;
    }
}

float Enemy::GetDistanceToPlayer() const
{
    if (!targetPlayer)
        return 999999.0f;

    Vector2 playerCenter = {
        targetPlayer->Pos.x + targetPlayer->hitboxOffsetX + targetPlayer->hitboxW * 0.5f,
        targetPlayer->Pos.y + targetPlayer->hitboxOffsetY + targetPlayer->hitboxH * 0.5f};

    Vector2 enemyCenter = {
        Pos.x + hitboxOffsetX + hitboxW * 0.5f,
        Pos.y + hitboxOffsetY + hitboxH * 0.5f};

    float dx = playerCenter.x - enemyCenter.x;
    float dy = playerCenter.y - enemyCenter.y;

    return std::sqrt(dx * dx + dy * dy);
}

bool Enemy::IsPlayerInRange(float range) const
{
    return GetDistanceToPlayer() < range;
}

void Enemy::MoveTowardTarget(Vector2 target, float dt)
{
    Vector2 enemyCenter = {
        Pos.x + hitboxOffsetX + hitboxW * 0.5f,
        Pos.y + hitboxOffsetY + hitboxH * 0.5f};

    float dx = target.x - enemyCenter.x;
    float dy = target.y - enemyCenter.y;

    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 1.0f)
    {
        velocityX = 0;
        return;
    }

    // Normalize direction
    dx /= distance;

    // Set facing direction
    bool facingPlayerRight = dx > 0;
    SetFacingLeft(!facingPlayerRight);

    // Move with constant speed
    velocityX = dx * speed;
}

void Enemy::TakeDamage(float damage)
{
    hp -= damage;
    if (hp < 0)
        hp = 0;

    if (hp <= 0)
    {
        aiState = EnemyAIState::DEAD;
        ChangeAnimState(AnimState::DEAD);
    }
    else
    {
        // Brief knockback and hurt animation
        if (aiState != EnemyAIState::KNOCKBACK)
        {
            aiState = EnemyAIState::KNOCKBACK;
            ChangeAnimState(AnimState::HURT);
        }
    }
}

void Enemy::ApplyKnockback(Vector2 direction, float force)
{
    float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (len > 0)
    {
        direction.x /= len;
        direction.y /= len;
    }

    knockbackVelocity = {direction.x * force, direction.y * force};
    knockbackDuration = knockbackDurationMax;
    aiState = EnemyAIState::KNOCKBACK;
    ChangeAnimState(AnimState::HURT);
}

void Enemy::anim()
{
    // Switch animation based on current state
    switch (animState)
    {
    case AnimState::IDLE:
        currentAnim = idle1Anim;
        break;
    case AnimState::WALK:
        currentAnim = walkAnim;
        break;
    case AnimState::RUN:
        currentAnim = runAnim;
        break;
    case AnimState::ATTACK1:
        currentAnim = attack1Anim;
        break;
    case AnimState::ATTACK2:
        currentAnim = attack2Anim;
        break;
    case AnimState::ATTACK3:
        currentAnim = attack3Anim;
        break;
    case AnimState::RUN_ATTACK:
        currentAnim = runAttackAnim;
        break;
    case AnimState::HURT:
        currentAnim = hurtAnim;
        break;
    case AnimState::DEAD:
        currentAnim = deadAnim;
        break;
    default:
        currentAnim = idle1Anim;
        break;
    }
}

void Enemy::DebugDraw() const
{
    if (!debugDraw)
        return;

    // Draw detection range
    Vector2 center = {Pos.x + hitboxOffsetX + hitboxW * 0.5f,
                      Pos.y + hitboxOffsetY + hitboxH * 0.5f};

    DrawCircleLines((int)center.x, (int)center.y, (int)detectionRange, ORANGE);
    DrawCircleLines((int)center.x, (int)center.y, (int)attackRange, RED);

    // Draw current waypoint if patrolling
    if (patrolPath && patrolPath->IsValid() && currentPathNode < patrolPath->GetNodeCount())
    {
        Vector2 waypoint = patrolPath->GetNode(currentPathNode);
        DrawCircle((int)waypoint.x, (int)waypoint.y, 6, PURPLE);
    }

    // Draw AI state text
    const char *stateStr = "";
    switch (aiState)
    {
    case EnemyAIState::IDLE:
        stateStr = "IDLE";
        break;
    case EnemyAIState::PATROLLING:
        stateStr = "PATROL";
        break;
    case EnemyAIState::CHASING:
        stateStr = "CHASE";
        break;
    case EnemyAIState::ATTACKING:
        stateStr = "ATTACK";
        break;
    case EnemyAIState::KNOCKBACK:
        stateStr = "KNOCKBACK";
        break;
    case EnemyAIState::DEAD:
        stateStr = "DEAD";
        break;
    }
    DrawText(stateStr, (int)center.x - 20, (int)center.y - 20, 10, WHITE);
}
