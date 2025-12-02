#include "GameManager.h"
#include "PauseState.h"

#include "characters/Knight1.h"
#include "characters/Knight2.h"
#include "characters/Knight3.h"
#include "characters/Samurai.h"
#include "characters/SamuraiArcher.h"
#include "characters/SamuraiCommander.h"

#include "characters/AnimStates.h"

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

    // Reduce collidable region by a few pixels from top for better visuals
    map_collide.SetCollisionTopMargin(6);

    // Setup camera defaults
    camera.offset = {(float)GetScreenWidth() * 0.5f, (float)GetScreenHeight() * 0.5f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;



    switch (ID)
    {
    case KNIGHT1:
    {
        hud.playerName = "Lionheart";
        hud.Potrait = Loader::Knight1HUD;
        player = new Knight1();
        break;
    }

        // Set player hitbox to match sprite/frame size if available
        if (player && player->currentAnim)
        {
            player->hitboxW = player->currentAnim->frameWidth * 0.5f;   // half width
            player->hitboxH = player->currentAnim->frameHeight * 0.75f; // use lower 75% of sprite
            player->hitboxOffsetX = (player->currentAnim->frameWidth - player->hitboxW) * 0.5f;
            player->hitboxOffsetY = player->currentAnim->frameHeight - player->hitboxH; // align to bottom
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

    // --- Spawn coins here ---
    for (int y = 0; y < interactables.GetHeight(); y++)
    {
        for (int x = 0; x < interactables.GetWidth(); x++)
        {
            if (interactables.GetTile(x, y) == 397) // coin
            {
                float posX = x * interactables.GetTileSize();
                float posY = y * interactables.GetTileSize();
                coins.emplace_back(posX, posY);
            }
        }
    }



}

GameManager::~GameManager()
{
    // NOTE(demon_slayer): Cleanup resources if any
}

void GameManager::Update(Engine &engine)
{
    float dt = GetFrameTime();

    // =========================================================
    //     ESC → PAUSE MENU
    // =========================================================
    if (IsKeyPressed(KEY_ESCAPE))
    {
        engine.PushState(new PauseState());
        return;
    }

    // Toggle debug draw
    if (IsKeyPressed(KEY_F1))
    {
        debugDrawCollision = !debugDrawCollision;
    }

    // Update camera to center on player
    if (player)
    {
        // center the camera on the player's hitbox center
        Vector2 hitCenter = {player->Pos.x + player->hitboxOffsetX + player->hitboxW * 0.5f,
                             player->Pos.y + player->hitboxOffsetY + player->hitboxH * 0.5f};
        camera.target = hitCenter;

        // -------------------------------------------------------------------------
        // CLAMP CAMERA TO LEVEL BOUNDS
        // -------------------------------------------------------------------------

        // half of the visible area in world units (account for zoom)
        float halfViewW = camera.offset.x / camera.zoom;
        float halfViewH = camera.offset.y / camera.zoom;

        // world size based on your collision tilemap
        int tileSize = map_collide.GetTileSize();
        float worldW = map_collide.GetWidth()  * (float)tileSize;
        float worldH = map_collide.GetHeight() * (float)tileSize;

        // allowed min/max camera center positions
        float minX = halfViewW;
        float maxX = worldW - halfViewW;
        float minY = halfViewH;
        float maxY = worldH - halfViewH;

        // If the world is smaller than the screen, center instead of clamping
        if (maxX < minX) { minX = maxX = worldW * 0.5f; }
        if (maxY < minY) { minY = maxY = worldH * 0.5f; }

    #if __cplusplus >= 201703L
        // Use std::clamp for C++17+
        camera.target.x = std::clamp(camera.target.x, minX, maxX);
        camera.target.y = std::clamp(camera.target.y, minY, maxY);
    #else
        // Fallback for older C++
        camera.target.x = fmax(minX, fmin(maxX, camera.target.x));
        camera.target.y = fmax(minY, fmin(maxY, camera.target.y));
    #endif

        // -------------------------------------------------------------------------
    }

    // runtime control for tile collision top margin
    if (IsKeyPressed(KEY_F4)) // increase margin
    {
        int delta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 4 : 1;
        map_collide.SetCollisionTopMargin(map_collide.GetCollisionTopMargin() + delta);
    }
    if (IsKeyPressed(KEY_F5)) // decrease margin
    {
        int delta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 4 : 1;
        int newm = map_collide.GetCollisionTopMargin() - delta;
        if (newm < 0)
            newm = 0;
        map_collide.SetCollisionTopMargin(newm);
    }

    // Adjust hitbox vertical offset at runtime (F2/F3) for fine tuning
    if (player)
    {
        float offsetDelta = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) ? 5.0f : 1.0f;
        if (IsKeyPressed(KEY_F2)) // move hitbox down
        {
            player->ChangeHitboxOffsetY(offsetDelta);
        }
        if (IsKeyPressed(KEY_F3)) // move hitbox up
        {
            player->ChangeHitboxOffsetY(-offsetDelta);
        }
    }

    // =========================================================
    //     ACTION INPUTS (attacks, test keys)
    // =========================================================

    bool attackPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool jumpPressed = IsKeyPressed(KEY_SPACE);

    if (attackPressed && player->IsAnimationLocked() == false)
    {
        player->ChangeAnimState(AnimState::ATTACK1);
    }

    // TEST KEYS
    if (IsKeyPressed(KEY_H))
        player->ChangeAnimState(AnimState::HURT);
    if (IsKeyPressed(KEY_P))
        player->ChangeAnimState(AnimState::PROTECT);
    if (IsKeyPressed(KEY_R))
        player->ChangeAnimState(AnimState::RUN_ATTACK);
    if (IsKeyPressed(KEY_Q))
        player->ChangeAnimState(AnimState::DEAD);

    if (player->IsAnimationLocked())
    {
        player->anim();
        animator.Update(player, dt);
        return;
    }

    bool movingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool movingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool runKey = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    player->velocityX = 0;

    if (movingRight)
    {
        player->velocityX = runKey ? player->speed * 1.8f : player->speed;
        player->SetFacingLeft(false); // Face right when moving right
    }
    else if (movingLeft)
    {
        player->velocityX = runKey ? -player->speed * 1.8f : -player->speed;
        player->SetFacingLeft(true); // Face left when moving left
    }
    // When not moving, don't change facing - character remembers last direction

    if (jumpPressed && player->isGrounded)
    {
        player->velocityY = player->jumpForce;
        player->isGrounded = false;
        player->ChangeAnimState(AnimState::JUMP);
    }

    if (!player->isGrounded)
    {
        // In air
        if (player->velocityY < 0)
            player->ChangeAnimState(AnimState::JUMP);
        else
            player->ChangeAnimState(AnimState::FALL);
    }
    else if (player->velocityX != 0)
    {
        // Running or walking
        if (runKey)
            player->ChangeAnimState(AnimState::RUN);
        else
            player->ChangeAnimState(AnimState::WALK);
    }
    else
    {
        // No movement
        player->ChangeAnimState(AnimState::IDLE);
    }

    player->ApplyPhysics(dt);

    // Resolve collisions between player and world tiles.
    // Keep a copy of previous position
    Vector2 prevPos = {player->Pos.x - player->velocityX * dt, player->Pos.y - player->velocityY * dt};

    // Use player's hitbox rect for collision checks
    // previous hitbox rect is available as needed via prevPos/hitbox offsets
    Rectangle rectX = Rectangle{player->Pos.x + player->hitboxOffsetX, prevPos.y + player->hitboxOffsetY, player->hitboxW, player->hitboxH};
    if (map_collide.CheckCollisionRect(rectX))
    {
        // Resolve horizontal collision by snapping to tile boundary
        int tx = 0, ty = 0;
        if (map_collide.GetFirstCollisionTile(rectX, tx, ty))
        {
            if (player->velocityX > 0)
            {
                // moving right: place player left of tile
                player->Pos.x = tx * map_collide.GetTileSize() - (player->hitboxOffsetX + player->hitboxW);
            }
            else if (player->velocityX < 0)
            {
                // moving left: place player right of tile
                player->Pos.x = (tx + 1) * map_collide.GetTileSize() - player->hitboxOffsetX;
            }
        }
        player->velocityX = 0;
    }

    // Vertical collision check: move vertically (with possibly corrected X)
    Rectangle rectY = {player->Pos.x + player->hitboxOffsetX, player->Pos.y + player->hitboxOffsetY, player->hitboxW, player->hitboxH};
    if (map_collide.CheckCollisionRect(rectY))
    {
        // we collided vertically, try to get the colliding tile to compute a resolution
        int tx = 0, ty = 0;
        if (map_collide.GetFirstCollisionTile(rectY, tx, ty))
        {
            if (player->velocityY > 0)
            {
                // moving down: place hitbox on top of the tile
                player->Pos.y = ty * map_collide.GetTileSize() - (player->hitboxOffsetY + player->hitboxH);
                player->isGrounded = true;
            }
            else
            {
                // moving up: place below the tile
                player->Pos.y = (ty + 1) * map_collide.GetTileSize() - player->hitboxOffsetY;
            }
        }
        // Stop vertical motion
        player->velocityY = 0;
    }

    player->anim();
    animator.Update(player, dt);

    for (size_t i = 0; i < coins.size(); i++)
    {
        if (CheckCollisionRecs(coins[i].hitbox, player->GetHitboxRect()))
        {
            // Compute tile coordinates BEFORE erasing coin
            int tileX = (int)(coins[i].pos.x / interactables.GetTileSize());
            int tileY = (int)(coins[i].pos.y / interactables.GetTileSize());

            // Remove coin from vector
            coins.erase(coins.begin() + i);
            i--;

            // Update interactables map to remove the coin
            interactables.SetTile(tileX, tileY, 0);

            // Optional: play sound or add score
        }
    }

}

void GameManager::Draw()
{
    // WORLD RENDERING WITH CAMERA
    BeginMode2D(camera);

    // --- Draw tilemaps ---
    map_collide.DrawMap();
    interactables.DrawMap();
    map_non_colliding.DrawMap();

    // --- Draw player properly inside camera ---
    if (player)
        animator.Draw(player);

    // --- DEBUG DRAW (inside camera) ---
    if (debugDrawCollision)
    {
        int tileSize = map_collide.GetTileSize();

        // Collidable tiles
        for (int y = 0; y < map_collide.GetHeight(); y++)
        {
            for (int x = 0; x < map_collide.GetWidth(); x++)
            {
                if (map_collide.IsSolidTile(x, y))
                {
                    DrawRectangleLines(x * tileSize, y * tileSize, tileSize, tileSize, GREEN);

                    int tileX = x * tileSize;
                    int tileY = y * tileSize + map_collide.GetCollisionTopMargin();
                    int tW    = tileSize;
                    int tH    = tileSize - map_collide.GetCollisionTopMargin();

                    DrawRectangleLines(tileX, tileY, tW, tH, RED);
                }
            }
        }

        // Interactables
        for (int y = 0; y < interactables.GetHeight(); y++)
        for (int x = 0; x < interactables.GetWidth(); x++)
            if (interactables.IsSolidTile(x,y))
                DrawRectangleLines(
                    x * interactables.GetTileSize(),
                    y * interactables.GetTileSize(),
                    interactables.GetTileSize(),
                    interactables.GetTileSize(),
                    SKYBLUE);

        // Non-colliding
        for (int y = 0; y < map_non_colliding.GetHeight(); y++)
        for (int x = 0; x < map_non_colliding.GetWidth(); x++)
            if (map_non_colliding.IsSolidTile(x,y))
                DrawRectangleLines(
                    x * map_non_colliding.GetTileSize(),
                    y * map_non_colliding.GetTileSize(),
                    map_non_colliding.GetTileSize(),
                    map_non_colliding.GetTileSize(),
                    GRAY);

        // Player hitbox
        if (player)
        {
            Rectangle hb = player->GetHitboxRect();
            DrawRectangleLinesEx(hb, 2, RED);
        }

        // Entity hitboxes
        for (auto e : entities)
        {
            if (e)
                DrawRectangleLinesEx(e->GetHitboxRect(), 1, YELLOW);
        }
    }

    EndMode2D(); // exit camera

    // HUD drawing (screen-space)
    hud.Draw();

    // DEBUG TEXT (screen-space)
    if (debugDrawCollision && player)
    {
        DrawText(
            ("HitboxOffsetY: " + std::to_string(player->GetHitboxOffsetY())).c_str(),
            20, 20, 12, WHITE);

        DrawText(
            ("TileCollisionTopMargin: " + std::to_string(map_collide.GetCollisionTopMargin())).c_str(),
            20, 36, 12, WHITE);
    }

    for (auto& coin : coins)
        {coin.Draw();}

}