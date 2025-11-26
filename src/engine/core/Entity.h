#pragma once
#include "raylib.h"
/// @brief  Represents an entity in the game world, such as a player, enemy, or NPC.
class Entity
{
public:
    // these will be changed based on what player/enemy it is
    float hp;
    float damage;
    float speed;

    Vector2 pos;

    Entity();
    ~Entity();
};