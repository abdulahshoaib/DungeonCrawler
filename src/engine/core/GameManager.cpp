#include "GameManager.h"

#include "characters/Knight1.h"
#include "characters/Knight2.h"
#include "characters/Knight3.h"
#include "characters/Samurai.h"
#include "characters/SamuraiArcher.h"
#include "characters/SamuraiCommander.h"

#include "characters/AnimStates.h"

#define KNIGHT1 1
#define KNIGHT2 2
#define KNIGHT3 3
#define SAMURAI 4
#define SAMURAI_COMMANDER 5
#define SAMURAI_ARCHER 6

GameManager::GameManager(int ID)
{
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
}

GameManager::~GameManager()
{
    // NOTE(demon_slayer): Cleanup resources if any
}

void GameManager::Update()
{
    float dt = GetFrameTime();

    // Update animation first
    animator.Update(player, dt);

    // Don't process input if animation is locked
    if (player->IsAnimationLocked())
    {
        player->anim();
        return;
    }

    // --- MOVEMENT INPUT ---
    bool movingRight = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool movingLeft = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    bool isMoving = movingLeft || movingRight;
    bool runKey = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    // --- ACTION INPUTS ---
    bool attackPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool jumpPressed = IsKeyPressed(KEY_SPACE);

    // ************************************************************
    // 1. PRIORITY ACTIONS (highest priority → lowest)
    // ************************************************************

    // --- ATTACK ---
    if (attackPressed)
    {
        player->ChangeAnimState(AnimState::ATTACK1);
    }

    // --- JUMP ---
    else if (jumpPressed)
    {
        player->ChangeAnimState(AnimState::JUMP);
    }

    // --- TEST ANIMATIONS (your debug keys) ---
    else if (IsKeyPressed(KEY_H))
    {
        player->ChangeAnimState(AnimState::HURT);
    }
    else if (IsKeyPressed(KEY_P))
    {
        player->ChangeAnimState(AnimState::PROTECT);
    }
    else if (IsKeyPressed(KEY_R))
    {
        player->ChangeAnimState(AnimState::RUN_ATTACK);
    }
    else if (IsKeyPressed(KEY_Q))
    {
        player->ChangeAnimState(AnimState::DEAD);
    }

    // ************************************************************
    // 2. MOVEMENT ANIMATIONS
    // ************************************************************
    else if (isMoving)
    {
        if (runKey)
            player->ChangeAnimState(AnimState::RUN);
        else
            player->ChangeAnimState(AnimState::WALK);
    }

    // ************************************************************
    // 3. NO INPUT → IDLE
    // ************************************************************
    else
    {
        player->ChangeAnimState(AnimState::IDLE);
    }

    // --- UPDATE ANIMATION & FRAME ---
    player->anim();
    animator.Update(player, dt);
}

void GameManager::Draw()
{
    map_collide.DrawMap();
    interactables.DrawMap();
    map_non_colliding.DrawMap();
    
    animator.Draw(player);

    hud.Draw();
}