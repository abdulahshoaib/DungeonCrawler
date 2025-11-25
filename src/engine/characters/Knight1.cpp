#include "Knight1.h"

void Knight1::LoadTex()
{
    attack[0] = LoadTexture("assets/knight/knight_attack1.png");
    attack[1] = LoadTexture("assets/knight/knight_attack2.png");
    attack[2] = LoadTexture("assets/knight/knight_attack3.png");
    dead = LoadTexture("assets/knight/knight_dead.png");
    defend = LoadTexture("assets/knight/knight_defend.png");
    hurt = LoadTexture("assets/knight/knight_hurt.png");
}