#include "GameManager.h"

GameManager::GameManager()
{
    map.LoadMap("assets/maps/platforms.csv");
    interactables.LoadMap("assets/maps/interactables.csv");
}

GameManager::~GameManager()
{
    // NOTE(demon_slayer): Cleanup resources if any
}

void GameManager::Update()
{
    // TODO(demon_slayer): Update game logic here and movements and collisions here
}

void GameManager::Draw()
{
    interactables.DrawMap();
    map.DrawMap();
    hud.Draw();
}
