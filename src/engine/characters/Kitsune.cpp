#include "Kitsune.h"

Kitsune::Kitsune(){}
void Kitsune::LoadTex()
{
    attack[0] = LoadTexture("assets/Yokai/Kitsune/Attack_1.png");
    attack[1] = LoadTexture("assets/Yokai/Kitsune/Attack_2.png");
    attack[2] = LoadTexture("assets/Yokai/Kitsune/Attack_3.png");
    dead       = LoadTexture("assets/Yokai/Kitsune/Dead.png");
    hurt       = LoadTexture("assets/Yokai/Kitsune/Hurt.png");
    idle[0]       = LoadTexture("assets/Yokai/Kitsune/Idle.png");
    idle[1]       = LoadTexture("assets/Yokai/Kitsune/Idle_2.png");
    jump       = LoadTexture("assets/Yokai/Kitsune/Jump.png");
    run        = LoadTexture("assets/Yokai/Kitsune/Run.png");
    walk       = LoadTexture("assets/Yokai/Kitsune/Walk.png");
    fire[0]    = LoadTexture("assets/Yokai/Kitsune/Fire_1.png");
    fire[1]    = LoadTexture("assets/Yokai/Kitsune/Fire_2.png");
}

void Kitsune::UnloadTex()
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
    UnloadTexture(fire[0]);
    UnloadTexture(fire[1]);
}
Kitsune::~Kitsune()
{
    UnloadTex();
}