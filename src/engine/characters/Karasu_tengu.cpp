#include "Karasu_tengu.h"

Karasu_tengu::Karasu_tengu(){}
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

void Karasu_tengu::UnloadTex()
{
    for (int i = 0; i < 3; i++) {
        UnloadTexture(attack[i]);
    }
    UnloadTexture(dead);
    UnloadTexture(hurt);
    UnloadTexture(jump);
    UnloadTexture(run);
    UnloadTexture(walk);
    UnloadTexture(idle[0]);
    UnloadTexture(idle[1]);
}

Karasu_tengu::~Karasu_tengu()
{
    UnloadTex();
}