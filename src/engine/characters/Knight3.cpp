#include "Knight3.h"

void Knight3::LoadTex()
{
    attack[0] = LoadTexture("assets/Knight/Knight_3/Attack 1.png");
    attack[1] = LoadTexture("assets/Knight/Knight_3/Attack 2.png");
    attack[2] = LoadTexture("assets/Knight/Knight_3/Attack 3.png");
    dead       = LoadTexture("assets/Knight/Knight_3/Dead.png");
    defend     = LoadTexture("assets/Knight/Knight_3/Defend.png");
    hurt       = LoadTexture("assets/Knight/Knight_3/Hurt.png");
    idle[0]       = LoadTexture("assets/Knight/Knight_3/Idle.png");
    jump       = LoadTexture("assets/Knight/Knight_3/Jump.png");
    protect    = LoadTexture("assets/Knight/Knight_3/Protect.png");
    run        = LoadTexture("assets/Knight/Knight_3/Run.png");
    run_attack = LoadTexture("assets/Knight/Knight_3/Run+Attack.png");
    walk       = LoadTexture("assets/Knight/Knight_3/Walk.png");

}