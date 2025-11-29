#pragma once

#include <vector>
#include "Map.h"
#include "MenuHUD.h"
#include "Animation.h"
#include "Animator.h"

using std::vector;

class GameManager
{
private:
    bool blink = true;
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
 
public:
    // NOTE(demon_slayer): the int here is for the ID passed to identify the charachter selected
    GameManager(int);
    ~GameManager();

    void Update();
    void Draw();
};