#include "GameManager.h"
#include "PauseState.h"
#include "state/DeathState.h"
#include "state/EndState.h"

#include "characters/Knight1.h"
#include "characters/Knight2.h"
#include "characters/Knight3.h"
#include "characters/Samurai.h"
#include "characters/SamuraiArcher.h"
#include "characters/SamuraiCommander.h"

#include "characters/AnimStates.h"

#include "EnemySkeleton.h"
#include "EnemyYokai.h"
#include "Audio.h"

#include <cmath>
#include <string>
#include <algorithm>

#define KNIGHT1 1
#define KNIGHT2 2
#define KNIGHT3 3
#define SAMURAI 4
#define SAMURAI_COMMANDER 5
#define SAMURAI_ARCHER 6

GameManager::GameManager(int ID)
{
    // layer order: interactables, non-colliding visuals, collidable map
    interactables.LoadMap("assets/maps/interactables.csv");
    map_non_colliding.LoadMap("assets/maps/non_colliding.csv");
    map_collide.LoadMap("assets/maps/map.csv");

    map_collide.SetCollisionTopMargin(2);

    camera.offset = {(float)GetScreenWidth() * 0.5f, (float)GetScreenHeight() * 0.5f};
    camera.rotation = 0.0f;
    camera.zoom = 2.00f;

    switch (ID)
    {
    case KNIGHT1:
    {
        hud.playerName = "Lionheart";
        hud.Potrait = Loader::Knight1HUD;
        player = new Knight1();
        break;
    }
    case KNIGHT2:
    {
        hud.playerName = "Van Gaurd";
        hud.Potrait = Loader::Knight2HUD;
        player = new Knight2();
        break;
    }
    case KNIGHT3:
    {
        hud.playerName = "Valerius";
        hud.Potrait = Loader::Knight3HUD;
        player = new Knight3();
        break;
    }
    case SAMURAI:
    {
        hud.playerName = "Akuna Bushi";
        hud.Potrait = Loader::SamuraiHUD;
        player = new Samurai();
        break;
    }
    case SAMURAI_ARCHER:
    {
        hud.playerName = "Kengi";
        hud.Potrait = Loader::SamuraiArcherHUD;
        player = new SamuraiArcher();
        break;
    }
    case SAMURAI_COMMANDER:
    {
        hud.playerName = "Shogun Kengi";
        hud.Potrait = Loader::SamuraiCommanderHUD;
        player = new SamuraiCommander();
        break;
    }
    }

    // Adjust player hitbox if available
    if (player && player->currentAnim)
    {
        player->hitboxW = player->currentAnim->frameWidth * 0.40f;
        player->hitboxH = player->currentAnim->frameHeight * 0.65f;
        player->hitboxOffsetX = (player->currentAnim->frameWidth - player->hitboxW) * 0.5f;
        player->hitboxOffsetY = player->currentAnim->frameHeight - player->hitboxH;
    }

    enemyManager.SetPlayerReference(player);
    enemyManager.SetCollisionMapReference(&map_collide);
    enemyManager.SetDebugDraw(debugDrawCollision);

    hud.SetPlayer(player);

    // Load enemy paths from CSV
    enemyManager.LoadPathsFromCSV("assets/maps/enemy_paths.csv");

    // Spawn enemies at proper positions
    if (enemyManager.GetPathCount() > 0)
    {
        EnemyPath *path = enemyManager.GetPath(0);
        if (path && path->IsValid())
        {
            Vector2 nodePos = path->GetNode(0);
            Vector2 startPos = {nodePos.x - 64.0f, nodePos.y - 128.0f};
            enemyManager.SpawnEnemyTypeWithPath<EnemySkeletonWarrior>(startPos, path, 200.0f, 80.0f);
        }
    }

    if (enemyManager.GetPathCount() > 1)
    {
        EnemyPath *path = enemyManager.GetPath(1);
        if (path && path->IsValid())
        {
            Vector2 nodePos = path->GetNode(0);
            Vector2 startPos = {nodePos.x - 64.0f, nodePos.y - 128.0f};
            enemyManager.SpawnEnemyTypeWithPath<EnemySkeletonArcher>(startPos, path, 200.0f, 80.0f);
        }
    }

    if (enemyManager.GetPathCount() > 2)
    {
        EnemyPath *path = enemyManager.GetPath(2);
        if (path && path->IsValid())
        {
            Vector2 nodePos = path->GetNode(0);
            Vector2 startPos = {nodePos.x - 64.0f, nodePos.y - 128.0f};
            enemyManager.SpawnEnemyTypeWithPath<EnemySkeletonSpearman>(startPos, path, 200.0f, 80.0f);
        }
    }

    if (enemyManager.GetPathCount() > 3)
    {
        EnemyPath *path = enemyManager.GetPath(3);
        if (path && path->IsValid())
        {
            Vector2 nodePos = path->GetNode(0);
            Vector2 startPos = {nodePos.x - 48.0f, nodePos.y - 96.0f};
            enemyManager.SpawnEnemyTypeWithPath<EnemyKarasuTengu>(startPos, path, 200.0f, 80.0f);
        }
    }

    if (enemyManager.GetPathCount() > 4)
    {
        EnemyPath *path = enemyManager.GetPath(4);
        if (path && path->IsValid())
        {
            Vector2 nodePos = path->GetNode(0);
            Vector2 startPos = {nodePos.x - 48.0f, nodePos.y - 96.0f};
            enemyManager.SpawnEnemyTypeWithPath<EnemyYamabushiTengu>(startPos, path, 200.0f, 80.0f);
        }
    }

    // Load coins from interactables layer (tile ID 397)
    for (int y = 0; y < interactables.GetHeight(); y++)
    {
        for (int x = 0; x < interactables.GetWidth(); x++)
        {
            if (interactables.GetTile(x, y) == 397)
            {
                float posX = x * interactables.GetTileSize();
                float posY = y * interactables.GetTileSize();
                coins.emplace_back(posX, posY);
            }
        }
    }

    // If loading saved game, restore coin positions and player position
    if (GameProgress::IsDataLoaded())
    {
        const auto &saved = GameProgress::GetRemainingCoins();
        if (!saved.empty())
        {
            coins.clear();
            // Clear all coin tiles first
            for (int y = 0; y < interactables.GetHeight(); y++)
                for (int x = 0; x < interactables.GetWidth(); x++)
                    if (interactables.GetTile(x, y) == 397)
                        interactables.SetTile(x, y, 0);

            // Restore saved coins
            int tileSize = interactables.GetTileSize();
            for (const auto &p : saved)
            {
                coins.emplace_back(p.x, p.y);
                int tx = (int)(p.x / tileSize);
                int ty = (int)(p.y / tileSize);
                if (tx >= 0 && ty >= 0 && tx < interactables.GetWidth() && ty < interactables.GetHeight())
                {
                    interactables.SetTile(tx, ty, 397);
                }
            }
        }

        // Restore player position
        if (player)
        {
            Vector2 savedPos = GameProgress::GetMapPosition();
            if (savedPos.x != 0.0f || savedPos.y != 0.0f)
            {
                player->Pos = savedPos;
            }
        }
    }
}

GameManager::~GameManager()
{
    enemyManager.Clear();
}

void GameManager::Update(Engine &engine)
{
    float dt = GetFrameTime();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine.PushState(new PauseState());
        return;
    }

    if (currentComboStep > 0)
    {
        comboTimer -= dt;
        if (comboTimer <= 0.0f)
        {
            currentComboStep = 0;
            comboTimer = 0.0f;
        }
    }

#ifdef DEBUG
    if (IsKeyPressed(KEY_F1))
    {
        debugDrawCollision = !debugDrawCollision;
    }

    bool cameraDebugMode = IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
    float cameraPanSpeed = 10.0f;
    if (cameraDebugMode)
    {
        if (IsKeyDown(KEY_UP))
            camera.target.y -= cameraPanSpeed;
        if (IsKeyDown(KEY_DOWN))
            camera.target.y += cameraPanSpeed;
        if (IsKeyDown(KEY_LEFT))
            camera.target.x -= cameraPanSpeed;
        if (IsKeyDown(KEY_RIGHT))
            camera.target.x += cameraPanSpeed;
    }
#endif

    if (player
#ifdef DEBUG
        && !cameraDebugMode
#endif
    )
    {
        Vector2 hitCenter = {player->Pos.x + player->hitboxOffsetX + player->hitboxW * 0.5f,
                             player->Pos.y + player->hitboxOffsetY + player->hitboxH * 0.5f};
        
        // Smooth camera follow using lerp
        camera.target.x += (hitCenter.x - camera.target.x) * cameraLerpSpeed * dt;
        camera.target.y += (hitCenter.y - camera.target.y) * cameraLerpSpeed * dt;

        float halfViewW = camera.offset.x / camera.zoom;
        float halfViewH = camera.offset.y / camera.zoom;

        int tileSize = map_collide.GetTileSize();
        float worldW = map_collide.GetWidth() * (float)tileSize;
        float worldH = map_collide.GetHeight() * (float)tileSize;

        float minX = halfViewW;
        float maxX = worldW - halfViewW;
        float minY = halfViewH;
        float maxY = worldH - halfViewH;

        if (maxX < minX)
        {
            minX = maxX = worldW * 0.5f;
        }
        if (maxY < minY)
        {
            minY = maxY = worldH - halfViewH;
        }

#if __cplusplus >= 201703L
        camera.target.x = std::clamp(camera.target.x, minX, maxX);
        camera.target.y = std::clamp(camera.target.y, minY, maxY);
#else
        camera.target.x = fmax(minX, fmin(maxX, camera.target.x));
        camera.target.y = fmax(minY, fmin(maxY, camera.target.y));
#endif

        // Apply screen shake
        if (screenShakeTimer > 0.0f)
        {
            screenShakeTimer -= dt;
            float shakeX = ((float)(GetRandomValue(-100, 100)) / 100.0f) * screenShakeIntensity;
            float shakeY = ((float)(GetRandomValue(-100, 100)) / 100.0f) * screenShakeIntensity;
            camera.target.x += shakeX;
            camera.target.y += shakeY;
            
            // Fade out shake intensity
            screenShakeIntensity *= 0.9f;
        }
    }
    
    // Update invincibility timer
    if (playerInvincibilityTimer > 0.0f)
    {
        playerInvincibilityTimer -= dt;
    }

#ifdef DEBUG
    if (IsKeyPressed(KEY_F4))
    {
        int delta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 4 : 1;
        map_collide.SetCollisionTopMargin(map_collide.GetCollisionTopMargin() + delta);
    }
    if (IsKeyPressed(KEY_F5))
    {
        int delta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 4 : 1;
        int newm = map_collide.GetCollisionTopMargin() - delta;
        if (newm < 0)
            newm = 0;
        map_collide.SetCollisionTopMargin(newm);
    }
#endif

    if (player)
    {
        float offsetDelta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 5.0f : 1.0f;
        if (IsKeyPressed(KEY_F2))
        {
            player->ChangeHitboxOffsetY(offsetDelta);
        }
        if (IsKeyPressed(KEY_F3))
        {
            player->ChangeHitboxOffsetY(-offsetDelta);
        }
    }

    bool attackPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool shootPressed = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
    bool jumpPressed = IsKeyPressed(KEY_SPACE);

    if (attackPressed && player->IsAnimationLocked() == false)
    {
        Audio::PlaySFx(SWORD_SLICE_SFX);

        AnimState nextAttack = AnimState::ATTACK1;

        if (currentComboStep == 0)
        {
            nextAttack = AnimState::ATTACK1;
            currentComboStep = 1;
        }
        else if (currentComboStep == 1)
        {
            nextAttack = AnimState::ATTACK2;
            currentComboStep = 2;
        }
        else if (currentComboStep == 2)
        {
            nextAttack = AnimState::ATTACK3;
            currentComboStep = 3;
        }
        else
        {
            nextAttack = AnimState::ATTACK1;
            currentComboStep = 1;
        }

        player->ChangeAnimState(nextAttack);
        comboTimer = COMBO_TIMEOUT;
    }

    if (shootPressed && player->IsAnimationLocked() == false)
    {
        player->ChangeAnimState(AnimState::SHOT1);
        currentComboStep = 0;
        comboTimer = 0.0f;
    }

    if (IsKeyPressed(KEY_H))
        player->ChangeAnimState(AnimState::HURT);
    if (IsKeyPressed(KEY_P))
        player->ChangeAnimState(AnimState::PROTECT);
    if (IsKeyPressed(KEY_R))
        player->ChangeAnimState(AnimState::RUN_ATTACK);
    if (IsKeyPressed(KEY_Q))
        player->ChangeAnimState(AnimState::DEAD);

    bool inputLocked = player->IsAnimationLocked();
    if (inputLocked)
    {
        player->anim();
        animator.Update(player, dt);
    }

    bool movingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool movingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool runKey = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    bool isRunning = (movingRight || movingLeft) && runKey;

    if (isRunning && player->isGrounded && !player->IsAnimationLocked())
    {
        Audio::PlayRunningSFX();
    }
    else
    {
        Audio::StopRunningSFX();
    }

    if (isRunning && attackPressed && player->IsAnimationLocked() == false)
    {
        Audio::PlaySFx(SWORD_SLICE_SFX);

        player->ChangeAnimState(AnimState::RUN_ATTACK);
        currentComboStep = 0;
        comboTimer = 0.0f;
    }

    if (!inputLocked)
    {
        player->velocityX = 0;

        if (movingRight)
        {
            player->velocityX = runKey ? player->speed * 1.8f : player->speed;
            player->SetFacingLeft(false);
        }
        else if (movingLeft)
        {
            player->velocityX = runKey ? -player->speed * 1.8f : -player->speed;
            player->SetFacingLeft(true);
        }
    }

    if (!inputLocked && jumpPressed && player->isGrounded)
    {
        player->velocityY = player->jumpForce;
        player->isGrounded = false;
        player->ChangeAnimState(AnimState::JUMP);
    }

    if (!player->isGrounded)
    {
        if (player->velocityY < 0)
            player->ChangeAnimState(AnimState::JUMP);
        else
            player->ChangeAnimState(AnimState::FALL);
    }
    else if (player->velocityX != 0 && !player->IsAnimationLocked())
    {
        if (runKey)
            player->ChangeAnimState(AnimState::RUN);
        else
            player->ChangeAnimState(AnimState::WALK);
    }
    else if (player->velocityX == 0 && !player->IsAnimationLocked())
    {
        player->ChangeAnimState(AnimState::IDLE);
    }

    player->ApplyPhysics(dt);

    Vector2 prevPos = {player->Pos.x - player->velocityX * dt, player->Pos.y - player->velocityY * dt};

    Rectangle rectX = Rectangle{player->Pos.x + player->hitboxOffsetX, prevPos.y + player->hitboxOffsetY, player->hitboxW, player->hitboxH};
    if (map_collide.CheckCollisionRect(rectX))
    {
        int tx = 0, ty = 0;
        if (map_collide.GetFirstCollisionTile(rectX, tx, ty))
        {
            if (player->velocityX > 0)
            {
                player->Pos.x = tx * map_collide.GetTileSize() - (player->hitboxOffsetX + player->hitboxW);
            }
            else if (player->velocityX < 0)
            {
                player->Pos.x = (tx + 1) * map_collide.GetTileSize() - player->hitboxOffsetX;
            }
        }
        player->velocityX = 0;
    }

    Rectangle rectY = {player->Pos.x + player->hitboxOffsetX, player->Pos.y + player->hitboxOffsetY, player->hitboxW, player->hitboxH};
    if (map_collide.CheckCollisionRect(rectY))
    {
        int tx = 0, ty = 0;
        if (map_collide.GetFirstCollisionTile(rectY, tx, ty))
        {
            if (player->velocityY > 0)
            {
                player->Pos.y = ty * map_collide.GetTileSize() - (player->hitboxOffsetY + player->hitboxH);
                player->isGrounded = true;
            }
            else
            {
                player->Pos.y = (ty + 1) * map_collide.GetTileSize() - player->hitboxOffsetY;
            }
        }
        player->velocityY = 0;
    }
    else
    {
        Rectangle feetCheck = {player->Pos.x + player->hitboxOffsetX, player->Pos.y + player->hitboxOffsetY + player->hitboxH + 1, player->hitboxW, 2};
        if (map_collide.CheckCollisionRect(feetCheck))
        {
            player->isGrounded = true;
        }
        else
        {
            player->isGrounded = false;
        }
    }

    player->anim();
    animator.Update(player, dt);

    if (player->deathAnimationFinished)
    {
        player->deathAnimationFinished = false;
        player->deathPending = false;
        engine.PushState(new DeathState());
        return;
    }

    // Handle player attack hitting enemies
    if (player->attackTriggered)
    {
        player->attackTriggered = false;

        // Calculate player attack position (center of hitbox)
        Vector2 playerCenter = {
            player->Pos.x + player->hitboxOffsetX + player->hitboxW * 0.5f,
            player->Pos.y + player->hitboxOffsetY + player->hitboxH * 0.5f};

        // Attack range - increased for better feel
        float attackRange = 100.0f;

        // Get all enemies in range
        std::vector<size_t> hitEnemies = enemyManager.GetEnemiesInRange(playerCenter, attackRange);

        // Apply damage to each enemy
        for (size_t idx : hitEnemies)
        {
            Enemy *enemy = enemyManager.GetEnemy(idx);
            if (enemy && enemy->hp > 0)
            {
                // Calculate knockback direction based on player facing
                Vector2 knockbackDir = {
                    player->IsFacingLeft() ? -1.0f : 1.0f,
                    -0.2f};

                // Apply damage with knockback
                float damageAmount = player->damage > 0 ? player->damage : 15.0f; // Fallback damage
                enemyManager.DamageEnemy(idx, damageAmount, knockbackDir, 250.0f);
            }
        }
    }

    enemyManager.Update(dt);

    for (size_t i = 0; i < enemyManager.GetEnemyCount(); i++)
    {
        Enemy *enemy = enemyManager.GetEnemy(i);
        if (enemy)
        {
            enemy->anim();
            animator.Update(enemy, dt);
        }
    }

    for (size_t i = 0; i < enemyManager.GetEnemyCount(); i++)
    {
        Enemy *enemy = enemyManager.GetEnemy(i);
        if (!enemy)
            continue;

        if (enemy->attackTriggered)
        {
            enemy->attackTriggered = false;
            if (player && playerInvincibilityTimer <= 0.0f)
            {
                Vector2 enemyCenter = {enemy->Pos.x + enemy->hitboxOffsetX + enemy->hitboxW * 0.5f,
                                       enemy->Pos.y + enemy->hitboxOffsetY + enemy->hitboxH * 0.5f};
                Vector2 playerCenter = {player->Pos.x + player->hitboxOffsetX + player->hitboxW * 0.5f,
                                        player->Pos.y + player->hitboxOffsetY + player->hitboxH * 0.5f};
                float dx = playerCenter.x - enemyCenter.x;
                float dy = playerCenter.y - enemyCenter.y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist <= enemy->GetAttackRange() * 1.2f)
                {
                    player->hp -= enemy->damage;
                    hud.HurtFlash();
                    
                    // Trigger screen shake on hit
                    screenShakeTimer = 0.3f;
                    screenShakeIntensity = 5.0f;
                    
                    // Start invincibility frames
                    playerInvincibilityTimer = INVINCIBILITY_DURATION;
                    
                    if (player->hp <= 0)
                    {
                        player->hp = 0;
                        player->deathPending = true;
                        player->ForceChangeAnimState(AnimState::DEAD);
                        return;
                    }
                    else
                    {
                        player->ForceChangeAnimState(AnimState::HURT);
                    }
                }
            }
        }
    }

    // Update coins animation
    for (auto &coin : coins)
    {
        coin.Update(dt);
    }

    // Check coin collection
    for (size_t i = 0; i < coins.size(); i++)
    {
        if (CheckCollisionRecs(coins[i].hitbox, player->GetHitboxRect()))
        {
            int tileX = (int)(coins[i].pos.x / interactables.GetTileSize());
            int tileY = (int)(coins[i].pos.y / interactables.GetTileSize());

            coins.erase(coins.begin() + i);
            i--;

            interactables.SetTile(tileX, tileY, 0);

            GameProgress::AddCoins(1);
        }
    }

    if (player && !levelCompletedTriggered)
    {
        Rectangle phb = player->GetHitboxRect();
        int tileSize = interactables.GetTileSize();
        int left = (int)floor(phb.x / tileSize);
        int right = (int)floor((phb.x + phb.width) / tileSize);
        int top = (int)floor(phb.y / tileSize);
        int bottom = (int)floor((phb.y + phb.height) / tileSize);

        left = std::max(0, left);
        top = std::max(0, top);
        right = std::min(interactables.GetWidth() - 1, right);
        bottom = std::min(interactables.GetHeight() - 1, bottom);

        bool foundExit = false;
        for (int ty = top; ty <= bottom && !foundExit; ++ty)
        {
            for (int tx = left; tx <= right; ++tx)
            {
                if (interactables.GetTile(tx, ty) == 280)
                {
                    foundExit = true;
                    break;
                }
            }
        }

        if (foundExit)
        {
            levelCompletedTriggered = true;
            int kills = enemyManager.GetEnemiesKilled();
            int coinsCollected = GameProgress::GetCoinsCollected();
            engine.PushState(new EndState(kills, coinsCollected));
            return;
        }
    }
}

void GameManager::Draw()
{
    BeginMode2D(camera);

    if (Loader::MapBackground.id != 0)
    {
        float bgScale = 0.3f;

        int bgWidth = (int)(Loader::MapBackground.width * bgScale);
        int bgHeight = (int)(Loader::MapBackground.height * bgScale);

        int tileSize = map_collide.GetTileSize();
        int worldWidth = map_collide.GetWidth() * tileSize;
        int worldHeight = map_collide.GetHeight() * tileSize;

        int tilesX = (worldWidth / bgWidth) + 2;
        int tilesY = (worldHeight / bgHeight) + 2;

        for (int y = 0; y < tilesY; y++)
        {
            for (int x = 0; x < tilesX; x++)
            {
                Vector2 pos = {
                    (float)(x * bgWidth),
                    (float)(y * bgHeight)};

                DrawTextureEx(Loader::MapBackground, pos, 0.0f, bgScale, WHITE);
            }
        }
    }

    map_non_colliding.DrawMap();
    interactables.DrawMap();
    map_collide.DrawMap();

    enemyManager.Draw(animator);

    // Draw player with invincibility flashing effect
    if (player)
    {
        // Flash white during invincibility frames
        if (playerInvincibilityTimer > 0.0f)
        {
            // Flash every 0.1 seconds
            bool showWhite = ((int)(playerInvincibilityTimer * 10) % 2) == 0;
            if (showWhite)
            {
                // Draw with tint to show invincibility
                BeginBlendMode(BLEND_ADDITIVE);
                animator.Draw(player);
                EndBlendMode();
            }
            else
            {
                animator.Draw(player);
            }
        }
        else
        {
            animator.Draw(player);
        }
    }

    // Draw coins
    for (auto &coin : coins)
    {
        coin.Draw();
    }

#ifdef DEBUG
    if (debugDrawCollision)
    {
        int tileSize = map_collide.GetTileSize();

        for (int y = 0; y < map_collide.GetHeight(); y++)
        {
            for (int x = 0; x < map_collide.GetWidth(); x++)
            {
                if (map_collide.IsSolidTile(x, y))
                {
                    DrawRectangleLines(x * tileSize, y * tileSize, tileSize, tileSize, GREEN);

                    int tileX = x * tileSize;
                    int tileY = y * tileSize + map_collide.GetCollisionTopMargin();
                    int tW = tileSize;
                    int tH = tileSize - map_collide.GetCollisionTopMargin();

                    DrawRectangleLines(tileX, tileY, tW, tH, RED);
                }
            }
        }

        for (int y = 0; y < interactables.GetHeight(); y++)
            for (int x = 0; x < interactables.GetWidth(); x++)
                if (interactables.IsSolidTile(x, y))
                    DrawRectangleLines(
                        x * interactables.GetTileSize(),
                        y * interactables.GetTileSize(),
                        interactables.GetTileSize(),
                        interactables.GetTileSize(),
                        SKYBLUE);

        for (int y = 0; y < map_non_colliding.GetHeight(); y++)
            for (int x = 0; x < map_non_colliding.GetWidth(); x++)
                if (map_non_colliding.IsSolidTile(x, y))
                    DrawRectangleLines(
                        x * map_non_colliding.GetTileSize(),
                        y * map_non_colliding.GetTileSize(),
                        map_non_colliding.GetTileSize(),
                        map_non_colliding.GetTileSize(),
                        GRAY);

        if (player)
        {
            Rectangle hb = player->GetHitboxRect();
            DrawRectangleLinesEx(hb, 2, RED);
        }

        enemyManager.DebugDraw();

        for (auto e : entities)
        {
            if (e)
                DrawRectangleLinesEx(e->GetHitboxRect(), 1, YELLOW);
        }
    }
#endif

    EndMode2D();

    hud.Draw();

#ifdef DEBUG
    if (debugDrawCollision && player)
    {
        DrawText(
            ("HitboxOffsetY: " + std::to_string(player->GetHitboxOffsetY())).c_str(),
            20, 20, 12, WHITE);

        DrawText(
            ("TileCollisionTopMargin: " + std::to_string(map_collide.GetCollisionTopMargin())).c_str(),
            20, 36, 12, WHITE);
    }
#endif
    
    // Always show FPS in top-right corner (useful for players too)
    DrawFPS(GetScreenWidth() - 100, 10);
}

std::vector<Vector2> GameManager::GetCoinPositions() const
{
    std::vector<Vector2> out;
    out.reserve(coins.size());
    for (const auto &c : coins)
        out.push_back(c.pos);
    return out;
}

void GameManager::SetCoinsFromPositions(const std::vector<Vector2> &positions)
{
    coins.clear();
    int tileSize = interactables.GetTileSize();
    for (int y = 0; y < interactables.GetHeight(); y++)
        for (int x = 0; x < interactables.GetWidth(); x++)
            if (interactables.GetTile(x, y) == 397)
                interactables.SetTile(x, y, 0);

    for (const auto &p : positions)
    {
        coins.emplace_back(p.x, p.y);
        int tx = (int)(p.x / tileSize);
        int ty = (int)(p.y / tileSize);
        if (tx >= 0 && ty >= 0 && tx < interactables.GetWidth() && ty < interactables.GetHeight())
            interactables.SetTile(tx, ty, 397);
    }
}

Vector2 GameManager::GetPlayerPosition() const
{
    if (player)
        return player->Pos;
    return {0.0f, 0.0f};
}