#include "Knight2.h"

void Knight2::LoadTex()
{
    attack[0] = LoadTexture("assets/Knight/Knight_2/Attack 1.png");
    attack[1] = LoadTexture("assets/Knight/Knight_2/Attack 2.png");
    attack[2] = LoadTexture("assets/Knight/Knight_2/Attack 3.png");
    dead       = LoadTexture("assets/Knight/Knight_2/Dead.png");
    defend     = LoadTexture("assets/Knight/Knight_2/Defend.png");
    hurt       = LoadTexture("assets/Knight/Knight_2/Hurt.png");
    idle[0]       = LoadTexture("assets/Knight/Knight_2/Idle.png");
    jump       = LoadTexture("assets/Knight/Knight_2/Jump.png");
    protect    = LoadTexture("assets/Knight/Knight_2/Protect.png");
    run        = LoadTexture("assets/Knight/Knight_2/Run.png");
    run_attack = LoadTexture("assets/Knight/Knight_2/Run+Attack.png");
    walk       = LoadTexture("assets/Knight/Knight_2/Walk.png");

}

void Knight2::UnloadTex()
{
    for (int i = 0; i < 3; i++) {
        UnloadTexture(attack[i]);
    }
    UnloadTexture(dead);
    UnloadTexture(defend);
    UnloadTexture(hurt);
    UnloadTexture(idle[0]);
    UnloadTexture(jump);
    UnloadTexture(protect);
    UnloadTexture(run);
    UnloadTexture(run_attack);
    UnloadTexture(walk);
}