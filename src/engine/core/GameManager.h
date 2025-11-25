#pragma once

#include <vector>
#include "Entity.h"
#include "Map.h"
#include "MenuHUD.h"

using std::vector;

class GameManager
{
private:
    // Layer 2: Interactables
    Map interactables;

    // Layer 1: Map
    Map map;

    // Layer 3: Players + Enemies + NPCs
    std::vector<Entity> entities;
    Entity player;

    // Layer 4: HUD + UI Overlays
    MenuHUD hud;

public:
    GameManager();
    ~GameManager();

    void Update();
    void Draw();
};