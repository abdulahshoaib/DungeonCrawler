#include "Karasu_tengu.h"

void Karasu_tengu::LoadTex()
{
    attack[0] = LoadTexture("assets/Yokai/Karasu_tengu/Attack_1.png");
    attack[1] = LoadTexture("assets/Yokai/Karasu_tengu/Attack_2.png");
    attack[2] = LoadTexture("assets/Yokai/Karasu_tengu/Attack_3.png");
    dead       = LoadTexture("assets/Yokai/Karasu_tengu/Dead.png");
    hurt       = LoadTexture("assets/Yokai/Karasu_tengu/Hurt.png");
    jump       = LoadTexture("assets/Yokai/Karasu_tengu/Jump.png");
    run        = LoadTexture("assets/Yokai/Karasu_tengu/Run.png");
    walk      = LoadTexture("assets/Yokai/Karasu_tengu/Walk.png");
    idle[0]    = LoadTexture("assets/Yokai/Karasu_tengu/Idle.png");
    idle[1]    = LoadTexture("assets/Yokai/Karasu_tengu/Idle_2.png");
}