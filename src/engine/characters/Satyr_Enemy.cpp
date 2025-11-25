#include "Satyr_Enemy.h"

void Satyr_enemy::LoadTex()
{
    attack[0] = LoadTexture("assets/Satyr_enemy/Attack.png");
    dead       = LoadTexture("assets/Satyr_enemy/Dead.png");
    hurt       = LoadTexture("assets/Satyr_enemy/Hurt.png");
    idle[0]       = LoadTexture("assets/Satyr_enemy/Idle.png");
    walk       = LoadTexture("assets/Satyr_enemy/Walk.png");
    charge = LoadTexture("assets/Satyr_enemy/Charge.png");

}