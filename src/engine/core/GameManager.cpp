#include "GameManager.h"

#define KNIGHT1 1
#define KNIGHT2 2
#define KNIGHT3 3
#define SAMURAI 4
#define SAMURAI_COMMANDER 5
#define SAMURAI_ARCHER 6

GameManager::GameManager(int ID)
{
    map.LoadMap("assets/maps/platforms.csv");
    interactables.LoadMap("assets/maps/interactables.csv");

    // TODO(demon_slayer): a way to set the player entity to a selected charachter
    switch (ID)
    {
    case KNIGHT1:
        break;
    case KNIGHT2:
        break;
    case KNIGHT3:
        break;
    case SAMURAI:
        break;
    case SAMURAI_ARCHER:
        break;
    case SAMURAI_COMMANDER:
        break;
    }
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

    // TODO(demon_slayer): Remove this later just to test game state
    if (blink)
        DrawTextEx(Loader::TitleFont, "Under Construction", {350, 500}, 50, 2, WHITE);
    else
        DrawTextEx(Loader::TitleFont, "Under Construction", {350, 500}, 50, 2, YELLOW);
    blink = !blink;
}
