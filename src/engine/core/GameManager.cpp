#include "GameManager.h"

#define KNIGHT1 1
#define KNIGHT2 2
#define KNIGHT3 3
#define SAMURAI 4
#define SAMURAI_COMMANDER 5
#define SAMURAI_ARCHER 6

GameManager::GameManager(int ID)
{
    map_collide.LoadMap("assets/maps/platforms.csv");
    map_non_colliding.LoadMap("assets/maps/map.csv");
    interactables.LoadMap("assets/maps/interactables.csv");

    // TODO(demon_slayer): a way to set the player entity to a selected charachter
    switch (ID)
    {
    case KNIGHT1:
    {
        hud.playerName = "Lionheart";
        hud.Potrait = Loader::Knight1HUD;
        break;
    }
    case KNIGHT2:
    {
        hud.playerName = "Van Gaurd";
        hud.Potrait = Loader::Knight2HUD;
        break;
    }
    case KNIGHT3:
    {
        hud.playerName = "Valerius";
        hud.Potrait = Loader::Knight3HUD;
        break;
    }
    case SAMURAI:
    {
        hud.playerName = "Akuna Bushi";
        hud.Potrait = Loader::SamuraiHUD;
        break;
    }
    case SAMURAI_ARCHER:
    {
        hud.playerName = "Kengi";
        hud.Potrait = Loader::SamuraiArcherHUD;
        break;
    }
    case SAMURAI_COMMANDER:
    {
        hud.playerName = "Shogun Kengi";
        hud.Potrait = Loader::SamuraiCommanderHUD;
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
    // TODO(demon_slayer): Update game logic here and movements and collisions here
}

void GameManager::Draw()
{
    // interactables.DrawMap();
    // map_collide.DrawMap();
    // map_non_colliding.DrawMap();
    // player->anim();

    hud.Draw();
}
