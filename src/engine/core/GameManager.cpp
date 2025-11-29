#include "GameManager.h"

#include "characters/Knight1.h"
#include "characters/Knight2.h"
#include "characters/Knight3.h"
#include "characters/Samurai.h"
#include "characters/SamuraiArcher.h"
#include "characters/SamuraiCommander.h"

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
