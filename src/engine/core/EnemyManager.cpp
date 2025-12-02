#include "EnemyManager.h"
#include "Map.h"
#include "system/Animator.h"
#include <algorithm>
#include <cmath>

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
    Clear();
}

Enemy *EnemyManager::SpawnEnemy(Vector2 startPos, float detectionRange, float attackRange)
{
    auto enemy = std::make_unique<Enemy>();
    enemy->Pos = startPos;
    enemy->SetTargetPlayer(playerRef);
    enemy->SetDetectionRange(detectionRange);
    enemy->SetAttackRange(attackRange);
    enemy->SetDebugDraw(debugDraw);

    Enemy *ptr = enemy.get();
    enemies.push_back(std::move(enemy));
    return ptr;
}

Enemy *EnemyManager::SpawnEnemyWithPath(Vector2 startPos, EnemyPath *path,
                                        float detectionRange, float attackRange)
{
    Enemy *enemy = SpawnEnemy(startPos, detectionRange, attackRange);
    if (enemy && path)
    {
        enemy->SetPatrolPath(path);
    }
    return enemy;
}

EnemyPath *EnemyManager::CreatePath()
{
    auto path = std::make_unique<EnemyPath>();
    EnemyPath *ptr = path.get();
    paths.push_back(std::move(path));
    return ptr;
}

void EnemyManager::AddPathNode(EnemyPath *path, Vector2 pos, float pauseTime)
{
    if (path)
    {
        path->AddNode(pos, pauseTime);
    }
}

void EnemyManager::SetPathLooping(EnemyPath *path, bool looping)
{
    if (path)
    {
        path->SetLooping(looping);
    }
}

void EnemyManager::Update(float dt)
{
    if (!collisionMapRef)
        return;

    for (auto &enemy : enemies)
    {
        if (enemy)
        {
            enemy->Update(dt, *collisionMapRef);
        }
    }

    RemoveDeadEnemies();
}

void EnemyManager::Draw(Animator &animator)
{
    for (auto &enemy : enemies)
    {
        if (enemy)
        {
            animator.Draw(enemy.get());
        }
    }
}

void EnemyManager::DebugDraw() const
{
    for (const auto &enemy : enemies)
    {
        if (enemy)
        {
            enemy->DebugDraw();
        }
    }
}

Enemy *EnemyManager::GetEnemy(size_t index)
{
    if (index >= enemies.size())
        return nullptr;
    return enemies[index].get();
}

const Enemy *EnemyManager::GetEnemy(size_t index) const
{
    if (index >= enemies.size())
        return nullptr;
    return enemies[index].get();
}

void EnemyManager::RemoveDeadEnemies()
{
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](const std::unique_ptr<Enemy> &e)
                       { return e && e->GetAIState() == EnemyAIState::DEAD && e->hp <= 0; }),
        enemies.end());
}

void EnemyManager::Clear()
{
    enemies.clear();
    paths.clear();
}

void EnemyManager::DamageEnemy(size_t index, float damage, Vector2 knockbackDir, float knockbackForce)
{
    Enemy *enemy = GetEnemy(index);
    if (enemy)
    {
        enemy->TakeDamage(damage);
        enemy->ApplyKnockback(knockbackDir, knockbackForce);
    }
}

std::vector<size_t> EnemyManager::GetEnemiesInRange(Vector2 pos, float range) const
{
    std::vector<size_t> result;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        if (!enemies[i])
            continue;

        Vector2 enemyCenter = {
            enemies[i]->Pos.x + enemies[i]->hitboxOffsetX + enemies[i]->hitboxW * 0.5f,
            enemies[i]->Pos.y + enemies[i]->hitboxOffsetY + enemies[i]->hitboxH * 0.5f};

        float dx = enemyCenter.x - pos.x;
        float dy = enemyCenter.y - pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < range)
        {
            result.push_back(i);
        }
    }

    return result;
}

void EnemyManager::RemoveEnemy(size_t index)
{
    if (index < enemies.size())
    {
        enemies.erase(enemies.begin() + index);
    }
}

void EnemyManager::LoadPathsFromCSV(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        // File doesn't exist yet, that's okay
        return;
    }

    char line[65536];
    int pathCount = 0;

    // Read number of paths
    if (fgets(line, sizeof(line), file))
    {
        pathCount = atoi(line);
    }

    // Read each path
    for (int p = 0; p < pathCount; p++)
    {
        if (fgets(line, sizeof(line), file))
        {
            EnemyPath *path = CreatePath();
            int pathIndex, nodeCount, isLooping;

            // Parse first three values
            sscanf(line, "%d,%d,%d", &pathIndex, &nodeCount, &isLooping);
            path->SetLooping(isLooping != 0);

            // Parse remaining values (coordinates and pause times)
            char *ptr = line;
            int commaCount = 0;
            while (*ptr && commaCount < 3)
            {
                if (*ptr == ',')
                    commaCount++;
                ptr++;
            }

            // Parse nodes
            for (int n = 0; n < nodeCount; n++)
            {
                int x, y;
                float pauseTime;
                int result = sscanf(ptr, "%d,%d,%f", &x, &y, &pauseTime);
                if (result == 3)
                {
                    path->AddNode({(float)x * 32.0f, (float)y * 32.0f}, pauseTime);

                    // Skip to next triplet
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                    while (*ptr && *ptr != ',')
                        ptr++;
                    if (*ptr)
                        ptr++; // skip comma
                }
            }
        }
    }

    fclose(file);
}

EnemyPath *EnemyManager::GetPath(size_t index)
{
    if (index < paths.size())
    {
        return paths[index].get();
    }
    return nullptr;
}
