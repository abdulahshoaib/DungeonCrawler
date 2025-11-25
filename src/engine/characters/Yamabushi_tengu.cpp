#include "Yamabushi_tengu.h"

void Yamabushi_tengu::LoadTex()
{
    attack[0] = LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_1.png");
    attack[1] = LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_2.png");
    attack[2] = LoadTexture("assets/Yokai/Yamabushi_tengu/Attack_3.png");
    dead       = LoadTexture("assets/Yokai/Yamabushi_tengu/Dead.png");
    hurt       = LoadTexture("assets/Yokai/Yamabushi_tengu/Hurt.png");
    idle[0]       = LoadTexture("assets/Yokai/Yamabushi_tengu/Idle.png");
    idle[1]       = LoadTexture("assets/Yokai/Yamabushi_tengu/Idle_2.png");
    jump       = LoadTexture("assets/Yokai/Yamabushi_tengu/Jump.png");
    run        = LoadTexture("assets/Yokai/Yamabushi_tengu/Run.png");
    walk       = LoadTexture("assets/Yokai/Yamabushi_tengu/Walk.png");
}