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
    hp = 50.0f;
    maxHp = hp;
    damage = 8.0f;
    speed = 180.0f;

    // Hitbox for enemy (128x128 sprite)
    // Make hitbox tighter and aligned to bottom of sprite
    hitboxW = 50.0f;
    hitboxH = 90.0f;
    hitboxOffsetX = 39.0f; // Center horizontally in 128px sprite
    hitboxOffsetY = 38.0f; // Align to bottom, feet at y=128

    animState = AnimState::IDLE;
}

Enemy::~Enemy()
{
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
        break;
    case EnemyAIState::IDLE:
    default:
        break;
    }

    // Check for player detection and state transitions
    if (targetPlayer && aiState != EnemyAIState::KNOCKBACK && aiState != EnemyAIState::DEAD)
    {
        float distToPlayer = GetDistanceToPlayer();

        if (distToPlayer < attackRange)
        {
            if (aiState != EnemyAIState::ATTACKING)
            {
                aiState = EnemyAIState::ATTACKING;
                velocityX = 0;
            }
        }
        else if (distToPlayer < detectionRange)
        {
            if (aiState != EnemyAIState::ATTACKING)
            {
                aiState = EnemyAIState::CHASING;
                chaseTimer = chaseTimeMax;
            }
        }
        else
        {
            if (aiState == EnemyAIState::CHASING)
            {
                aiState = EnemyAIState::PATROLLING;
            }
        }
    }

    // Apply physics
    ApplyPhysics(dt);

    // Handle collisions with tilemap
    for (int i = 0; i < 3; i++)
    {
        HandleCollisions(collisionMap);
    }

    // Update animation
    anim();
}

void Enemy::HandleCollisions(Map &collisionMap)
{
    Rectangle hitbox = GetHitboxRect();
    isGrounded = false;

    // Check bottom/ground collision first (more important)
    Rectangle feetCheck = {hitbox.x + 2, hitbox.y + hitbox.height - 2, hitbox.width - 4, 4};
    if (collisionMap.CheckCollisionRect(feetCheck))
    {
        isGrounded = true;
    }

    // Handle horizontal collisions
    if (velocityX != 0)
    {
        Rectangle horizontalCheck = hitbox;
        if (collisionMap.CheckCollisionRect(horizontalCheck))
        {
            int tx, ty;
            if (collisionMap.GetFirstCollisionTile(horizontalCheck, tx, ty))
            {
                float tileSize = collisionMap.GetTileSize();

                // Push out of collision based on movement direction
                if (velocityX > 0)
                {
                    // Moving right - push left
                    Pos.x = tx * tileSize - hitboxOffsetX - hitboxW - 1;
                }
                else if (velocityX < 0)
                {
                    // Moving left - push right
                    Pos.x = (tx + 1) * tileSize - hitboxOffsetX + 1;
                }
                velocityX = 0;
            }
        }
    }

    // Handle vertical collisions
    hitbox = GetHitboxRect(); // Recalculate after horizontal adjustment

    if (collisionMap.CheckCollisionRect(hitbox))
    {
        int tx, ty;
        if (collisionMap.GetFirstCollisionTile(hitbox, tx, ty))
        {
            float tileSize = collisionMap.GetTileSize();
            float tileY = ty * tileSize;

            if (velocityY > 0)
            {
                // Falling - land on top of tile
                Pos.y = tileY - hitboxOffsetY - hitboxH;
                velocityY = 0;
                isGrounded = true;
            }
            else if (velocityY < 0)
            {
                // Jumping - hit ceiling
                Pos.y = (ty + 1) * tileSize - hitboxOffsetY;
                velocityY = 0;
            }
        }
    }
}

void Enemy::UpdatePatrol(float dt, Map &collisionMap)
{
    if (!patrolPath || !patrolPath->IsValid())
    {
        aiState = EnemyAIState::IDLE;
        ChangeAnimState(AnimState::IDLE);
        velocityX = 0;
        return;
    }

    Vector2 targetNode = patrolPath->GetNode(currentPathNode);

    Vector2 enemyCenter = {
        Pos.x + hitboxOffsetX + hitboxW * 0.5f,
        Pos.y + hitboxOffsetY + hitboxH * 0.5f};

    float dx = targetNode.x - enemyCenter.x;
    float dy = targetNode.y - enemyCenter.y;
    float distToNode = std::sqrt(dx * dx + dy * dy);

    const float WAYPOINT_REACH_DISTANCE = 48.0f; // Increased from 32 to make it easier to reach

    // Check if we've reached the current waypoint
    if (distToNode < WAYPOINT_REACH_DISTANCE)
    {
        // At waypoint - handle pause
        if (pathPauseTimer > 0)
        {
            pathPauseTimer -= dt;
            ChangeAnimState(AnimState::IDLE);
            velocityX = 0;
            return;
        }

        // Pause time expired, move to next waypoint
        currentPathNode++;

        if (currentPathNode >= patrolPath->GetNodeCount())
        {
            if (patrolPath->IsLooping())
            {
                currentPathNode = 0;
            }
            else
            {
                aiState = EnemyAIState::IDLE;
                ChangeAnimState(AnimState::IDLE);
                velocityX = 0;
                return;
            }
        }

        // Set pause time for new waypoint
        pathPauseTimer = patrolPath->GetPauseTime(currentPathNode);

        // If pause time is 0, continue moving immediately
        if (pathPauseTimer <= 0)
        {
            targetNode = patrolPath->GetNode(currentPathNode);
            MoveTowardTarget(targetNode, dt);
            ChangeAnimState(AnimState::WALK);
        }
        else
        {
            // Start pausing
            velocityX = 0;
            ChangeAnimState(AnimState::IDLE);
        }
    }
    else
    {
        // Not at waypoint yet - keep moving
        // Only move if we're on the ground to prevent glitching
        if (isGrounded)
        {
            MoveTowardTarget(targetNode, dt);
            ChangeAnimState(AnimState::WALK);
        }
        else
        {
            // In air - let physics handle it
            velocityX *= 0.95f; // Slight air resistance
        }
    }
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
        aiState = EnemyAIState::PATROLLING;
        currentPathNode = 0;
        pathPauseTimer = 0;
        return;
    }

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

    velocityX = 0;

    float distToPlayer = GetDistanceToPlayer();
    if (distToPlayer > attackRange * 1.2f)
    {
        aiState = EnemyAIState::CHASING;
        chaseTimer = chaseTimeMax;
        return;
    }

    Vector2 playerCenter = {
        targetPlayer->Pos.x + targetPlayer->hitboxOffsetX + targetPlayer->hitboxW * 0.5f,
        targetPlayer->Pos.y};
    bool playerToRight = playerCenter.x > Pos.x;
    SetFacingLeft(!playerToRight);

    if (attackCooldown <= 0 && !IsAnimationLocked())
    {
        ChangeAnimState(AnimState::ATTACK1);
        attackCooldown = attackCooldownMax;
    }
    else if (IsAnimationLocked() == false)
    {
        ChangeAnimState(AnimState::IDLE);
    }
}

void Enemy::UpdateKnockback(float dt, Map &collisionMap)
{
    knockbackDuration -= dt;

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
    bool facingRight = dx > 0;
    SetFacingLeft(!facingRight);

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
#ifdef DEBUG
    Vector2 center = {Pos.x + hitboxOffsetX + hitboxW * 0.5f,
                      Pos.y + hitboxOffsetY + hitboxH * 0.5f};

    DrawCircleLines((int)center.x, (int)center.y, (int)detectionRange, ORANGE);
    DrawCircleLines((int)center.x, (int)center.y, (int)attackRange, RED);

    if (patrolPath && patrolPath->IsValid() && currentPathNode < patrolPath->GetNodeCount())
    {
        Vector2 waypoint = patrolPath->GetNode(currentPathNode);
        DrawCircle((int)waypoint.x, (int)waypoint.y, 6, PURPLE);
    }

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
#endif
}