#include "Knight1.h"

void Knight1::LoadTex()
{
    attack[0] = LoadTexture("assets/Knight/Knight_1/Attack 1.png");
    attack[1] = LoadTexture("assets/Knight/Knight_1/Attack 2.png");
    attack[2] = LoadTexture("assets/Knight/Knight_1/Attack 3.png");
    dead       = LoadTexture("assets/Knight/Knight_1/Dead.png");
    defend     = LoadTexture("assets/Knight/Knight_1/Defend.png");
    hurt       = LoadTexture("assets/Knight/Knight_1/Hurt.png");
    idle[0]       = LoadTexture("assets/Knight/Knight_1/Idle.png");
    jump       = LoadTexture("assets/Knight/Knight_1/Jump.png");
    protect    = LoadTexture("assets/Knight/Knight_1/Protect.png");
    run        = LoadTexture("assets/Knight/Knight_1/Run.png");
    run_attack = LoadTexture("assets/Knight/Knight_1/Run+Attack.png");
    walk       = LoadTexture("assets/Knight/Knight_1/Walk.png");

}