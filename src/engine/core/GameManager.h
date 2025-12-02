#pragma once

#include <vector>
#include "Map.h"
#include "MenuHUD.h"
#include "Animation.h"
#include "Animator.h"
#include "Coin.h"
#include "EnemyManager.h"
#include "system/GameProgress.h"
using std::vector;

class GameManager
{
private:
    bool blink = true;
    // By default draw all hitboxes as outlines. Toggle with F1.
    bool debugDrawCollision = true;
    // Layer 0: Interactables
    Map interactables;

    // Layer 1: Map non-colliding
    Map map_non_colliding;

    // Layer 2: Colliding Map
    Map map_collide;

    // Layer 3: Players +Enemies + NPCs
    std::vector<Character *> entities;
    Character *player;

    // Layer 4: HUD + UI Overlays
    MenuHUD hud;

    Animator animator;
    Camera2D camera;
    std::vector<CoinObject> coins;

    // Enemy system
    EnemyManager enemyManager;

    // Attack combo tracking
    int currentComboStep = 0;
    float comboTimer = 0.0f;
    const float COMBO_TIMEOUT = 1.5f; // Time window for next attack in combo

public:
    // NOTE(demon_slayer): the int here is for the ID passed to identify the charachter selected
    GameManager(int);
    ~GameManager();

    void Update(Engine &);
    void Draw();

    // ===== ENEMY MANAGEMENT =====
    EnemyManager &GetEnemyManager() { return enemyManager; }
};