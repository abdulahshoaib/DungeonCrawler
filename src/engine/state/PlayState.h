#pragma once
#include "GameState.h"
#include "GameManager.h"

class PlayState : public GameState
{
private:
    GameManager gameManager;
    // Layer 1: Map
    // Layer 2: Interactables
    // Layer 3: Players + Enemies + NPCs
    // Layer 4: HUD + UI Overlays

public:
    PlayState();
    void Update(Engine &);
    void Draw(Engine &);
};